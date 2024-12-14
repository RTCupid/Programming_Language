#include <stdio.h>

#include "../../hdr/colors.h"
#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "MakeCodeAsm.h"

void MakeAsmCode (tree_t* program, node_t* crnt_node)
{
    size_t n_operator = 0;
    FILE* file_asm = fopen ("Asm_file.txt", "wt");
    if (file_asm == NULL)
    {
        printf ("ERROR: MakeAsm can't open Asm_file to write code\n");
        abort ()
    }

    RecursiveMakeAsm (program, file_asm, crnt_node, n_operator);
}

void RecursiveMakeAsm (tree_t* program, FILE* file_asm, node_t* crnt_node, size_t n_operator)
{
    fprintf (file_asm, ";%lu\n", n_operator);

    if (crnt_node->type == NUM)
    {
        fprintf (file_asm, "%f\n", crnt_node->value);
    }
    else if (crnt_node->type == ID)
    {

    }
    if (crnt_node->type == OP)
    {

    }
}
