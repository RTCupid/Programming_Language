#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../common/hdr/Enum.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/WriteProgramFile.h"
#include "../../common/hdr/colors.h"
#include "../../common/hdr/Config.h"

void WriteNameTable (tree_t* program, FILE* file, modelang_t mode)
{
    fprintf (file, "size table: %lu\n", program->nametable_id);

    for (size_t i = 0; i < program->nametable_id; i++)
    {
        assert (i < program->nametable_id);

        char identificator[MAX_LEN_BUF] = {};

        if (mode == FRONTEND)
        {
            snprintf (identificator, program->nametable[i].n_symbols + 1, "%s", program->nametable[i].start_pos);

            fprintf (file, "%lu %s %d %d \n", i, identificator, program->nametable[i].type_id, program->nametable[i].argument);

            FRONT_DBG fprintf (stderr, BHMAG "%lu %s %d %d \n" RESET, i, identificator, program->nametable[i].type_id, program->nametable[i].argument);
        }
        else if (mode == MIDDLEEND)
        {

            fprintf (file, "%lu %s %d %d \n", i, program->nametable[i].name, program->nametable[i].type_id, program->nametable[i].argument);

            FRONT_DBG fprintf (stderr, BHMAG "%lu %s %d %d \n" RESET, i, program->nametable[i].name, program->nametable[i].type_id, program->nametable[i].argument);
        }
    }
}

void WriteBase (tree_t* program, node_t* crnt_node, FILE* file, int level)
{
    WriteTab (level, file);

    fprintf (file, "{");

    if (crnt_node->type == OP)
    {
        fprintf (file, "OP:");

        if ((int)crnt_node->value == SIN)
        {
            fprintf (file, "\"sin\"");
        }
        if ((int)crnt_node->value == COS)
        {
            fprintf (file, "\"cos\"");
        }
        if ((int)crnt_node->value == LN)
        {
            fprintf (file, "\"ln\"");
        }
        else
        {
            fprintf (file, "\"%s\"", KeyFromEnum ((int)crnt_node->value));
        }
    }
    else if (crnt_node->type == ST)
    {
        fprintf (file, "OP:\"%s\"", KeyFromEnum((int)crnt_node->value));
    }
    else if (crnt_node->type == NUM)
    {
        fprintf (file, "NUM:\"%g\"", crnt_node->value);
    }
    else if (crnt_node->type == ID)
    {
        fprintf (file, "ID:\"%d\"", (int)crnt_node->value);
    }

    if (crnt_node->left && crnt_node->right)
    {
        fprintf (file, "\n");

        WriteBase (program, crnt_node->left , file, level + 1);

        WriteBase (program, crnt_node->right, file, level + 1);

        WriteTab (level, file);
    }
    else if (crnt_node->left && !crnt_node->right)
    {
        fprintf (file, "\n");

        WriteBase (program, crnt_node->left , file, level + 1);

        WriteTab (level + 1, file);

        fprintf (file, "{ID:\"\"}\n");

        WriteTab (level, file);
    }
    fprintf (file, "}\n");
    return;
}

void WriteTab (int level, FILE* file)
{
    for (int i = 1; i < level; i++)
    {
        assert (i < level);

        fprintf (file, "\t");
    }
}
