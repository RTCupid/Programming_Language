#include <stdio.h>
#include <stdlib.h>

#include "../../common/hdr/Config.h"
#include "../../common/hdr/colors.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/MakeCodeNasm.h"

void MakeNasmCode (tree_t* program)
{
    printf (GRN "MakeNasmCode started\n" RESET);

    FILE* file_nasm = fopen ("Nasm_file.txt", "wt");

    if (file_nasm == NULL)
    {
        fprintf (stderr, "ERROR: MakeNasm can't open Nasm_file to write code\n");

        exit (0);
    }
    fprintf (file_nasm, ";--------------------------------------------------------------------------------------------------\n");
    fprintf (file_nasm, ";                           Programming language\n");
    fprintf (file_nasm, ";                         (c) 2025 Muratov Artyom\n");
    fprintf (file_nasm, ";--------------------------------------------------------------------------------------------------\n");

    RecursiveMakeNasm (program, file_nasm, program->root);

    fprintf (file_nasm, "\nhlt\n");

    printf (GRN "MakeNasmCode completed\n" RESET);
}

void RecursiveMakeNasm (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    static size_t n_operator = 0;

    if (crnt_node == NULL)
    {
        return;
    }

    if (crnt_node->type == OP)
    {
        fprintf (file_nasm, ";number operator = %lu ", n_operator);

        BACK_DBG fprintf (stderr, CYN ";%lu\n" RESET, n_operator);

        BACK_DBG fprintf (stderr, CYN "%g\n" RESET, crnt_node->value);

        switch ((int)crnt_node->value)
        {
            case SMC:
            {
                n_operator++;

                BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

                RecursiveMakeNasm (program, file_nasm, crnt_node->left );

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                break;
            }
            case END:
            {
                n_operator++;

                fprintf (file_nasm, "\nhlt\n");

                break;
            }
            case PRNT:
            {
                n_operator++;

                BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

                RecursiveMakeNasm (program, file_nasm, crnt_node->left );

                fprintf (file_nasm, "\nout\n");

                break;
            }
            case INPT:
            {
                n_operator++;

                BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

                fprintf (file_nasm, "\nin\n");

                fprintf (file_nasm, "\npop ");

                fprintf (file_nasm, "[%lu] \t; %s\n", (size_t)crnt_node->left->value, program->nametable[(int)crnt_node->left->value].name);

                break;
            }
            case SQRT:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                fprintf (file_nasm, "\nsqrt\n");

                break;
            }
            case IF:
            {
                n_operator++;

                size_t num_if = n_operator;

                BACK_DBG fprintf (stderr, GRN "operator = %s\n" RESET, KeyFromEnum ((int)crnt_node->value));

                fprintf (file_nasm, "\n; -------start-if-%lu-----------------------\n", num_if);

                fprintf (file_nasm, "\n; -------start-test-%lu---------------------\n", num_if);

                if (crnt_node->left->type == OP && (int)crnt_node->left->value == LESS)
                {
                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->left);

                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->right);

                    fprintf (file_nasm, "\nja end_if%lu:\n", num_if);
                }
                else if (crnt_node->left->type == OP && (int)crnt_node->left->value == MORE)
                {
                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->left);

                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->right);

                    fprintf (file_nasm, "\njb end_if%lu:\n", num_if);
                }
                else
                {
                    RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                    fprintf (file_nasm, "\npush 0\n");

                    fprintf (file_nasm, "\nje end_if%lu:\n", num_if);
                }

                fprintf (file_nasm, "; action\n");

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\nend_if%lu:\n", num_if);

                fprintf (file_nasm, "; -------end-if-------------------------\n");

                break;
            }
            case EQU:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\npop ");

                fprintf (file_nasm, "[%lu] \t; %s\n", (size_t)crnt_node->left->value, program->nametable[(int)crnt_node->left->value].name);

                break;
            }
            case ADD:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\nadd\n");

                break;
            }
            case SUB:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\nsub\n");

                break;
            }
            case MUL:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\nmul\n");

                break;
            }
            case DIV:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\ndiv\n");

                break;
            }
            default:
            {
                fprintf (stderr, YEL "ERROR: RecursiveMakeNasm unknown operator\n" RESET);

                exit (0);
            }
        }
    }
    else if (crnt_node->type == NUM)
    {
        fprintf (file_nasm, "\npush %d\n", (int)crnt_node->value);

        return;
    }
    else if (crnt_node->type == ID)
    {
        fprintf (file_nasm, "\npush [%lu] \t;%s\n", (size_t)crnt_node->value, program->nametable[(int)crnt_node->value].name);

        return;
    }
}
