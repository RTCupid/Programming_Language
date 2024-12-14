#include <stdio.h>
#include <stdlib.h>

#include "../../hdr/colors.h"
#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "../hdr/MakeCodeAsm.h"

void MakeAsmCode (tree_t* program)
{
    FILE* file_asm = fopen ("Asm_file.txt", "wt");
    if (file_asm == NULL)
    {
        printf ("ERROR: MakeAsm can't open Asm_file to write code\n");
        abort ();
    }

    RecursiveMakeAsm (program, file_asm, program->root);
}

void RecursiveMakeAsm (tree_t* program, FILE* file_asm, node_t* crnt_node)
{
    static size_t n_operator = 0;

    if (crnt_node == NULL)
    {
        return;
    }

    if (crnt_node->type == OP)
    {
        fprintf (file_asm, ";%lu\n", n_operator);

        switch ((int)crnt_node->value)
        {
            case SMC:
            {
                n_operator++;
                RecursiveMakeAsm (program, file_asm, crnt_node->left );
                n_operator++;
                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                break;
            }
            case EQU:
            {
                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                fprintf (file_asm, "pop ");
                RecursiveMakeAsm (program, file_asm, crnt_node->left);
                break;
            }
            case ADD:
            {
                RecursiveMakeAsm (program, file_asm, crnt_node->left);
                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                fprintf (file_asm, "add\n");
                break;
            }
            default:
            {
                printf (RED "ERROR: RecursiveMakeAsm unknown operator" RESET);
                abort ();
            }
        }
    }
    else if (crnt_node->type == NUM)
    {
        fprintf (file_asm, "push %f\n", crnt_node->value);
        return;
    }
    else if (crnt_node->type == ID)
    {
        fprintf (file_asm, "[%lu] ;%s\n", (size_t)crnt_node->value, program->nametable[(int)crnt_node->value].name);
        return;
    }
}
