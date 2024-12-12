#include <stdio.h>
#include <assert.h>

#include "../Enum.h"
#include "../ProgramFunc.h"
#include "WriteProgramFile.h"
#include "../colors.h"

void WriteBase (node_t* crnt_node, FILE* file, int level)
{
    fprintf (file, "{");
    if (crnt_node->type == OP)
    {
        if (crnt_node->value == SIN)
        {
            fprintf (file, "sin");
        }
        if (crnt_node->value == COS)
        {
            fprintf (file, "cos");
        }
        if (crnt_node->value == LN)
        {
            fprintf (file, "ln");
        }
        else
        {
            fprintf (file, "%c", (int)crnt_node->value);
        }
    }
    else if (crnt_node->type == NUM)
    {
        fprintf (file, "%f", crnt_node->value);
    }
    else if (crnt_node->type == ID)
    {
        fprintf (file, "id%d", (int)crnt_node->value);
    }

    if (crnt_node->left)
    {
        fprintf (file, "\n");

        WriteBase (crnt_node->left , file, level + 1);
        WriteBase (crnt_node->right, file, level + 1);
    }
    fprintf (file, "}");
    return;
}
