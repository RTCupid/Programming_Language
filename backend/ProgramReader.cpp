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

#include "../Enum.h"
#include "../ProgramFunc.h"
#include "ProgramReader.h"
#include "../colors.h"

node_t* MakeProgram (tree_t* expr)
{
    return RunReadProgram (expr);   //TODO: may be unused function
}

node_t* RunReadProgram (tree_t* expr)
{
    char bracket = '\0';
    static int ID = 0;

    int offset = 0;
    PrintExprDump (expr, ID);
    offset = 0;
    sscanf (expr->data + ID, "%c%n", &bracket, &offset);
    ID += offset;
    fprintf (expr->dbg_log_file, "first bracket = <%c>\n", bracket);
    fprintf (expr->dbg_log_file, "ID -> %d\n", ID);

    if (bracket == '(' )
    {
        char buffer[MAX_LEN_BUF] = {};

        PrintExprDump (expr, ID);
        offset = 0;
        int nsymbols = sscanf (expr->data + ID, "%[^()]%n", buffer, &offset);
        fprintf (expr->dbg_log_file, "nsymbols = %d\n", nsymbols);
        fprintf (expr->dbg_log_file, "offset = %d\n", offset);
        ID += offset;
        fprintf (expr->dbg_log_file, "<%s>\n", buffer);
        fprintf (expr->dbg_log_file, "ID -> %d\n", ID);

        /*---LEFT-ARGUMENT---*/
        PrintExprDump (expr, ID);
        offset = 0;
        sscanf (expr->data + ID, "%c%n", &bracket, &offset);
        ID += offset;
        fprintf (expr->dbg_log_file, "second bracket in func = <%c>\n", bracket);
        fprintf (expr->dbg_log_file, "ID -> %d\n", ID);

        node_t* new_left = NULL;
        node_t* new_right = NULL;
        if (bracket == '(')
        {
            ID--;
            fprintf (expr->dbg_log_file, "ID -> %d\n", ID);


            new_left = RunReadProgram (expr);

            char operation = '\0';
            PrintExprDump (expr, ID);
            offset = 0;
            sscanf (expr->data + ID, "%c%n", &operation, &offset);
            ID += offset;
            fprintf (expr->dbg_log_file, "main value = <%c>\n", operation);
            fprintf (expr->dbg_log_file, "ID -> %d\n", ID);

            if (operation == ')')
            {
                size_t type = NodeType (expr, buffer[0]);
                return NewNode (type, buffer[0], new_left, new_right);
            }

            size_t type = NodeType (expr, operation);

            /*---RIGHT-ARGUMENT---*/
            PrintExprDump (expr, ID);
            offset = 0;
            sscanf (expr->data + ID, "%c%n", &bracket, &offset);
            ID += offset;
            fprintf (expr->dbg_log_file, "third bracket in func = <%c>\n", bracket);
            fprintf (expr->dbg_log_file, "ID -> %d\n", ID);

            if (bracket == '(')
            {
                //ungetc ('(', base_file);
                ID--;
                fprintf (expr->dbg_log_file, "ID -> %d\n", ID);

                new_right = RunReadProgram (expr);
                offset = 0;
                sscanf (expr->data + ID, "%c%n", &bracket, &offset);
                ID += offset;
            }

            PrintExprDump (expr, ID);
            fprintf (expr->dbg_log_file, "end bracket = <%c>\n", bracket);
            fprintf (expr->dbg_log_file, "ID -> %d\n", ID);

            if (bracket == ')')
            {
                return NewNode (type, operation, new_left, new_right);
            }
        }

        if (bracket == ')')
        {
            int value = 0;
            if (isalpha(buffer[0]))
            {
                value = 'x';
            }
            else
            {
                value = atoi (buffer);
            }
            size_t type = NodeType (expr, value);

            fprintf (expr->dbg_log_file, "return\n\n");
            return NewNode (type, value, NULL, NULL);
        }
        else
        {
            fprintf (expr->dbg_log_file, "ERROR: recursive function return null\n");
            return NULL;
        }
    }
    else
    {
        fprintf (expr->dbg_log_file, "ERROR: recursive function return null\n");
        return NULL;
    }
}

void PrintExprDump (tree_t* expr, int ID)
{
    fprintf (expr->dbg_log_file, "\nReader:\n");
    fprintf (expr->dbg_log_file, "%s", expr->data);
    for (int i = 0; i < expr->size_data; i++)
    {
        if (i == ID)
        {
            fprintf (expr->dbg_log_file, "^");
        }
        else
        {
            fprintf (expr->dbg_log_file, "_");
        }
    }
    fprintf (expr->dbg_log_file, "\n");
    for (int i = 0; i < 10; i++)
    {
        fprintf (expr->dbg_log_file, "%d", i);

    }
    fprintf (expr->dbg_log_file, "\n\n");
    fprintf (expr->dbg_log_file, "scanf:\n");
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
