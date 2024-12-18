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

#define _CMP_OP(operator) (program->tokens[p].type == OP && strcmp(keywords[p].key_op, operator) == 0)

node_t* GetG (tree_t* program)
{
    printf (GRN "Start\n" RESET);

    node_t* node = _ST(NULL, NULL);

    node->left = GetOp (program);
    node->right = _ST(NULL, NULL);

    node_t* crnt_node = node->right;

    while (_CMP_OP(";"))
    {
        p++;
        crnt_node->left = GetOp (program);
        crnt_node->right = _ST(NULL, NULL);
        crnt_node = crnt_node->right;
    }

    if (!_CMP_OP("$"))
    {
        SintaxError (program, "GetG");
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
    if (program->tokens[p].type == ID)
    {
        new_left_node = _ID (program->tokens[p].value);
        p++;
        if (_CMP_OP("="))
        {
            p++;
        }
        else
        {
            SintaxError (program, "GetA");
        }
        new_right_node = GetE (program);
    }
    else
    {
        SintaxError (program, "GetA");
    }

    return _EQU (new_left_node, new_right_node);
}

node_t* GetE (tree_t* program)
{
    node_t* node = GetT (program);
    while (_CMP_OP("+") || _CMP_OP("-"))
    {
        const char* op = keywords[p].key_op;
        //int op = program->data[p];
        p++;
        node_t* new_node = GetT (program);
        if (strcmp (op, "+"))
        {
            node = _ADD (
                        node,
                        new_node);
        }
        if (strcmp (op, "-"))
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
    while (_CMP_OP("*") || _CMP_OP ("/"))
    {
        const char* op = keywords[p].key_op;
        p++;
        node_t* new_node = GetP (program);
        if (strcmp (op, "*"))
        {
            node = _MUL (node, new_node);
        }
        if (strcmp (op, "/"))
        {
            node = _DIV (node, new_node);
        }
    }
    return node;
}

node_t* GetP (tree_t* program)
{
    if (_CMP_OP("("))
    {
        p++;
        node_t* node = GetE (program);
        if (!_CMP_OP(")"))
        {
            SintaxError (program, "GetP");
        }
        p++;
        return node;
    }
    if (program->tokens[p].type == ID)
    {
        return _ID (program->tokens[p].value);
    }
    if (program->tokens[p].type == NUM)
    {
        return _NUM (program->tokens[p].type);
    }

    /*---else---*/
    SintaxError (program, "GetP");
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

void SintaxError (tree_t* program, const char* name_func)
{
    fprintf (program->dbg_log_file, "SYNTAX ERROR: %s: unknown token: token[%lu].type = ", name_func, p);
    PrintType (program, program->tokens[p]);
    fprintf (program->dbg_log_file, " token[%lu].value = %g", p, program->tokens[p].value);

    fprintf (stderr, YEL "SYNTAX ERROR: %s: unknown token: token[%lu].type = %d\n" RESET, name_func, p, program->tokens[p].type);
    fprintf (stderr, YEL "token[%lu].value = %g\n" RESET, p, program->tokens[p].value);
    abort ();
}


