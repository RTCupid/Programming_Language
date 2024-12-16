#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "../hdr/Tokenizer.h"

const char* MY_KEY_WORDS_FILE = "KeyWords.txt";

token_t* Tokenizer (tree_t* program)
{
    fprintf (program->dbg_log_file, "\nStart Tokenizer:\n");

    size_t p = 0;
    size_t token_id = 0;

    token_t*   tokens   = (token_t*)   calloc (N_TOKENS, sizeof (*tokens));

    keyword_t* keywords = InputKeyWords (program, MY_KEY_WORDS_FILE);

    KeyWordsDump (program, keywords);

    char* buffer = NULL;
    char* endptr = NULL;

    double number = 0;
    while (program->data[p]!='$') //TODO: OP to tokens, or change all operators to keywords
    {
        /*SkipSpaces (program, &p);*/

        if (isdigit (program->data[p]))
        {
            fprintf (program->dbg_log_file, "first symbol = '%c' is number\n", program->data[p]);

            int n_print_symbols = 0;

            buffer = ReadToken (program, NUM, &p, &n_print_symbols);

            number = strtod (buffer, &endptr);

            free (buffer);
            buffer = NULL;

            fprintf (program->dbg_log_file, "number is <%f>\n\n", number);

            tokens[token_id].type  = NUM;
            tokens[token_id].value = number;
            token_id++;
        }
        else if (isalpha (program->data[p]))
        {
            fprintf (program->dbg_log_file, "first symbol = '%c' is alpha\n", program->data[p]);
            char* start_pos = &program->data[p];

            int n_print_symbols = 0;

            buffer = ReadToken (program, ID, &p, &n_print_symbols);

            fprintf (program->dbg_log_file, "name = <%s>\n\n", buffer);

            size_t number_key = 0;//IsKeyWord (buffer));
            if (number_key)
            {
                tokens[token_id].type  = OP;
                tokens[token_id].value = (double)number_key;
                token_id++;
            }
            else
            {
                program->nametable[program->nametable_id].start_pos = start_pos;
                program->nametable[program->nametable_id].n_symbols = (size_t)n_print_symbols;

                tokens[token_id].type  = ID;
                tokens[token_id].value = (double)program->nametable_id;

                program->nametable_id++;
                token_id++;
            }

            free (buffer);
            buffer = NULL;
        }
        else
        {
            p++;
        }
    }

    TokenizerDump (program, tokens, keywords);
    fprintf (program->dbg_log_file, "Tokenizer completed!\n\n");

    ClearKeywords (keywords);

    return tokens;
}

// void SkipSpaces (tree_t* program, size_t* p)
// {
//     while (1)
//     {
//
//     }
// }

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
        while (isalpha (program->data[*p]))
        {
            int offset = sprintf (buffer + *n_print_symbols, "%c", program->data[*p]);
            *n_print_symbols += offset;
            *p += 1;
        }
    }
    return buffer;
}

keyword_t* InputKeyWords (tree_t* program, const char* keywords_file)
{
    FILE* k_file = fopen (keywords_file, "rt");

    char signature[SIZE_SIGNATURE] = {};

    keyword_t* keywords = (keyword_t*) calloc (N_KEYWORDS, sizeof (*keywords));

    fscanf (k_file, "%s", signature);

    int keyword_number = 0;
    size_t keywords_id = 0;

    char buffer[MAX_LEN_BUF] = {};

    fscanf (k_file, "%s %s %s", buffer, buffer, buffer);

    while(keywords_id < N_KEYWORDS)
    {
        char* name         = (char*) calloc (MAX_LEN_BUF, sizeof (*buffer));
        char* sinonim      = (char*) calloc (MAX_LEN_BUF, sizeof (*sinonim));

        fscanf (k_file, "%s %s %d", name, sinonim, &keyword_number);

        keywords[keywords_id].name_key   = name;
        fprintf (program->dbg_log_file, "\nname of key   %lu = <%s>\n", keywords_id, keywords[keywords_id].name_key);
        keywords[keywords_id].sinonim    = sinonim;
        fprintf (program->dbg_log_file, "name sinonim  %lu = <%s>\n", keywords_id, keywords[keywords_id].sinonim);
        keywords[keywords_id].number_key = keyword_number;
        fprintf (program->dbg_log_file, "number of key %lu = <%d>\n", keywords_id, keywords[keywords_id].number_key);

        keywords_id++;
    }

    return keywords;
}

void TokenizerDump (tree_t* program, token_t* tokens, keyword_t* keywords)
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
                fprintf (program->dbg_log_file, " %f\n", tokens[i].value);
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
                fprintf (program->dbg_log_file, " %s\n", keywords[(int)tokens[i].value].name_key);
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

void KeyWordsDump (tree_t* program, keyword_t* keywords)
{
    fprintf (program->dbg_log_file, "\n----------------------------------------------------------------\n"
                                    "Dump Keywords:\n");
    for (size_t i = 0; i < N_KEYWORDS; i++)
    {
        fprintf (program->dbg_log_file, "%-*s %-*s %d\n", (int)MAX_LEN_BUF, keywords[i].name_key, (int)MAX_LEN_BUF, keywords[i].sinonim, keywords[i].number_key);
    }
    fprintf (program->dbg_log_file, "\n----------------------------------------------------------------\n");
    fprintf (program->dbg_log_file, "End Dump!\n\n");
}

void ClearKeywords (keyword_t* keywords)
{
    for (size_t i = 0; i < N_KEYWORDS; i++)
    {
        free (keywords[i].name_key);
        keywords[i].name_key = NULL;

        free (keywords[i].sinonim);
        keywords[i].sinonim = NULL;
    }
    free (keywords);
    keywords = NULL;
}
