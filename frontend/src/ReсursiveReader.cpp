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

#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "../../hdr/DSL.h"
#include "../../hdr/colors.h"
#include "../hdr/Tokenizer.h"
#include "../hdr/RecursiveReader.h"

bool status = true;
//+ - 1+ times
/*
Main:
{ G  ::= {St ';'}+ '&'
{ St ::= A | ... // пока только присваивание
Everything
{ A  ::= Id '=' E
if
while
Equation
{ E  ::= T {['+' '-'] T}*
{ T  ::= P {['*' '/'] P}*
{ P  ::= '(' E ')' | N | Id
> <
TOkens:
{ N  ::= ['0'-'9']+
{ Id ::= ['a'-'z']+
*/
size_t p = 0;

node_t* GetG (tree_t* program)
{
    printf (GRN "Start\n" RESET);

    node_t* node = _ST(NULL, NULL);

    node->left = GetOp (program);
    node->right = _ST(NULL, NULL);

    node_t* crnt_node = node->right;

    while (program->data[p] == ';')
    {
        p++;
        crnt_node->left = GetOp (program);
        crnt_node->right = _ST(NULL, NULL);
        crnt_node = crnt_node->right;
    }

    if (program->data[p] != '$')
    {
        SintaxError (program);
    }
    p++;
    return node;
}

node_t* GetOp (tree_t* program)
{
    node_t* node = GetA (program);
    return node;
}

node_t* GetA (tree_t* program)
{
    node_t* new_right_node = NULL;
    node_t* new_left_node  = NULL;
    if (isalpha (program->data[p]))
    {
        new_left_node = GetId (program);
        if (program->data[p] == '=')
        {
            p++;
        }
        else
        {
            SintaxError (program);
        }
        new_right_node = GetE (program);
    }
    else
    {
        SintaxError (program);
    }

    return _EQU (new_left_node, new_right_node);
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
            SintaxError (program);
        }
        p++;
        return node;
    }
    if (isalpha (program->data[p]))
    {
        return GetId (program);
    }
    if (isdigit (program->data[p]))
    {
        return GetN (program);
    }

    /*---else---*/
    SintaxError (program);
    return NULL;
}

node_t* GetId (tree_t* program)
{
    printf (MAG "is alpha\n" RESET);

    size_t n_symbols = 0;
    char* start_pos = &program->data[p];

    while (isalpha (program->data[p]))
    {
        fprintf(program->dbg_log_file, "p = %lu, alpha = <%c>\n", p, program->data[p]);
        n_symbols++;
        p++;
    }

    fprintf (program->dbg_log_file, "nt_id = %lu, start_pos = %p, n_symbols = %lu\n", program->nametable_id, start_pos, n_symbols);

    program->nametable[program->nametable_id].n_symbols = n_symbols;
    program->nametable[program->nametable_id].start_pos = start_pos;
    size_t index = program->nametable_id;

    program->nametable_id++;

    return _ID ((double)index);
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

void SintaxError (tree_t* program)
{
    fprintf (program->dbg_log_file, "SYNTAX ERROR: %c\n", program->data[p]);
    fprintf (stderr, "SYNTAX ERROR: %c\n", program->data[p]);
    abort ();
}


