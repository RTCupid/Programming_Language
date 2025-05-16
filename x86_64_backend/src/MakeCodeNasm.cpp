#include <stdio.h>
#include <stdlib.h>

#include "../../common/hdr/Config.h"
#include "../../common/hdr/colors.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/MakeCodeNasm.h"

//---------------------------------------------------------------------------------------

static err_t ProcessNUM     (FILE* file_nasm, node_t* crnt_node, order_t variable_order);

static err_t ProcessID      (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order);

static err_t ProcessSMC     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessEND     (FILE* file_nasm);

static err_t ProcessPRNT    (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessINPT    (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessSQRT    (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessIF      (tree_t* program, FILE* file_nasm, node_t* crnt_node, size_t num_if);

static err_t ProcessWHILE   (tree_t* program, FILE* file_nasm, node_t* crnt_node, size_t num_while);

static err_t ProcessEQU     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessADD     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessSUB     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessMUL     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessDIV     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

//---------------------------------------------------------------------------------------

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

    fprintf (file_nasm, "\n\tcall my_hlt\n");

    fprintf (file_nasm, "\nsection .note.GNU-stack\n");

    printf (GRN "MakeNasmCode completed\n" RESET);
}

//---------------------------------------------------------------------------------------

void RecursiveMakeNasm (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order)
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

                ProcessSMC (program, file_nasm, crnt_node);

                break;
            }
            case END:
            {
                n_operator++;

                ProcessEND (file_nasm);

                break;
            }
            case PRNT:
            {
                n_operator++;

                ProcessPRNT (program, file_nasm, crnt_node);

                break;
            }
            case INPT:
            {
                n_operator++;

                ProcessINPT (program, file_nasm, crnt_node);

                break;
            }
            case SQRT:
            {
                n_operator++;

                ProcessSQRT (program, file_nasm, crnt_node);

                break;
            }
            case IF:
            {
                n_operator++;

                ProcessIF (program, file_nasm, crnt_node, n_operator);

                break;
            }
            case WHILE:
            {
                n_operator++;

                ProcessWHILE (program, file_nasm, crnt_node, n_operator);

                break;
            }
            case EQU:
            {
                n_operator++;

                ProcessEQU (program, file_nasm, crnt_node);

                break;
            }
            case ADD:
            {
                n_operator++;

                ProcessADD (program, file_nasm, crnt_node);

                break;
            }
            case SUB:
            {
                n_operator++;

                ProcessSUB (program, file_nasm, crnt_node);

                break;
            }
            case MUL:
            {
                n_operator++;

                ProcessMUL (program, file_nasm, crnt_node);

                break;
            }
            case DIV:
            {
                n_operator++;

                ProcessDIV (program, file_nasm, crnt_node);

                break;
            }
            default:
            {
                fprintf (stderr, YEL "ERROR: RecursiveMakeNasm unknown operator\n" RESET);

                exit (0);
            }
        }

        fprintf (file_nasm, ";number operator %lu ", n_operator);
    }
    else if (crnt_node->type == NUM)
    {
        ProcessNUM (file_nasm, crnt_node, variable_order);

        return;
    }
    else if (crnt_node->type == ID)
    {
        ProcessID (program, file_nasm, crnt_node, variable_order);

        return;
    }
}

//---------------------------------------------------------------------------------------

