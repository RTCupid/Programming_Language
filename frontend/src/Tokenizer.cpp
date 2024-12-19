#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../../common/hdr/Enum.h"
#include "../../common/hdr/colors.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/Tokenizer.h"


//First version
//The_Shogun_ordered jojo assign food multiply 666          | jojo  = food * 666;
//The_Shogun_ordered ded  assign 333 add food               | ded   = 333 + food;
//The_Shogun_ordered tyoma assign 166 subtract 2            | tyoma = 166;
//If (night add 5) The_Shogun_ordered to_write_about (ded)  | if (night + 5) printf ("%d", ded);
//While_samurai_do (ex) The_Shogun_ordered tyoma assign tyoma add 1

//Second version
//The Shogun ordered jojo assign food multiply 666                    | jojo  = food * 666;
//The Shogun ordered ded  assign 333 add food                         | ded   = 333 + food;
//The Shogun ordered tyoma assign 166 subtract 2                      | tyoma = 166;
//If happens (night add 5) The Shogun ordered to write about (ded)    | if (night + 5) printf ("%d", ded);
//While samurai do (ex) The Shogun ordered tyoma assign tyoma add 1

token_t* Tokenizer (tree_t* program)
{
    fprintf (program->dbg_log_file, "\nStart Tokenizer:\n");

    size_t p = 0;
    size_t token_id = 0;

    token_t*   tokens   = (token_t*)   calloc (N_TOKENS, sizeof (*tokens));

    KeyWordsDump (program);

    char* buffer = NULL;
    char* endptr = NULL;

    double number = 0;

    int next = 1;

    //printf (RED "program->data in Tokenizer = <%p>\n" RESET, program->data);

    while (next) //TD: OP to tokens, or change all operators to keywords (est)
    {
        SkipSpaces (program, &p);

        if (isdigit (program->data[p]))
        {
            fprintf (program->dbg_log_file, "first symbol = '%c' is number\n", program->data[p]);

            int n_print_symbols = 0;

            buffer = ReadToken (program, NUM, &p, &n_print_symbols);

            number = strtod (buffer, &endptr);

            free (buffer);
            buffer = NULL;

            fprintf (program->dbg_log_file, "number is <%g>\n\n", number);

            tokens[token_id].type  = NUM;
            tokens[token_id].value = number;
            token_id++;
        }
        else
        {
            fprintf (program->dbg_log_file, "first symbol = <%c> is alpha\n", program->data[p]);
            char* start_pos = &program->data[p];

            int n_print_symbols = 0;

            buffer = ReadToken (program, ID, &p, &n_print_symbols);

            fprintf (program->dbg_log_file, "name = <%s>\n", buffer);

            size_t number_key = IsKeyWord (program, buffer);
            fprintf (program->dbg_log_file, "number_key = <%lu>\n", number_key);

            if (number_key)
            {
                tokens[token_id].type  = OP;
                tokens[token_id].value = (double)number_key;
                token_id++;

                fprintf (program->dbg_log_file, "\n");

                //fprintf (program->dbg_log_file, "!!! %d\n", keywords[number_key].number_key);

                if (keywords[number_key].number_key == END)
                {
                    next = 0;
                    fprintf (program->dbg_log_file, "next = %d\n\n", next);
                }
            }
            else
            {
                program->nametable[program->nametable_id].start_pos = start_pos;
                program->nametable[program->nametable_id].n_symbols = (size_t)n_print_symbols;

                tokens[token_id].type  = ID;
                tokens[token_id].value = (double)program->nametable_id;

                fprintf (program->dbg_log_file, "new token's nametable_id = %lu\n\n", program->nametable_id);

                program->nametable_id++;
                token_id++;
            }

            free (buffer);
            buffer = NULL;
        }
        SkipSpaces (program, &p);
    }

    TokenizerDump (program, tokens);
    fprintf (program->dbg_log_file, "Tokenizer completed!\n\n");

    return tokens;
}

bool IsOp (tree_t* program, size_t p)
{
    if (program->data[p] == '=' || program->data[p] == '*' || program->data[p] == '/' ||
        program->data[p] == '+' || program->data[p] == '-'   )
    {
        return true;
    }
    else
    {
        return false;
    }
}

