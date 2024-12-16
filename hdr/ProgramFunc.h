#ifndef PROGRAMFUNC_H
    #define PROGRAMFUNC_H

    typedef struct node_t
    {
        size_t type;
        double value;
        node_t* left;
        node_t* right;
    } node_t;

    typedef struct identificator_t
    {
        char* start_pos;
        size_t n_symbols;
        char* name;
    } identificator_t;

    struct token_t;

    typedef struct tree_t
    {
        node_t* root;
        node_t* crnt_node;
        identificator_t* nametable;
        size_t nametable_id;
        token_t* tokens;
        char* data;
        int size_data;
        FILE* log_file;
        FILE* dbg_log_file;
    } tree_t;

    enum modelang_t
    {
        FRONTEND = 0,
        BACKEND,
    };

    const size_t SIZE_NAMETABLE = 100;

    const size_t MAX_LEN_BUF = 20;

    const size_t SIZE_SIGNATURE = 20;

    /*-ret-------func----------------------arguments-----------------------------------*/
    bool        ProgramCtor     (tree_t* expr, modelang_t mode);

    void        ProgramDtor     (tree_t* expr);

    node_t*     NewNode         (size_t type, double value, node_t* left, node_t* right);

    void        ClearNameTable  (tree_t* program);

    void        ClearTree       (node_t* node);

    void        VerifyOpenFile  (FILE* file, const char* namefunc);
#endif
