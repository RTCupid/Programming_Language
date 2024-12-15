#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "../hdr/Tokenizer.h"

token_t* Tokenizer (tree_t* program)
{
    fprintf (program->dbg_log_file, "\nStart Tokenizer:\n");

    size_t p = 0;
    size_t token_id = 0;

    token_t*   tokens   = (token_t*)   calloc (N_TOKENS, sizeof (*tokens));

    keyword_t* keywords = InputKeyWords (program, MY_KEY_WORDS_FILE);

    KeyWordsDump (program, keywords);

    char buffer[MAX_LEN_BUF] = {};
    char* endptr = NULL;

    double number = 0;
    while (program->data[p]!='$')
    {
        if (isdigit (program->data[p]))
        {
            fprintf (program->dbg_log_file, "first symbol = '%d' is number\n", program->data[p]);

            while (isdigit (program->data[p]))
            {
                sprintf (buffer, "%d", program->data[p]);
                p++;
            }
            number = strtod (buffer, &endptr);

            tokens[token_id].type  = NUM;
            tokens[token_id].value = number;
            token_id++;
        }
        else if (isalpha (program->data[p]))
        {
            fprintf (program->dbg_log_file, "first symbol = '%c' is alpha\n", program->data[p]);

            while (isalpha (program->data[p]))
            {
                sprintf (buffer, "%c", program->data[p]);
                p++;
            }
            size_t number_key = 0;//IsKeyWord (buffer));
            if (number_key)
            {
                tokens[token_id].type  = OP;
                tokens[token_id].value = (double)number_key;
            }
            else
            {
                program->nametable[program->nametable_id];
            }
        }
    }
    fprintf (program->dbg_log_file, "Tokenizer completed!\n");
    return tokens;
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

void KeyWordsDump (tree_t* program, keyword_t* keywords)
{
    fprintf (program->dbg_log_file, "\n----------------------------------------------------------------\nDump Keywords:\n");
    for (size_t i = 0; i < N_KEYWORDS; i++)
    {
        fprintf (program->dbg_log_file, "%-*s %-*s %d\n", (int)MAX_LEN_BUF, keywords[i].name_key, (int)MAX_LEN_BUF, keywords[i].sinonim, keywords[i].number_key);
    }
    fprintf (program->dbg_log_file, "\n----------------------------------------------------------------\n");
    fprintf (program->dbg_log_file, "End Dump!\n");
}