size_t IsKeyWord (tree_t* program, char* buffer)
{
    size_t number_key = 0;

    for (size_t i = 0; i < N_KEYWORDS; i++)
    {
        if (strcmp (buffer, keywords[i].name_key) == 0)
        {
            number_key = i;
            fprintf (program->dbg_log_file, "<%s> is keyword\n", buffer);
            break;
        }
    }

    return number_key;
}

void SkipSpaces (tree_t* program, size_t* p)
{
    while (isspace (program->data[*p]))
    {
        *p += 1;
    }
}

char* ReadToken (tree_t* program, types_t mode, size_t* p, int* n_print_symbols)
{
    char* buffer = (char*) calloc (MAX_LEN_BUF, sizeof (*buffer));

    if (mode == NUM)
    {
        *n_print_symbols = 0;
        while (isdigit (program->data[*p]))
        {
            int offset = sprintf (buffer + *n_print_symbols, "%c", program->data[*p]);
            *n_print_symbols += offset;
            *p += 1;
        }
    }
    if (mode == ID)
    {
        *n_print_symbols = 0;
        if (ispunct (program->data[*p]))
        {
            int offset = sprintf (buffer + *n_print_symbols, "%c", program->data[*p]);
            *n_print_symbols += offset;
            *p += 1;
        }
        else
        {
            while (isalpha (program->data[*p]))         //TODO: ispunct, if ispunct read one char and end of reading
            {
                int offset = sprintf (buffer + *n_print_symbols, "%c", program->data[*p]);
                *n_print_symbols += offset;
                *p += 1;
            }
        }
    }
    return buffer;
}

void TokenizerDump (tree_t* program, token_t* tokens)
{
    fprintf (program->dbg_log_file, "----------------------------------------------------------------\n"
                                    "Dump Tokens:\n");
    for (size_t i = 0; tokens[i].type != 0; i++)
    {
        PrintType (program, tokens[i]);
        switch (tokens[i].type)
        {
            case NUM:
            {
                fprintf (program->dbg_log_file, " %g\n", tokens[i].value);
                break;
            }
            case ID:
            {
                char name[MAX_LEN_BUF] = {};

                snprintf (name, program->nametable[(int)tokens[i].value].n_symbols + 1, "%s", program->nametable[(int)tokens[i].value].start_pos);

                fprintf (program->dbg_log_file, " %s\n", name);
                break;
            }
            case OP:
            {
                fprintf (program->dbg_log_file, " %s\n", keywords[(int)tokens[i].value].key_op);
                break;
            }
            case ST:
            {
                fprintf (program->dbg_log_file, " %c", (int)tokens[i].value);
                break;
            }
            default:
            {
                fprintf (program->dbg_log_file, "ERROR: TokenizerDump - unknown type\n");
                abort ();
            }
        }
    }
}

void PrintType (tree_t* program, token_t token)
{
    switch (token.type)
    {
        case ID:
        {
            fprintf (program->dbg_log_file, "ID");
            break;
        }
        case OP:
        {
            fprintf (program->dbg_log_file, "OP");
            break;
        }
        case NUM:
        {
            fprintf (program->dbg_log_file, "NUM");
            break;
        }
        case ST:
        {
            fprintf (program->dbg_log_file, "ST");
            break;
        }
        default:
        {
            fprintf (program->dbg_log_file, "ERROR: PrintType - Unknown type\n");
            abort ();
        }
    }
}

void KeyWordsDump (tree_t* program)
{
    fprintf (program->dbg_log_file, "\n----------------------------------------------------------------\n"
                                    "Dump Keywords:\n");
    for (size_t i = 0; i < N_KEYWORDS; i++)
    {
        fprintf (program->dbg_log_file, "%-*s %d\n", (int)MAX_LEN_BUF, keywords[i].name_key, keywords[i].number_key);
    }
    fprintf (program->dbg_log_file, "\n----------------------------------------------------------------\n");
    fprintf (program->dbg_log_file, "End Dump!\n\n");
}

// void ClearKeywords (keyword_t* keywords)
// {
//     if (!keywords)
//     {
//         return;
//     }
//     for (size_t i = 0; i < N_KEYWORDS; i++)
//     {
//         free (keywords[i].name_key);
//         keywords[i].name_key = NULL;
//
//         free (keywords[i].sinonim);
//         keywords[i].sinonim = NULL;
//     }
//     free (keywords);
//     keywords = NULL;
// }
