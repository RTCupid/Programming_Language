#ifndef MAKECODEASM_H
    #define MAKECODEASM_H

    void   MakeAsmCode         (tree_t* program, node_t* crnt_node);

    void   RecursiveMakeAsm    (tree_t* program, FILE* file_asm, node_t* crnt_node, size_t n_operator);
#endif
