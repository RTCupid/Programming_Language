#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "MyLanguage.h"
#include "DSL.h"
#include "colors.h"
#include "RecursiveReader.h"

/*
{ G  ::= E '&'
{ E  ::= T {['+' '-'] T}*
{ T  ::= P {['*' '/'] P}*
{ P  ::= '(' E ')' | N | Id
{ N  ::= ['0'-'9']+
{ Id ::= 'x'
*/
int p = 0;

node_t* GetG (tree_t* program)
{
    printf (GRN "Start\n" RESET);
    node_t* node = GetE (program);
    if (program->data[p] != '$')
    {
        assert (0);
    }
    p++;
    return node;
}

node_t* GetE (tree_t* program)
{
    node_t* node = GetT (program);
    while (program->data[p] == '+' || program->data[p] == '-')
    {
        int op = program->data[p];
        p++;
        node_t* new_node = GetT (program);
        if (op == '+')
        {
            node = _ADD (
                        node,
                        new_node);
        }
        if (op == '-')
        {
            node = _SUB (
                        node,
                        new_node);
        }
    }
    return node;
}

node_t* GetT (tree_t* program)
{
    node_t* node = GetP (program);
    while (program->data[p] == '*' || program->data[p] == '/')
    {
        int op = program->data[p];
        p++;
        node_t* new_node = GetP (program);
        if (op == '*')
        {
            node = _MUL (node, new_node);
        }
        if (op == '/')
        {
            node = _DIV (node, new_node);
        }
    }
    return node;
}

node_t* GetP (tree_t* program)
{
    if (program->data[p] == '(')
    {
        p++;
        node_t* node = GetE (program);
        if (program->data[p] != ')')
        {
            assert (0);
        }
        p++;
        return node;
    }
    if (isalpha (program->data[p]))
    {
        return GetId (program);
    }
    else
    {
        return GetN (program);
    }
}

node_t* GetId (tree_t* program)
{
    printf (RED "is alpha\n" RESET);
    char alpha = '\0';
    char identificator = {};

    sscanf (program->data + p, "%c", &alpha);

    while (isalpha (alpha))
    {
        p++;

        sscanf (program->data + p, "%c", &alpha);
    }

    return _VAR (alpha);
}

node_t* GetN (tree_t* program)
{
    int val = 0;
    while ('0' <= program->data[p] && program->data[p] <= '9')
    {
        val = val * 10 + program->data[p] - '0';
        p++;
    }
    return _NUM (val);
}

void InputProgram (tree_t* expr)
{
    struct stat fileInf = {};

    int err = stat ("Program.txt", &fileInf);
    if (err != 0)
    {
        fprintf(expr->dbg_log_file, "Stat err %d\n", err);
    }

    fprintf (expr->dbg_log_file, "\n%lu\n", (size_t)fileInf.st_size);
    fprintf (expr->dbg_log_file, "count of char = %lu\n", (size_t)fileInf.st_size / sizeof (char));

    char* expression = (char*)calloc ((size_t)fileInf.st_size + 1, sizeof(char));      // каллочу буффер, чтобы в него считать текст

    FILE* expr_file = fopen ("Program.txt", "rt");

    if (expr_file == NULL)
    {
        fprintf (expr->dbg_log_file, "File opening error\n");
        fprintf (expr->dbg_log_file, "errno = <%d>\n", errno);
        perror("Program.txt\n");
    }

    expr->size_data = (int) fread (expression, sizeof (char), (size_t)fileInf.st_size, expr_file); // с помощью fread читаю файл в буффер, сохраняю возвращаемое значение fread ()

    if (expr->size_data == 0)
    {
        fprintf (expr->dbg_log_file, "errno = <%d>\n", errno);
        perror ("Program.txt");
    }

    fprintf (expr->dbg_log_file, "\n%s\n", expression);                    // вывожу вид выражения

    fclose (expr_file);                                                   // закрываю файл

    fprintf (expr->dbg_log_file, "sizeOfFile = <%d>\n\n", expr->size_data);

    expr->data = expression;
}

