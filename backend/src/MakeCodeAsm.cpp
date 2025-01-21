#include <stdio.h>
#include <stdlib.h>

#include "../../common/hdr/colors.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/MakeCodeAsm.h"

void MakeAsmCode (tree_t* program)
{
    printf (CYN "MakeAsmCode started\n" RESET);

    FILE* file_asm = fopen ("Asm_file.txt", "wt");
    if (file_asm == NULL)
    {
        printf ("ERROR: MakeAsm can't open Asm_file to write code\n");
        abort ();
    }

    RecursiveMakeAsm (program, file_asm, program->root);
    fprintf (file_asm, "hlt\n");

    printf (CYN "MakeAsmCode completed\n" RESET);
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
        fprintf (file_asm, ";%lu ", n_operator);
        fprintf (stderr, CYN ";%lu\n" RESET, n_operator);

        fprintf (stderr, CYN "%g\n" RESET, crnt_node->value);

        switch ((int)crnt_node->value)
        {
            case SMC:
            {
                n_operator++;
                fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));
                RecursiveMakeAsm (program, file_asm, crnt_node->left );
                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                break;
            }
            case END:
            {
                n_operator++;
                fprintf (file_asm, "\nhlt\n");
                break;
            }
            case PRNT:
            {
                n_operator++;
                fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));
                RecursiveMakeAsm (program, file_asm, crnt_node->left );
                fprintf (file_asm, "\nout\n");
                break;
            }
            case INPT:
            {
                n_operator++;
                fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));
                fprintf (file_asm, "\nin\n");
                fprintf (file_asm, "\npop ");
                fprintf (file_asm, "[%lu] \t; %s\n", (size_t)crnt_node->left->value, program->nametable[(int)crnt_node->left->value].name);
                break;
            }
            case SQRT:
            {
                n_operator++;
                RecursiveMakeAsm (program, file_asm, crnt_node->left);
                fprintf (file_asm, "\nsqrt\n");
                break;
            }
            case IF:
            {
                n_operator++;
                size_t num_if = n_operator;
                fprintf (stderr, GRN "operator = %s\n" RESET, KeyFromEnum ((int)crnt_node->value));
                fprintf (file_asm, "; start if.....................................................\n");
                fprintf (file_asm, "; test\n");

                if (crnt_node->left->type == OP && crnt_node->left->value == LESS)
                {
                    RecursiveMakeAsm (program, file_asm, crnt_node->left->left);
                    RecursiveMakeAsm (program, file_asm, crnt_node->left->right);
                    fprintf (file_asm, "ja end_if%lu:\n", num_if);
                }
                else if (crnt_node->left->type == OP && crnt_node->left->value == MORE)
                {
                    RecursiveMakeAsm (program, file_asm, crnt_node->left->left);
                    RecursiveMakeAsm (program, file_asm, crnt_node->left->right);
                    fprintf (file_asm, "jb end_if%lu:\n", num_if);
                }
                else
                {
                    RecursiveMakeAsm (program, file_asm, crnt_node->left);
                    fprintf (file_asm, "\npush 0\n");
                    fprintf (file_asm, "je end_if%lu:\n", num_if);
                }

                fprintf (file_asm, "; action\n");

                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                fprintf (file_asm, "end_if%lu:\n", num_if);
                fprintf (file_asm, "; end if.........................................................\n");
                break;
            }
            case EQU:
            {
                n_operator++;
                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                fprintf (file_asm, "\npop ");
                fprintf (file_asm, "[%lu] \t; %s\n", (size_t)crnt_node->left->value, program->nametable[(int)crnt_node->left->value].name);
                break;
            }
            case ADD:
            {
                n_operator++;
                RecursiveMakeAsm (program, file_asm, crnt_node->left);
                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                fprintf (file_asm, "\nadd\n");
                break;
            }
            case SUB:
            {
                n_operator++;
                RecursiveMakeAsm (program, file_asm, crnt_node->left);
                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                fprintf (file_asm, "\nsub\n");
                break;
            }
            case MUL:
            {
                n_operator++;
                RecursiveMakeAsm (program, file_asm, crnt_node->left);
                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                fprintf (file_asm, "\nmul\n");
                break;
            }
            case DIV:
            {
                n_operator++;
                RecursiveMakeAsm (program, file_asm, crnt_node->left);
                RecursiveMakeAsm (program, file_asm, crnt_node->right);
                fprintf (file_asm, "\ndiv\n");
                break;
            }
            default:
            {
                fprintf (stderr, YEL "ERROR: RecursiveMakeAsm unknown operator\n" RESET);
                abort ();
            }
        }
    }
    else if (crnt_node->type == NUM)
    {
        fprintf (file_asm, "\npush %d\n", (int)crnt_node->value);
        return;
    }
    else if (crnt_node->type == ID)
    {
        fprintf (file_asm, "\npush [%lu] \t;%s\n", (size_t)crnt_node->value, program->nametable[(int)crnt_node->value].name);
        return;
    }
}
