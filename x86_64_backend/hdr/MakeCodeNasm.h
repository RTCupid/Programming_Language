#ifndef MAKECODENASM_H
#define MAKECODENASM_H

enum order_t
{
    FIRST_EXPR,
    SECOND_EXPR,
};

void   MakeNasmCode        (tree_t* program);

void   RecursiveMakeNasm   (tree_t* program, FILE* file_asm, node_t* crnt_node, order_t variable_order = FIRST_EXPR);

#endif
