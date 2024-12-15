#ifndef TOKENIZER_H
    #define TOKENIZER_H

    enum types_t;

    const size_t N_TOKENS = 100;

    const size_t N_KEYWORDS = 6;

    const char* MY_KEY_WORDS_FILE = "KeyWords.txt";

    typedef struct
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

    token_t*    Tokenizer     (tree_t* program);

    keyword_t*  InputKeyWords (tree_t* program, const char* keywords_file);

    void        KeyWordsDump (tree_t* program, keyword_t* keywords);
#endif
