#ifndef RECURSIVEREADER_H
    #define RECURSIVEREADER_H
    void        InputProgram    (tree_t* expr);

    node_t*     GetG            (tree_t* program);

    node_t*     GetE            (tree_t* program);

    node_t*     GetT            (tree_t* program);

    node_t*     GetP            (tree_t* program);

    node_t*     GetN            (tree_t* program);

    node_t*     GetId           (tree_t* program);
#endif