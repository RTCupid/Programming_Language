 #ifndef LANGUAGE_H
    #define LANGUAGE_H

    struct node_t;

    struct identificator_t;

    struct tree_t;

    const size_t SIZE_NAMETABLE = 100;

    /*-ret-------func----------------------arguments-----------------------------------*/
    bool        ProgramCtor     (tree_t* expr);

    void        ProgramDtor     (tree_t* expr);

    void        VerifyOpenFile  (FILE* file, const char* namefunc);
#endif
