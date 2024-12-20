#ifndef TOKENIZER_H
#define TOKENIZER_H

enum types_t;

const size_t N_TOKENS = 100;

extern const char* MY_KEY_WORDS_FILE;

typedef struct token_t
{
    types_t type;
    double  value;
} token_t;

struct keyword_t;

/*---------------------------------------------------------------------------------------*/

token_t*    Tokenizer       (tree_t* program);

void        TokenizerDump   (tree_t* program, token_t* tokens);

void        PrintType       (tree_t* program, token_t token);

size_t      LenBuffer       (char* buffer);

int         IsInNametable   (tree_t* program, char* buffer);

size_t      IsKeyWord       (tree_t* program, char* buffer);

bool        IsOp            (tree_t* program, size_t p);

void        KeyWordsDump    (tree_t* program);

//void        ClearKeywords   (keyword_t* keywords);

char*       ReadToken       (tree_t* program, types_t mode, size_t* p, int* n_symbols_buffer);

void        SkipSpaces      (tree_t* program, size_t* p);
#endif
