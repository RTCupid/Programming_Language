#include <stdio.h>
#include <assert.h>

#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "../hdr/WriteProgramFile.h"
#include "../../hdr/colors.h"

void WriteBase (tree_t* program, node_t* crnt_node, FILE* file, int level)
{
    WriteTab (level, file);
    fprintf (file, "{");
    if (crnt_node->type == OP)
    {
        fprintf (file, "OP:");
        if (crnt_node->value == SIN)
        {
            fprintf (file, "\"sin\"");
        }
        if (crnt_node->value == COS)
        {
            fprintf (file, "\"cos\"");
        }
        if (crnt_node->value == LN)
        {
            fprintf (file, "\"ln\"");
        }
        else
        {
            fprintf (file, "\"%c\"", (int)crnt_node->value);
        }
    }
    else if (crnt_node->type == ST)
    {
        fprintf (file, "OP:\"%c\"", (int)crnt_node->value);
    }
    else if (crnt_node->type == NUM)
    {
        fprintf (file, "NUM:\"%f\"", crnt_node->value);
    }
    else if (crnt_node->type == ID)
    {
        fprintf (file, "ID:\"%d\"", (int)crnt_node->value);
    }

    if (crnt_node->left)
    {
        fprintf (file, "\n");

        WriteBase (program, crnt_node->left , file, level + 1);
        WriteBase (program, crnt_node->right, file, level + 1);
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
