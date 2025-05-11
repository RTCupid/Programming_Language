#ifndef MAKECODENASM_H
#define MAKECODENASM_H

void   MakeNasmCode        (tree_t* program);

void   RecursiveMakeNasm   (tree_t* program, FILE* file_asm, node_t* crnt_node);

#endif
