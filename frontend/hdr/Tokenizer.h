#ifndef TOKENIZER_H
    #define TOKENIZER_H

    enum types_t;

    const size_t N_TOKENS = 100;

    const size_t N_KEYWORDS = 6;

    extern const char* MY_KEY_WORDS_FILE;

    typedef struct token_t
    {
        types_t type;
        double  value;
    } token_t;

    typedef struct
    {
        int number_key;
        char*  sinonim;
        char*  name_key;
    } keyword_t;

/*---------------------------------------------------------------------------------------*/

    token_t*    Tokenizer       (tree_t* program);

    void        TokenizerDump   (tree_t* program, token_t* tokens, keyword_t* keywords);

    void        PrintType       (tree_t* program, token_t token);

    keyword_t*  InputKeyWords   (tree_t* program, const char* keywords_file);

    void        KeyWordsDump    (tree_t* program, keyword_t* keywords);

    void        ClearKeywords   (keyword_t* keywords);

    char*       ReadToken       (tree_t* program, types_t mode, size_t* p, int* n_symbols_buffer);
#endif
