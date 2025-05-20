#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#include "../../common/hdr/Config.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/DSL.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/ProgramReader.h"
#include "../../frontend/hdr/Tokenizer.h"
#include "../../common/hdr/colors.h"


node_t* MakeProgram (tree_t* program, const char* namefile)
{
    FILE* base_file = fopen (namefile, "rt");

    VerifyOpenFile (base_file, "MakeProgram");

    char buffer[MAX_LEN_BUF] = {};

    fscanf (base_file, "%s %s %lu", buffer, buffer, &program->nametable_id);

    for (size_t i = 0; i < program->nametable_id; i++)
    {
        size_t      addr_RAM    = 0;
        type_id_t   type_id     = TYPE_NONE;
        arg_t       argument    = WITHOUT_ARGUMENT;

        char* name = (char*) calloc (MAX_LEN_BUF, sizeof (*name));

        fscanf (base_file, "%lu %s %d %d ", &addr_RAM, name, (int*)(&type_id), (int*)(&argument));

        BACK_DBG fprintf (stderr, "%lu %s %d %d \n", addr_RAM, name, type_id, argument);

        program->nametable[i].name        = name;

        program->nametable[i].type_id     = type_id;

        program->nametable[i].argument    = argument;
    }

    node_t* new_node = RunProgram (program, base_file);

    fclose (base_file);

    return new_node;
}

node_t* RunProgram (tree_t* program, FILE* base_file)
{
    char symbol = '\0';

    fscanf (base_file, " %c", &symbol);

    fprintf (program->dbg_log_file, "start symbol = <%c>\n", symbol);

    char buffer[MAX_LEN_BUF] = {};

    int size_data            = 0;

    char* endptr             = NULL;

    node_t* node             = NULL;

    if (symbol == '{')
    {
        fscanf (base_file, "%[^\"]", buffer);

        size_t type = NodeType (buffer);

        size_data = 0;

        fscanf (base_file, "\"%[^\"]\"%n", buffer, &size_data);

        fprintf (program->dbg_log_file, "text = <%s>\n", buffer);

        switch (type)
        {
            case NUM:
            {
                node = _NUM (strtod (buffer, &endptr));

                break;
            }
            case OP:
            {
                node = NewNode (OP, (double)keywords[IsKeyWord(program, buffer)].number_key, NULL, NULL);

                break;
            }
            case ID:
            {
                node = NewNode (ID, atoi (buffer), NULL, NULL);

                break;
            }
            default:
            {
                printf (RED "ERROR: in RunProgram unknown type\n" RESET);

                exit (0);
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

size_t NodeType (char* buffer)
{
    if (strncmp (buffer, "ID:", 3) == 0)
    {
        return ID;
    }
    if (strncmp (buffer, "ST:", 3) == 0)
    {
        return ST;
    }
    if (strncmp (buffer, "OP:", 3) == 0)
    {
        return OP;
    }
    if (strncmp (buffer, "NUM:", 4) == 0)
    {
        return NUM;
    }
    /*-else-*/
    printf (RED "ERROR: unknown type <%s>\n" RESET, buffer);

    exit (0);
}