static err_t ProcessNUM (FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    if (variable_order == FIRST_EXPR)
    {
        fprintf (file_nasm, "\n\tmov r8, %d", (int)crnt_node->value);
    }
    else if (variable_order == SECOND_EXPR)
    {
        fprintf (file_nasm, "\n\tmov r9, %d", (int)crnt_node->value);
    }

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessID (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    if (variable_order == FIRST_EXPR)
    {
        fprintf (file_nasm, "\n\tmov r8, [%lu]", (size_t)crnt_node->value);
    }
    else if (variable_order == SECOND_EXPR)
    {
        fprintf (file_nasm, "\n\tmov r9, [%lu]", (size_t)crnt_node->value);
    }

    fprintf (file_nasm, "; %s\n", program->nametable[(int)crnt_node->value].name);

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessSMC (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

    RecursiveMakeNasm (program, file_nasm, crnt_node->left );

    RecursiveMakeNasm (program, file_nasm, crnt_node->right);

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessEND (FILE* file_nasm)
{
    fprintf (file_nasm, "\n\tcall my_hlt");

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessPRNT (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

    RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

    fprintf (file_nasm, "\n\n\tcall my_print\n");


// ;-----------Dex-handler----------------------------------------------------------------------------
//
// case_4:                                                 ; handler %d
//                                                         ; rdx = index of next free cell in buffer
//             mov  rax, [rsp + OfsStrtArgInStk + 8 * r9]  ; rax = some argument from stack
//             inc  r9                                     ; r9++ <=> next argument
//
//             cmp  eax, 0                                 ; if (rax > 0) {
//             jg   DexPositiveParam                       ;     goto DexPositiveParam }
//
//             neg  eax                                    ; rax = -rax, find positive value of rax
//
//             mov  rbx, '-'
//             mov  [Buffer + rdx], bl                     ; Buffer[rdx] = '-'
//             inc  rdx                                    ; rdx++
//
// DexPositiveParam:
//
//             mov  r14, rdx                               ; save old value rdx in r14
//
//             mov  r12, 10                                ; r12 = 10, factor for div
//
//             xor  r13, r13                               ; r13 = 0, r13 = counter of dex digits
//
// NewDigitDex:
//
//             xor  rdx, rdx                               ; rdx = 0              -------------
//                                                         ;             number - | rdx : rax |
//                                                         ;                      -------------
//             div  r12                                    ; rax = rdx / 10, rdx = rdx % 10 (r12 = 10)
//
//             push rdx                                    ; rdx to stack, rdx - digit of number
//
//             inc  r13                                    ; r13++, r13 = counter of dex digits
//
//             cmp  rax, 0                                 ; if (rdx != 0) {
//
//             jne  NewDigitDex                            ; goto NewDigitDex }
//
// ;-----------Output-dex-number-from stack-to-buffer-------------------------------------------------
//
//             mov  rdx, r14                               ; rdx = r14, back old value of rdx
//             xor  rax, rax                               ; rax = 0
//
// NewDigitsInDexOutput:
//
//             pop  rax                                    ; take rax from stack
//                                                         ; rax = some digit of dex number
//             add  rax, 30h                               ; rax += 30h to find ASCII code of number
//
//             mov  [Buffer + rdx], al                     ; Buffer[rdx] = al
//             inc  rdx                                    ; rdx++
//
//             dec  r13                                    ; if (!--r13) {
//             jne  NewDigitsInDexOutput                   ;     goto NewDigitsInDexOutput }
//
//             ret
//
// ;--------------------------------------------------------------------------------------------------
// ; WriteBuf  function to write to console buffer
// ; Entry:    rsi = Buffer
// ;           rdx = number of symbols to write
// ; Exit:     rsi = Buffer
// ;           rdx = 0
// ; Destroy:  rax, rdx, rdi
// ;--------------------------------------------------------------------------------------------------
// WriteBuf:
//             mov  rax, 0x01                              ; write64 (rdi, rsi, rdx)
//             mov  rdi, 1                                 ; stdout
//
//             syscall
//
//             xor  rdx, rdx                               ; rdx = 0, to "clear" buffer
//
//             ret

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessINPT (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

    fprintf (file_nasm, "\n\tcall my_input");

    fprintf (file_nasm, "; %s\n", program->nametable[(int)crnt_node->left->value].name);

// in   al, 60h                    ; read data from PPI port

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessSQRT (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left);

    fprintf (file_nasm, "\n\tsqrt");

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessIF (tree_t* program, FILE* file_nasm, node_t* crnt_node, size_t num_if)
{
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

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessWHILE (tree_t* program, FILE* file_nasm, node_t* crnt_node, size_t num_while)
{
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

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessEQU (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->right);

    fprintf (file_nasm, "\n\tpop ");

    fprintf (file_nasm, "[%lu]", (size_t)crnt_node->left->value);

    fprintf (file_nasm, "; %s\n", program->nametable[(int)crnt_node->left->value].name);

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessADD (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

    RecursiveMakeNasm (program, file_nasm, crnt_node->right, SECOND_EXPR);

    fprintf (file_nasm, "\n\tadd r8, r9");

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessSUB (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left);

    RecursiveMakeNasm (program, file_nasm, crnt_node->right);

    fprintf (file_nasm, "\n\tsub");

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessMUL (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left);

    RecursiveMakeNasm (program, file_nasm, crnt_node->right);

    fprintf (file_nasm, "\n\tmul");

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessDIV (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left);

    RecursiveMakeNasm (program, file_nasm, crnt_node->right);

    fprintf (file_nasm, "\n\tdiv");

    return OK;
}
