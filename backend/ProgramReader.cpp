#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "../Enum.h"
#include "../ProgramFunc.h"
#include "ProgramReader.h"
#include "../colors.h"


node_t* MakeProgram (tree_t* program)
{
    return RunProgram (program);
}

node_t* RunProgram (tree_t* program)
{
    char symbol = '\0';
    fscanf (base_file, " %c", &symbol);
    fprintf (program->dbg_log_file, "start symbol = <%c>\n", symbol);

    if (symbol == '{')
    {
        fscanf (base_file, "\"%[^\"]\"", program->text);
        fprintf (program->dbg_log_file, "text = <%s>\n", program->text);

        node_t* node = NewNode (program, strdup(program->text), NULL, NULL);

        fscanf (base_file, " %c", &symbol);
        fprintf (program->dbg_log_file, "end symbol = <%c>\n", symbol);

        if (symbol == '}')
        {
            fprintf (program->dbg_log_file, "return\n");
            return node;
        }
        else if (symbol == '{')
        {
            ungetc (symbol, base_file);
            /*......LEFT......*/
            node->left  = RunProgram (program, base_file);
            /*......RIGHT.....*/
            node->right = RunProgram (program, base_file);
        }
        fscanf (base_file, " %c", &symbol);
        fprintf (program->dbg_log_file, "end symbol = <%c>\n", symbol);

        if (symbol == '}')
        {
            return node;
        }
        else
        {
            fprintf (program->dbg_log_file, "ERROR: unknown symbol \" not a { or }\"\n");
        }
    }
    fprintf (program->dbg_log_file, "ERROR: uncorrect file of base\n");
    return NULL;
}


size_t NodeType (tree_t* expr, int value)
{
    fprintf (expr->dbg_log_file, "In NodeType value = %d\n", value);
    if (value == EQU || value == ADD || value == SUB || value == MUL ||
        value == DIV || value == DEG || value == SIN || value == COS ||
        value == LN)
        return OP;
    if (strncmp (value, "id", 2) == 0)
        return ID;
    else
        return NUM;
}
