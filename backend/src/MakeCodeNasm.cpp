#include <stdio.h>
#include <stdlib.h>

#include "../../common/hdr/Config.h"
#include "../../common/hdr/colors.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/MakeCodeNasm.h"

#define PrintTabsForComments fprintf(file_nasm, "\t\t\t\t\t\t\t\t\t\t")
#define PrintTabsForCommentsPop fprintf(file_nasm, "   \t\t\t\t\t\t\t\t")
#define PrintTabsForCommentsPush fprintf(file_nasm, "  \t\t\t\t\t\t\t\t")

void MakeNasmCode (tree_t* program)
{
    printf (GRN "MakeNasmCode started\n" RESET);

    FILE* file_nasm = fopen ("Nasm_file.s", "wt");

    if (file_nasm == NULL)
    {
        fprintf (stderr, "ERROR: MakeNasm can't open Nasm_file to write code\n");

        exit (0);
    }
    fprintf (file_nasm, ";--------------------------------------------------------------------------------------------------\n");
    fprintf (file_nasm, ";                           Programming language\n");
    fprintf (file_nasm, ";                         (c) 2025 Muratov Artyom\n");
    fprintf (file_nasm, ";--------------------------------------------------------------------------------------------------\n");

    fprintf (file_nasm, "section .text\n\n");

    fprintf (file_nasm, "start:\n");

    RecursiveMakeNasm (program, file_nasm, program->root);

    fprintf (file_nasm, "\n\thlt\n");

    fprintf (file_nasm, "\nsection .note.GNU-stack\n");

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

                fprintf (file_nasm, "\n\thlt");

                break;
            }
            case PRNT:
            {
                n_operator++;

                BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

                RecursiveMakeNasm (program, file_nasm, crnt_node->left );

                fprintf (file_nasm, "\n\tout");

                break;
            }
            case INPT:
            {
                n_operator++;

                BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

                fprintf (file_nasm, "\n\tin");

                fprintf (file_nasm, "\n\tpop ");

                fprintf (file_nasm, "[%lu]", (size_t)crnt_node->left->value);

                PrintTabsForCommentsPop;
                fprintf (file_nasm, "; %s\n", program->nametable[(int)crnt_node->left->value].name);

                break;
            }
            case SQRT:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                fprintf (file_nasm, "\n\tsqrt");

                break;
            }
            case IF:
            {
                n_operator++;

                size_t num_if = n_operator;

                BACK_DBG fprintf (stderr, GRN "operator = %s\n" RESET, KeyFromEnum ((int)crnt_node->value));

                fprintf (file_nasm, "\n; -------start-if-%lu-----------------------\n", num_if);

                fprintf (file_nasm, "\n; test-%lu\n", num_if);

                if (crnt_node->left->type == OP && (int)crnt_node->left->value == LESS)
                {
                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->left);

                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->right);

                    fprintf (file_nasm, "\n\tja end_if%lu:", num_if);
                }
                else if (crnt_node->left->type == OP && (int)crnt_node->left->value == MORE)
                {
                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->left);

                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->right);

                    fprintf (file_nasm, "\n\tjb end_if%lu:", num_if);
                }
                else
                {
                    RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                    fprintf (file_nasm, "\n\tpush 0");

                    fprintf (file_nasm, "\nje end_if%lu:", num_if);
                }

                fprintf (file_nasm, "\n; action-%lu\n", num_if);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\n\tend_if%lu:", num_if);

                fprintf (file_nasm, "\n; -------end-if-%lu-------------------------\n", num_if);

                break;
            }
            case WHILE:
            {
                n_operator++;

                size_t num_while = n_operator;

                BACK_DBG fprintf (stderr, GRN "operator = %s\n" RESET, KeyFromEnum ((int)crnt_node->value));

                fprintf (file_nasm, "\n; -------start-while-%lu-----------------------\n", num_while);

                fprintf (file_nasm, "\n; test-%lu\n", num_while);

                if (crnt_node->left->type == OP && (int)crnt_node->left->value == LESS)
                {
                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->left);

                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->right);

                    fprintf (file_nasm, "\n\tja end_while%lu:", num_while);
                }
                else if (crnt_node->left->type == OP && (int)crnt_node->left->value == MORE)
                {
                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->left);

                    RecursiveMakeNasm (program, file_nasm, crnt_node->left->right);

                    fprintf (file_nasm, "\n\tjb end_while%lu:", num_while);
                }
                else
                {
                    RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                    fprintf (file_nasm, "\n\tpush 0");

                    fprintf (file_nasm, "\n\tje end_while%lu:", num_while);
                }

                fprintf (file_nasm, "\n; action-%lu\n", num_while);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\nend_while%lu:", num_while);

                fprintf (file_nasm, "\n; -------end-while-%lu------------------------\n", num_while);

                break;
            }
            case EQU:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\n\tpop ");

                fprintf (file_nasm, "[%lu]", (size_t)crnt_node->left->value);

                PrintTabsForCommentsPop;
                fprintf (file_nasm, "; %s\n", program->nametable[(int)crnt_node->left->value].name);

                break;
            }
            case ADD:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\n\tadd");

                break;
            }
            case SUB:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\n\tsub");

                break;
            }
            case MUL:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\n\tmul");

                break;
            }
            case DIV:
            {
                n_operator++;

                RecursiveMakeNasm (program, file_nasm, crnt_node->left);

                RecursiveMakeNasm (program, file_nasm, crnt_node->right);

                fprintf (file_nasm, "\n\tdiv");

                break;
            }
            default:
            {
                fprintf (stderr, YEL "ERROR: RecursiveMakeNasm unknown operator\n" RESET);

                exit (0);
            }
        }

        PrintTabsForComments;
        fprintf (file_nasm, ";number operator %lu ", n_operator);
    }
    else if (crnt_node->type == NUM)
    {
        fprintf (file_nasm, "%d", (int)crnt_node->value);

        return;
    }
    else if (crnt_node->type == ID)
    {
        fprintf (file_nasm, "mov rax, [%lu]", (size_t)crnt_node->value);

        PrintTabsForCommentsPush;
        fprintf (file_nasm, "; %s\n", program->nametable[(int)crnt_node->value].name);

        return;
    }
}

