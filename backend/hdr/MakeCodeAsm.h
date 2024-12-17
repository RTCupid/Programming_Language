#ifndef MAKECODEASM_H
#define MAKECODEASM_H

void   MakeAsmCode         (tree_t* program);

void   RecursiveMakeAsm    (tree_t* program, FILE* file_asm, node_t* crnt_node);
#endif
