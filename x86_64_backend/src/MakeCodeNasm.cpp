#include <stdio.h>
#include <stdlib.h>

#include "../../common/hdr/Config.h"
#include "../../common/hdr/colors.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/MakeCodeNasm.h"

//---------------------------------------------------------------------------------------

static err_t ProcessFUNC    (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessDEF     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessRET     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessCALL    (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order);

static err_t ProcessNUM     (FILE* file_nasm, node_t* crnt_node, order_t variable_order);

static err_t ProcessID      (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order);

static err_t ProcessSMC     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessEND     (FILE* file_nasm);

static err_t ProcessPRNT    (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessINPT    (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessSQRT    (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order);

static err_t ProcessIF      (tree_t* program, FILE* file_nasm, node_t* crnt_node, size_t num_if);

static err_t ProcessWHILE   (tree_t* program, FILE* file_nasm, node_t* crnt_node, size_t num_while);

static err_t ProcessEQU     (tree_t* program, FILE* file_nasm, node_t* crnt_node);

static err_t ProcessADD     (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order);

static err_t ProcessSUB     (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order);

static err_t ProcessMUL     (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order);

static err_t ProcessDIV     (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order);

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

    fprintf (file_nasm, "global  _start\n\n");

	fprintf (file_nasm, "%%INCLUDE \"stdlib.s\"\n\n");

    fprintf (file_nasm, "section .text\n");

    fprintf (file_nasm, "\n_start:\n");

    fprintf (file_nasm, "\n\tand rsp, -16");

    RecursiveMakeNasm (program, file_nasm, program->root);

    fprintf (file_nasm, "\n\n%-54s; exit (0)", "call _my_hlt");

    fprintf (file_nasm, "\n;--------------------------------------------------------------------------------------------------\n");

    fprintf (file_nasm, "\nsection .data\n");

    MakeSectionData (program, file_nasm);

    fprintf (file_nasm, "\n;--------------------------------------------------------------------------------------------------\n");

    fprintf (file_nasm, "\nsection .note.GNU-stack\n");

    printf (GRN "MakeNasmCode completed \n" RESET);
}

//---------------------------------------------------------------------------------------

void MakeSectionData (tree_t* program, FILE* file_nasm)
{
    for (size_t index = 0; index < program->nametable_id; index++)
    {
        if (program->nametable[index].type_id == TYPE_GLOBAL)
        {
            fprintf (file_nasm, "\n%s: dq 0", program->nametable[index].name);
        }
    }
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
            case FUNC:
            {
                n_operator++;

                ProcessFUNC (program, file_nasm, crnt_node);

                break;
            }
            case DEF:
            {
                n_operator++;

                ProcessDEF (program, file_nasm, crnt_node);

                break;
            }
            case RET:
            {
                n_operator++;

                ProcessRET (program, file_nasm, crnt_node);

                break;
            }
            case CALL:
            {
                n_operator++;

                ProcessCALL (program, file_nasm, crnt_node, variable_order);

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

                ProcessSQRT (program, file_nasm, crnt_node, variable_order);

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

                ProcessADD (program, file_nasm, crnt_node, variable_order);

                break;
            }
            case SUB:
            {
                n_operator++;

                ProcessSUB (program, file_nasm, crnt_node, variable_order);

                break;
            }
            case MUL:
            {
                n_operator++;

                ProcessMUL (program, file_nasm, crnt_node, variable_order);

                break;
            }
            case DIV:
            {
                n_operator++;

                ProcessDIV (program, file_nasm, crnt_node, variable_order);

                break;
            }
            default:
            {
                fprintf (stderr, YEL "ERROR: RecursiveMakeNasm unknown operator\n" RESET);

                exit (0);
            }
        }

        fprintf (file_nasm, " ; number operator %lu ", n_operator);
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

static err_t ProcessFUNC (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    char buffer[100] = {};

    fprintf (file_nasm, "\n\n;--------------------------------------------------------------------------------------------------");

    fprintf (file_nasm, "\n;\t%s:", program->nametable[(size_t) crnt_node->left->value].name);

    if (program->nametable[(size_t) crnt_node->left->value].argument == WITH_ARGUMENT)
    {
        fprintf (file_nasm, "\n;\tEntry: %s = [rbp + 8]", program->nametable[(size_t) crnt_node->right->value].name);
    }

    fprintf (file_nasm, "\n;--------------------------------------------------------------------------------------------------");

    snprintf (buffer, sizeof(buffer), "%s:", program->nametable[(size_t) crnt_node->left->value].name);

    fprintf(file_nasm, "\n\n%-54s; it is definition of %s ", buffer, program->nametable[(size_t) crnt_node->left->value].name);

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessDEF (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left);

    fprintf(file_nasm, "\n\n\t%-50s; rbp = rsp, save old value of rsp", "mov rbp, rsp");

    fprintf(file_nasm, "\n\n\t%-50s; [rbp] = address for return", " ");

    if (program->nametable[(size_t) crnt_node->left->left->value].argument == WITH_ARGUMENT)
    {
        fprintf(file_nasm, "\n\n\t%-50s; [rbp + 8] = function's argument", " ");
    }

    RecursiveMakeNasm (program, file_nasm, crnt_node->right);

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessRET (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

    fprintf(file_nasm, "\n\n\t%-50s; rsp = rbp, back old value of rsp", "mov rsp, rbp");

    fprintf (file_nasm, "\n\n\t%-50s; return;", "ret");

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessCALL (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    char buffer[100] = {};

    RecursiveMakeNasm (program, file_nasm, crnt_node->right, FIRST_EXPR);

    fprintf(file_nasm, "\n\n\t%-50s; reserved 8 byte for argument", "sub rsp, 8");

    fprintf(file_nasm, "\n\n\t%-50s; rax => [rsp], make stack frame;", "mov [rsp], rax");

    snprintf (buffer, sizeof(buffer), "call %s", program->nametable[(size_t) crnt_node->left->value].name);

    fprintf(file_nasm, "\n\n\t%-50s; %s (rax);", buffer, program->nametable[(size_t) crnt_node->left->value].name);

    fprintf(file_nasm, "\n\n\t%-50s; clean stack frame;", "add rsp, 8");

    if (variable_order == SECOND_EXPR)
    {
        fprintf(file_nasm, "\n\n\t%-50s; rdx = rax", "mov rdx, rax");
    }

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessNUM (FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    char buffer[100] = {};

    if (variable_order == FIRST_EXPR)
    {
        snprintf (buffer, sizeof(buffer), "mov rax, %d", (int)crnt_node->value);

        fprintf(file_nasm, "\n\n\t%-50s; rax = %d ", buffer, (int)crnt_node->value);
    }
    else if (variable_order == SECOND_EXPR)
    {
        snprintf (buffer, sizeof(buffer), "mov rdx, %d", (int)crnt_node->value);

        fprintf(file_nasm, "\n\t%-50s; rdx = %d ", buffer, (int)crnt_node->value);
    }
    else
    {
        fprintf (stderr, RED "unknown variable_order in ProcessNUM" RESET);
    }

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessID (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    char buffer[100] = {};

    if (variable_order == FIRST_EXPR)
    {
        snprintf (buffer, sizeof(buffer), "mov rax, [%s]", program->nametable[(int)crnt_node->value].name);

        fprintf(file_nasm, "\n\n\t%-50s; rax = %s ", buffer, program->nametable[(int)crnt_node->value].name);
    }
    else if (variable_order == SECOND_EXPR)
    {
        snprintf (buffer, sizeof(buffer), "mov rdx, [%s]", program->nametable[(int)crnt_node->value].name);

        fprintf(file_nasm, "\n\t%-50s; rdx = %s ", buffer, program->nametable[(int)crnt_node->value].name);
    }
    else
    {
        fprintf (stderr, RED "unknown variable_order in ProcessID" RESET);
    }

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
    fprintf (file_nasm, "\n\n\t%-50s; exit (0)", "call _my_hlt");

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessPRNT (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

    RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

    fprintf (file_nasm, "\n\n\t%-50s; print (eax)", "call _my_print");

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessINPT (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    char buffer[100] = {};

    BACK_DBG fprintf (stderr, "operator = %s\n", KeyFromEnum ((int)crnt_node->value));

    fprintf (file_nasm, "\n\n\t%-50s; input(%s); rax = input ", "call _my_input", program->nametable[(int)crnt_node->left->value].name);

    snprintf (buffer, sizeof(buffer), "mov [%s], rax", program->nametable[(int)crnt_node->left->value].name);

    fprintf(file_nasm, "\n\t%-50s; [%s] = rax ", buffer, program->nametable[(int)crnt_node->left->value].name);

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessSQRT (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

    fprintf (file_nasm, "\n\n\t%-50s; xmm0 = (double) rax", "cvtsi2sd xmm0, rax");

    fprintf (file_nasm, "\n\t%-50s; xmm1 = sqrt (xmm0)", "sqrtsd xmm1, xmm0");

    if (variable_order == FIRST_EXPR)
    {
        fprintf (file_nasm, "\n\t%-50s; rax  = xmm1", "cvtsd2si rax, xmm1");
    }
    else if (variable_order == SECOND_EXPR)
    {
        fprintf (file_nasm, "\n\t%-50s; rdx  = xmm1", "cvtsd2si rdx, xmm1");
    }
    else
    {
        fprintf (stderr, RED "unknown variable_order in ProcessSQRT" RESET);
    }

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessIF (tree_t* program, FILE* file_nasm, node_t* crnt_node, size_t num_if)
{
    char buffer[100] = {};

    BACK_DBG fprintf (stderr, GRN "operator = %s\n" RESET, KeyFromEnum ((int)crnt_node->value));

    fprintf (file_nasm, "\n;---start-if-%lu-----------------------------------------------------------------------------------", num_if);

    fprintf (file_nasm, "\n;   test-%lu", num_if);

    if (crnt_node->left->type == OP && (int)crnt_node->left->value == LESS)
    {
        RecursiveMakeNasm (program, file_nasm, crnt_node->left->left, FIRST_EXPR);

        RecursiveMakeNasm (program, file_nasm, crnt_node->left->right, SECOND_EXPR);

        fprintf(file_nasm, "\n\t%-50s; if (rax >= rdx)", "cmp rax, rdx");

        snprintf (buffer, sizeof(buffer), "jge  .end_if%lu", num_if);

        fprintf(file_nasm, "\n\t%-50s;  goto .end_if%lu", buffer, num_if);
    }
    else if (crnt_node->left->type == OP && (int)crnt_node->left->value == MORE)
    {
        RecursiveMakeNasm (program, file_nasm, crnt_node->left->left, FIRST_EXPR);

        RecursiveMakeNasm (program, file_nasm, crnt_node->left->right, SECOND_EXPR);

        fprintf(file_nasm, "\n\t%-50s; if (rax <= rdx)", "cmp rax, rdx");

        snprintf (buffer, sizeof(buffer), "jle  .end_if%lu", num_if);

        fprintf(file_nasm, "\n\t%-50s;  goto .end_if%lu", buffer, num_if);
    }
    else
    {
        RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

        fprintf(file_nasm, "\n\t%-50s;  if (rax = 0)", "test rax, rax");

        snprintf (buffer, sizeof(buffer), "je  .end_if%lu", num_if);

        fprintf(file_nasm, "\n\t%-50s;  goto .end_if%lu", buffer, num_if);
    }

    fprintf (file_nasm, "\n;   action-%lu", num_if);

    RecursiveMakeNasm (program, file_nasm, crnt_node->right);

    fprintf (file_nasm, "\n\n.end_if%lu:\n", num_if);

    fprintf (file_nasm, "\n;---end-if-%lu-------------------------------------------------------------------------------------", num_if);

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessWHILE (tree_t* program, FILE* file_nasm, node_t* crnt_node, size_t num_while)
{
    char buffer[100] = {};

    BACK_DBG fprintf (stderr, GRN "operator = %s\n" RESET, KeyFromEnum ((int)crnt_node->value));

    fprintf (file_nasm, "\n;---start-while-%lu--------------------------------------------------------------------------------", num_while);

    fprintf (file_nasm, "\n.start_while%lu:", num_while);

    fprintf (file_nasm, "\n;   test-%lu", num_while);

    if (crnt_node->left->type == OP && (int)crnt_node->left->value == LESS)
    {
        RecursiveMakeNasm (program, file_nasm, crnt_node->left->left, FIRST_EXPR);

        RecursiveMakeNasm (program, file_nasm, crnt_node->left->right, SECOND_EXPR);

        fprintf(file_nasm, "\n\t%-50s; if (rax < rdx)", "cmp rax, rdx");

        snprintf (buffer, sizeof(buffer), "jl  .end_while%lu", num_while);

        fprintf(file_nasm, "\n\t%-50s;  goto .end_while%lu", buffer, num_while);
    }
    else if (crnt_node->left->type == OP && (int)crnt_node->left->value == MORE)
    {
        RecursiveMakeNasm (program, file_nasm, crnt_node->left->left, FIRST_EXPR);

        RecursiveMakeNasm (program, file_nasm, crnt_node->left->right, SECOND_EXPR);

        fprintf(file_nasm, "\n\t%-50s; if (rax > rdx)", "cmp rax, rdx");

        snprintf (buffer, sizeof(buffer), "jg  .end_while%lu", num_while);

        fprintf(file_nasm, "\n\t%-50s;  goto .end_while%lu", buffer, num_while);
    }
    else
    {
        RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

        fprintf(file_nasm, "\n\t%-50s;  if (rax = 0)", "test rax, rax");

        snprintf (buffer, sizeof(buffer), "je  .end_while%lu", num_while);

        fprintf(file_nasm, "\n\t%-50s;  goto .end_while%lu", buffer, num_while);
    }

    fprintf (file_nasm, "\n;   action-%lu", num_while);

    RecursiveMakeNasm (program, file_nasm, crnt_node->right);

    snprintf (buffer, sizeof(buffer), "jmp short .start_while%lu", num_while);

    fprintf(file_nasm, "\n\t%-50s;  goto .start_while%lu", buffer, num_while);

    fprintf (file_nasm, "\n\n.end_while%lu:\n", num_while);

    fprintf (file_nasm, "\n;---end-while-%lu----------------------------------------------------------------------------------", num_while);

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessEQU (tree_t* program, FILE* file_nasm, node_t* crnt_node)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->right);

    char buffer[100] = {};

    snprintf (buffer, sizeof(buffer), "mov [%s], rax", program->nametable[(int)crnt_node->left->value].name);

    fprintf(file_nasm, "\n\t%-50s; %s = rax ", buffer, program->nametable[(int)crnt_node->left->value].name);

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessADD (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

    fprintf (file_nasm, "\n\t%-50s; rax => stack", "push rax");

    RecursiveMakeNasm (program, file_nasm, crnt_node->right, SECOND_EXPR);

    fprintf (file_nasm, "\n\t%-50s; rax <= stack", "pop rax");

    fprintf (file_nasm, "\n\t%-50s; rax += rdx", "add rax, rdx");

    if (variable_order == SECOND_EXPR)
    {
        fprintf (file_nasm, "\n\t%-50s; rdx = rax", "mov rdx, rax");
    }

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessSUB (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

    fprintf (file_nasm, "\n\t%-50s; rax => stack", "push rax");

    RecursiveMakeNasm (program, file_nasm, crnt_node->right, SECOND_EXPR);

    fprintf (file_nasm, "\n\t%-50s; rax <= stack", "pop rax");

    fprintf (file_nasm, "\n\t%-50s; rax -= rdx", "sub rax, rdx");

    if (variable_order == SECOND_EXPR)
    {
        fprintf (file_nasm, "\n\t%-50s; rdx = rax", "mov rdx, rax");
    }

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessMUL (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

    fprintf (file_nasm, "\n\t%-50s; rax => stack", "push rax");

    RecursiveMakeNasm (program, file_nasm, crnt_node->right, SECOND_EXPR);

    fprintf (file_nasm, "\n\t%-50s; rax <= stack", "pop rax");

    fprintf (file_nasm, "\n\t%-50s; rdi = rdx", "mov rdi, rdx");

    fprintf (file_nasm, "\n\t%-50s; rdx:rax = rax * rdi", "imul rdi");

    if (variable_order == SECOND_EXPR)
    {
        fprintf (file_nasm, "\n\t%-50s; rdx = rax", "mov rdx, rax");
    }

    return OK;
}

//---------------------------------------------------------------------------------------

static err_t ProcessDIV (tree_t* program, FILE* file_nasm, node_t* crnt_node, order_t variable_order)
{
    RecursiveMakeNasm (program, file_nasm, crnt_node->left, FIRST_EXPR);

    fprintf (file_nasm, "\n\t%-50s; rax => stack", "push rax");

    RecursiveMakeNasm (program, file_nasm, crnt_node->right, SECOND_EXPR);

    fprintf (file_nasm, "\n\t%-50s; rax <= stack", "pop rax");

    fprintf (file_nasm, "\n\t%-50s; rdi = rdx", "mov rdi, rdx");

    fprintf (file_nasm, "\n\t%-50s; rdx = 0", "cqo");

    fprintf (file_nasm, "\n\t%-50s; rax = rax:rdx / rdi, rdx = rax:rdx / rdi", "idiv rdi");

    if (variable_order == SECOND_EXPR)
    {
        fprintf (file_nasm, "\n\t%-50s; rdx = rax", "mov rdx, rax");
    }

    return OK;
}
