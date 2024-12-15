#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "../hdr/Tokenizer.h"

token_t* Tokenizer (tree_t* program)
{
    size_t p = 0;
    size_t token_id = 0;

    token_t*   tokens   = (token_t*)   calloc (N_TOKENS, sizeof (*tokens));

    keyword_t* keywords = InputKeyWords (KEY_WORDS);

    char buffer[MAX_LEN_BUF] = {};
    char* endptr = NULL;

    double number = 0;
    while (program->data[p]!='$')
    {

        if (isdigit (program->data[p]))
        {
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
            while (isalpha (program->data[p]))
            {
                sprintf (buffer, "%c", program->data[p]);
                p++;
            }
            size_t number_key = IsKeyWord (buffer));
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
    return tokens;
}

keyword_t* InputKeyWords (char* keywords_file)
{
    FILE* k_file = fopen (keywords_file, "rt");

    char* signature[SIZE_SIGNATURE] = {};

    fscanf (k_file, "%s", signature);

    char* buffer       = (char*) calloc (MAX_LEN_BUF, sizeof (*buffer));
    char* sinonim      = (char*) calloc (MAX_LEN_BUF, sizeof (*sinonim));
    int keyword_number = 0;

    fscanf (k_file, "%s %s %s", buffer, buffer, buffer);
    while (fscanf (k_file, "%s %s %d", buffer, sinonim, &keyword_number) == 3)
    {

    }
}
