#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../ProgramFunc.h"
#include "MyLanguage.h"
#include "DSL.h"
#include "colors.h"
#include "RecursiveReader.h"

bool ProgramCtor (tree_t* program)
{
    program->dbg_log_file = fopen ("frontend/dbg_log_file.txt", "wt");
    VerifyOpenFile (program->dbg_log_file, "ProgramCtor");

    program->log_file = fopen ("./bin/png/log_file.htm", "wt");
    VerifyOpenFile (program->log_file, "ProgramCtor");

    program->crnt_node = NULL;

    program->nametable = (identificator_t*) calloc (SIZE_NAMETABLE, sizeof (*program->nametable));

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

    free (program->nametable);
    program->nametable = NULL;

    program->crnt_node = NULL;
}

void VerifyOpenFile (FILE* file, const char* namefunc)
{
    if (file == NULL)
    {
        printf ("ERROR: in func: %s fopen returned nullptr\n", namefunc);
        assert (0);
    }
}
