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
#include <math.h>

#include "../hdr/Config.h"
#include "../hdr/Enum.h"
#include "../hdr/ProgramFunc.h"
#include "../../frontend/hdr/RecursiveReader.h"
#include "../../frontend/hdr/Tokenizer.h"
#include "../../backend/hdr/ProgramReader.h"
#include "../hdr/colors.h"


node_t* NewNode (size_t type, double value, node_t* left, node_t* right)
{
    node_t* node = (node_t*) calloc (1, sizeof (*node));

    node->type = type;

    if (node->type == ID)
    {
        node->value = (size_t)value;
    }
    else
    {
        node->value = value;
    }

    node->left = left;

    node->right = right;

    return node;
}

bool ProgramCtor (tree_t* program, modelang_t mode, const char* name_file_for_frontend)
{
    if (mode == FRONTEND)
    {
        program->log_file     = fopen ("build/png/front_log_file.htm", "wt");

        VerifyOpenFile (program->log_file, "ProgramCtor-log_file.htm");

        program->dbg_log_file = fopen ("frontend/dbg_log_file.txt", "wt");

        VerifyOpenFile (program->dbg_log_file, "ProgramCtor-dbg_log_file.txt");

        InputProgram   (program, name_file_for_frontend);

        FRONT_DBG fprintf (stderr, BLU "program->data = <%s>\n" RESET, program->data);
    }
    else if (mode == BACKEND)
    {
        program->dbg_log_file = fopen ("backend/dbg_log_file.txt", "wt");

        VerifyOpenFile (program->dbg_log_file, "ProgramCtor");

        program->log_file     = fopen ("./build/png/back_log_file.htm", "wt");

        VerifyOpenFile (program->log_file, "ProgramCtor");
    }

    program->crnt_node = NULL;

    program->nametable = (identificator_t*) calloc (SIZE_NAMETABLE, sizeof (*program->nametable));

    program->tokens    = NULL;

    return true;
}

bool TreeCtor (tree_t* program, modelang_t mode)
{
    if (mode == FRONTEND)
    {
        program->tokens = Tokenizer (program);

        fprintf (stderr, GRN "Finish expression construction in frontend \n" RESET);

        FRONT_DBG fprintf (stderr, GRN "expr->root = %p\n" RESET, program->root);
    }

    else if (mode == BACKEND)
    {
        program->root = MakeProgram (program, "Program_file.txt");

        fprintf (stderr, GRN "Finish expression construction in backend\n" RESET);

        BACK_DBG fprintf (stderr, GRN "expr->root = %p\n" RESET, program->root);
    }

    return true;
}

void ProgramDtor (tree_t* program)
{
    fclose (program->dbg_log_file);

    fclose (program->log_file);

    ClearTree (program->root);

    free (program->data);
    program->data = NULL;

    free (program->tokens);
    program->tokens = NULL;

    ClearNameTable (program);

    free (program->nametable);
    program->nametable = NULL;

    free (program->tokens);

    program->crnt_node = NULL;
}

void AddToNameTable (tree_t* program, size_t n_symbols, char* start_pos, type_id_t type_id, int number_func)
{
    program->nametable[program->nametable_id].start_pos   = start_pos;

    program->nametable[program->nametable_id].n_symbols   = n_symbols;

    program->nametable[program->nametable_id].type_id     = type_id;

    program->nametable[program->nametable_id].number_func = number_func;

    return;
}

void ClearNameTable (tree_t* program)
{
    for (size_t i = 0; i < program->nametable_id; i++)
    {
        free (program->nametable[i].name);

        program->nametable[i].name = NULL;
    }
}

void ClearTree (node_t* node)
{
    if (!node)
    {
        return;
    }
    if (node->left)
    {
        ClearTree (node->left);
    }
    if (node->right)
    {
        ClearTree (node->right);
    }

    free (node);

    node = NULL;
}

void InputProgram (tree_t* expr, const char* name_file_for_frontend)
{
    struct stat fileInf = {};

    int err = stat (name_file_for_frontend, &fileInf);

    if (err != 0)
    {
        fprintf(expr->dbg_log_file, "Stat err %d\n", err);
    }

    fprintf (expr->dbg_log_file, "\n%lu\n", (size_t)fileInf.st_size);

    fprintf (expr->dbg_log_file, "count of char = %lu\n", (size_t)fileInf.st_size / sizeof (char));

    char* expression = (char*)calloc ((size_t)fileInf.st_size + 1, sizeof(char));

    FILE* expr_file  = fopen (name_file_for_frontend, "rt");

    if (expr_file == NULL)
    {
        fprintf (expr->dbg_log_file, "File opening error\n");

        fprintf (stderr, RED "File opening error\n" RESET);

        fprintf (expr->dbg_log_file, "errno = <%d>\n", errno);

        perror(name_file_for_frontend);

        exit (0);
    }

    expr->size_data = (int) fread (expression, sizeof (char), (size_t)fileInf.st_size, expr_file);

    if (expr->size_data == 0)
    {
        fprintf (expr->dbg_log_file, "errno = <%d>\n", errno);

        perror (name_file_for_frontend);
    }

    fprintf (expr->dbg_log_file, "\n%s\n", expression);

    fclose (expr_file);

    fprintf (expr->dbg_log_file, "sizeOfFile = <%d>\n\n", expr->size_data);

    expr->data = expression;
}

void VerifyOpenFile (FILE* file, const char* namefunc)
{
    if (file == NULL)
    {
        printf ("ERROR: in func: %s fopen returned nullptr\n", namefunc);

        exit (0);
    }
}

const char* KeyFromEnum (int value)
{
    for (size_t i = 0; i < N_KEYWORDS; i++)
    {
        if (value == keywords[i].number_key)
        {
            return keywords[i].key_op;
        }
    }

    printf (YEL "ERROR: KeyFromEnum: unknown OP enum %d\n" RESET, value);

    exit (0);
}
