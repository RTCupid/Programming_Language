#ifndef PROGRAMREADER_H
    #define PROGRAMREADER_H

    node_t* MakeProgram     (tree_t* expr);

    node_t* RunReadProgram  (tree_t* expr);

    void    PrintExprDump   (tree_t* expr, int ID);

    size_t  NodeType        (tree_t* expr, int value);
#endif
