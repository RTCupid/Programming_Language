#include <stdio.h>

#include "../../hdr/colors.h"
#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "MakeCodeAsm.h"

FILE* RecursiveMakeAsm (tree_t* program, node_t* crnt_node)
{
    FILE* file_asm = fopen ("Asm_file.txt", "wt");
    if (file_asm == NULL)
    {
        printf ("ERROR: MakeAsm can't open Asm_file to write code\n");
        abort ()
    }

    if (crnt_node->type == OP)
    {
        ;
    }
}
