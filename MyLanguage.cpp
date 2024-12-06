#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "MyLanguage.h"
#include "DSL.h"
#include "colors.h"
#include "RecursiveReader.h"

node_t* NewNode (size_t type, double value, node_t* left, node_t* right)
{
    node_t* node = (node_t*) calloc (1, sizeof (*node));

    node->type = type;
    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

bool ProgramCtor (tree_t* program)
{
    program->dbg_log_file = fopen ("dbg_log_file.txt", "wt");
    VerifyOpenFile (program->dbg_log_file, "ProgramCtor");

    program->log_file = fopen ("log_file.htm", "wt");
    VerifyOpenFile (program->log_file, "ProgramCtor");

    program->crnt_node = NULL;

    InputProgram (program);
    printf (BLU "program->data = <%s>\n" RESET, program->data);
    program->root = GetG (program);

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

    program->crnt_node = NULL;
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

void VerifyOpenFile (FILE* file, const char* namefunc)
{
    if (file == NULL)
    {
        printf ("ERROR: in func: %s fopen returned nullptr\n", namefunc);
        assert (0);
    }
}
