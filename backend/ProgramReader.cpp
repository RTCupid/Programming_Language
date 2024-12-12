#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "../Enum.h"
#include "../DSL.h"
#include "../ProgramFunc.h"
#include "ProgramReader.h"
#include "../colors.h"


node_t* MakeProgram (tree_t* program, const char* namefile)
{
    FILE* base_file = fopen (namefile, "rt");
    VerifyOpenFile (base_file, "MakeAkinatorBase");

    node_t* new_node = RunProgram (program, base_file);

    // program->deep = FindDeepTree (program, program->root, 1);
    // fprintf (program->dbg_log_file, "deep of tree = <%lu>\n", program->deep);

    fclose (base_file);
    return new_node;
}

node_t* RunProgram (tree_t* program, FILE* base_file)
{
    char symbol = '\0';
    fscanf (base_file, " %c", &symbol);
    fprintf (program->dbg_log_file, "start symbol = <%c>\n", symbol);

    char buffer[MAX_LEN_BUF] = {};
    int size_data = 0;
    char* endptr = NULL;
    node_t* node = NULL;

    if (symbol == '{')
    {
        size_data = 0;
        fscanf (base_file, "\"%[^\"]\"%n", buffer, &size_data);
        fprintf (program->dbg_log_file, "text = <%s>\n", buffer);

        size_t type = NodeType (program, buffer);

        switch (type)
        {
            case NUM:
            {
                node = _NUM (strtod (buffer, &endptr));
                break;
            }
            case OP:
            {
                node = NewNode (OP, buffer[0], NULL, NULL);
                break;
            }
            case ID:
            {
                node = NewNode (ID, atoi (buffer + 2), NULL, NULL);
                break;
            }
            default:
            {

                abort ();
            }
        }

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



size_t NodeType (tree_t* expr, char* value)
{
    fprintf (expr->dbg_log_file, "In NodeType value = %s\n", value);
    if (strncmp (value, "id", 2) == 0)
        return ID;
    if (value[0] == EQU || value[0] == ADD || value[0] == SUB || value[0] == MUL || //TODO: may be other method of find type
        value[0] == DIV || value[0] == DEG || value[0] == SIN || value[0] == COS ||
        value[0] == LN)
        return OP;
    else
        return NUM;
}
