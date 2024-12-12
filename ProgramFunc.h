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
        size_t start_pos;
        size_t n_symbols;
    } identificator_t;

    typedef struct tree_t
    {
        node_t* root;
        node_t* crnt_node;
        identificator_t* nametable;
        size_t nametable_id;
        char* data;
        int size_data;
        FILE* log_file;
        FILE* dbg_log_file;
    } tree_t;

    enum mode_read_t
    {
        RECURSIVE = 0,
        BRACKETS,
    };

    const size_t SIZE_NAMETABLE = 100;

    /*-ret-------func----------------------arguments-----------------------------------*/
    bool        ProgramCtor     (tree_t* expr, mode_read_t mode);

    void        ProgramDtor     (tree_t* expr);

    node_t*     NewNode         (size_t type, double value, node_t* left, node_t* right);

    void        ClearTree       (node_t* node);

    void        VerifyOpenFile  (FILE* file, const char* namefunc);
#endif
