#ifndef TOKENIZER_H
    #define TOKENIZER_H

    enum types_t;

    const size_t N_TOKENS = 100;

    const char* KEY_WORDS = "KeyWords.txt";

    typedef struct
    {
        types_t type;
        double  value;
    } token_t;

    typedef struct
    {
        size_t number_key;
        char*  name_key;
    } keyword_t;

    token_t* Tokenizer (tree_t* program);

#endif
