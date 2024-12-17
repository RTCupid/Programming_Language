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

#include "../hdr/Enum.h"
#include "../hdr/ProgramFunc.h"
#include "../frontend/hdr/RecursiveReader.h"
#include "../frontend/hdr/Tokenizer.h"
#include "../backend/hdr/ProgramReader.h"
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

//TD: One func for rec descent & Program Ctor & Tree Ctor
bool ProgramCtor (tree_t* program, modelang_t mode)
{
    if (mode == FRONTEND)
    {
        program->log_file = fopen ("./bin/png/front_log_file.htm", "wt");
        VerifyOpenFile (program->log_file, "ProgramCtor");
        program->dbg_log_file = fopen ("frontend/dbg_log_file.txt", "wt");
        VerifyOpenFile (program->dbg_log_file, "ProgramCtor");

        InputProgram (program);
        printf (BLU "program->data = <%s>\n" RESET, program->data);
    }
    else if (mode == BACKEND)
    {
        program->dbg_log_file = fopen ("backend/dbg_log_file.txt", "wt");
        VerifyOpenFile (program->dbg_log_file, "ProgramCtor");
        program->log_file = fopen ("./bin/png/back_log_file.htm", "wt");
        VerifyOpenFile (program->log_file, "ProgramCtor");
    }

    program->crnt_node = NULL;

    program->nametable = (identificator_t*) calloc (SIZE_NAMETABLE, sizeof (*program->nametable));

    program->tokens =NULL;

    return true;
}

bool TreeCtor (tree_t* program, modelang_t mode)
{
    if (mode == FRONTEND)
    {
        program->tokens = Tokenizer (program);
    }

    else if (mode == BACKEND)
    {
        program->root = MakeProgram (program, "Program_file.txt");
    }

    printf (GRN "Finish expression construction \n" RESET);
    printf (GRN "expr->root = %p\n" RESET, program->root);

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

    ClearKeywords (program->keywords);

    program->crnt_node = NULL;
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

void VerifyOpenFile (FILE* file, const char* namefunc)
{
    if (file == NULL)
    {
        printf ("ERROR: in func: %s fopen returned nullptr\n", namefunc);
        assert (0);
    }
}

