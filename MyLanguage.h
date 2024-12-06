 #ifndef LANGUAGE_H
     #define LANGUAGE_H

    enum types_t
    {
        OP,
        NUM,
        VAR,
    };

    enum OP_t
    {
        EQU = '=',
        ADD = '+',
        SUB = '-',
        MUL = '*',
        DIV = '/',
        DEG = '^',
        SIN = 's',
        COS = 'c',
         LN = 'l',
    };

    typedef struct node_t
    {
        size_t type;
        double value;
        node_t* left;
        node_t* right;
    } node_t;

    typedef struct
    {
        node_t* root;
        node_t* crnt_node;
        char* data;
        int size_data;
        FILE* log_file;
        FILE* dbg_log_file;
    } tree_t;

    /*-ret-------func----------------------arguments-----------------------------------*/
    node_t*     NewNode         (size_t type, double value, node_t* left, node_t* right);

    bool        ProgramCtor     (tree_t* expr);

    void        ProgramDtor     (tree_t* expr);

    void        ClearTree       (node_t* node);

    void        VerifyOpenFile  (FILE* file, const char* namefunc);
#endif
