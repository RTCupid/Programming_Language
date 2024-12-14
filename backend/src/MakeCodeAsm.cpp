#include <stdio.h>
#include <stdlib.h>

#include "../../hdr/colors.h"
#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "../hdr/MakeCodeAsm.h"

void MakeAsmCode (tree_t* program)
{
    size_t n_operator = 0;
    FILE* file_asm = fopen ("Asm_file.txt", "wt");
    if (file_asm == NULL)
    {
        printf ("ERROR: MakeAsm can't open Asm_file to write code\n");
        abort ();
    }

    RecursiveMakeAsm (program, file_asm, program->root, n_operator);
}

void RecursiveMakeAsm (tree_t* program, FILE* file_asm, node_t* crnt_node, size_t n_operator)
{
    fprintf (file_asm, ";%lu\n", n_operator);

    if (crnt_node->type == NUM)
    {
        fprintf (file_asm, "%f\n", crnt_node->value);
        return;
    }
    else if (crnt_node->type == ID)
    {
        fprintf (file_asm, "%lu\n", (size_t)crnt_node->value);
        return;
    }
    // if (crnt_node->type == OP)
    // {
    //
    // }
    RecursiveMakeAsm (program, file_asm, crnt_node->left, n_operator);
    RecursiveMakeAsm (program, file_asm, crnt_node->left, n_operator);
}
