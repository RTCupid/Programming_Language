#ifndef DIFFDUMP_H
    #define DIFFDUMP_H

//--ret-value---function-------------argument------------------------------------------------------

    void    ProgramGraphviz         (tree_t* expr, modelang_t mode);

    void    MakeNameTableHTM        (tree_t* expr);

    void    MakeDotFileGraphviz     (tree_t* expr);

    void    PrintGraphviz           (tree_t expr, node_t* node, FILE* dot_file);

    void    PrintNodeDot            (FILE* dot_file, node_t* node);

    void    DiffDump                (tree_t* tree);

    void    MakeDotFileDump         (tree_t* tree);

    void    PrintDump               (tree_t tree, node_t* node, FILE* dot_file);

    void    PrintNodeDumpDot        (FILE* dot_file, node_t* node, tree_t tree);

//-------------------------------------------------------------------------------------------------

#endif
