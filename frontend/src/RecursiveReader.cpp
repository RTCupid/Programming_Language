#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "../../common/hdr/Config.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../../common/hdr/DSL.h"
#include "../../common/hdr/colors.h"
#include "../hdr/Tokenizer.h"
#include "../hdr/RecursiveReader.h"

bool status = true;

/*
Main
{General    ::= {OP {";" | "next"}}+ Hlt
{OP         ::= Assign | Func | Call | Ret | IF | Print | Input | Hlt

Everything
{Assign     ::= Id "=" Expr
{More       ::= Expr ">" Expr
{Less       ::= Expr "<" Expr
{IF         ::= "if_happen" "(" MORE | LESS | Expr ")"  "{" {OP { ";" | "next" } }+ "}"
{Print      ::= "write_about" "{" Expr "}"
{Input      ::= "input" "(" Id ")"
{While      ::= "while" "(" MORE | LESS | Expr ")" "{" {OP { ";" | "next" } }+ "}"
{Func       ::= Id "(" Id | " " ")" "{" {OP { ";" | "next" } }+ "}"
{Call       ::= Id "(" Id | " " ")" { ";" | "next" }
{Ret        ::= "return" Expr
{Hlt        ::= "then_commit_seppuku" | "$"

Equation
{Expr       ::= T {["+" | "add" | "-" | "subtract"] T}*
{T          ::= P {["*" | "multiply" | "/" | "divide"] P}*
{P          ::= "(" Expr ")" | Num | Id | "sqrt" "(" Expr ")" | Func "(" Expr ")"

Tokens
{Num        ::= NUM
{Id         ::= ID
*/

static size_t p = 0;

#define _CMP_OP(operator) (program->tokens[p].type == OP && strcmp(keywords[(int)program->tokens[p].value].key_op, operator) == 0)

//---------------------------------------------------------------------------------------

node_t* GetG (tree_t* program)
{
    printf (GRN "Start recursive descent\n" RESET);

    node_t* node      = _ST(NULL, NULL);

    node->left        = GetOp (program);

    node->right       = _ST(NULL, NULL);

    node_t* crnt_node = node->right;

    while (1)
    {
        if (_CMP_OP("$"))
        {
            fprintf (stderr, GRN "End recursive descent $\n" RESET);

            p++;

            break;
        }

        crnt_node->left  = GetOp (program);

        crnt_node->right = _ST(NULL, NULL);

        crnt_node        = crnt_node->right;
    }

    p++;

    return node;
}

//---------------------------------------------------------------------------------------

node_t* GetOp (tree_t* program)
{
    FRONT_DBG fprintf (stderr, CYN "Start GetOp\n" RESET);

    node_t* node = NULL;

    if (program->tokens[p].type == ID)
    {
        p++;

        if (_CMP_OP("="))
        {
            p--;

            FRONT_DBG fprintf (stderr, CYN "Start Assignment\n" RESET);

            node = GetA (program);
        }
        else if (_CMP_OP("("))
        {
            p--;

            FRONT_DBG fprintf (stderr, CYN "Start Function\n" RESET);

            node = GetFunc (program);
        }
        else
        {
            fprintf (stderr, YEL "ERROR:  in GetOp free ID\n" RESET);

            SintaxError (program, "GetOp");
        }
    }
    else if (_CMP_OP("return"))
    {
        FRONT_DBG fprintf (stderr, CYN "Start return\n" RESET);

        node = GetReturn (program);
    }
    else if (_CMP_OP("if"))
    {
        FRONT_DBG fprintf (stderr, CYN "Start if\n" RESET);

        node = GetIf (program);
    }
    else if (_CMP_OP("while"))
    {
        FRONT_DBG fprintf (stderr, CYN "Start while\n" RESET);

        node = GetWhile (program);
    }
    else if (_CMP_OP("print"))
    {
        FRONT_DBG fprintf (stderr, CYN "Start print\n" RESET);

        node = GetPrint (program);
    }
    else if (_CMP_OP("input"))
    {
        FRONT_DBG fprintf (stderr, CYN "Start input\n" RESET);

        node = GetInput (program);
    }
    else if (_CMP_OP("$"))
    {
        FRONT_DBG fprintf (stderr, CYN "Start Seppuku\n" RESET);

        node = _END();
    }
    else
    {
        fprintf (stderr, YEL "ERROR: in GetOp Unknown operator\n" RESET);

        SintaxError (program, "GetOp");
    }

    if (_CMP_OP(";"))
    {
        p++;
    }
    else if (_CMP_OP("$"))
    {
        p++;
    }
    else
    {
        fprintf (stderr, YEL "in GetOp: end token ISN'T \";\" and ISN'T \"$\"\n" RESET);

        SintaxError (program, "GetOp");
    }

    FRONT_DBG fprintf (stderr, MAG "End GetOp\n" RESET);

    return node;
}

//---------------------------------------------------------------------------------------

node_t* GetReturn (tree_t* program)
{
    node_t* return_node = NULL;

    if (_CMP_OP("return"))
    {
        p++;

        return_node = GetE (program);
    }
    else
    {
        fprintf (stderr, YEL "in GetReturn: token ISN'T \"return\"\n" RESET);

        SintaxError (program, "GetReturn");
    }

    return _RET(return_node);
}

//---------------------------------------------------------------------------------------

node_t* GetFunc (tree_t* program)
{
    node_t* new_left_node_def       = NULL;

    node_t* new_right_node_def      = NULL;

    node_t* argument_func_node      = NULL;

    node_t* identificator_func_node = NULL;

    if (program->tokens[p].type == ID)
    {
        identificator_func_node = _ID (program->tokens[p].value);

        program->nametable[(size_t) (program->tokens[p].value)].type_id = TYPE_FUNC;

        int number_func = (int) program->tokens[p].value;

        p++;

        if (_CMP_OP("("))
        {
            FRONT_DBG fprintf (stderr, CYN " \"(\"\n" RESET);
            p++;

            if (program->tokens[p].type == ID)
            {
                FRONT_DBG fprintf (stderr, CYN " function's argument = \"%lu\"\n" RESET, (size_t) (program->tokens[p].value));

                argument_func_node = GetE (program);

                program->nametable[(size_t) (number_func)].argument = WITH_ARGUMENT;
            }

            FRONT_DBG fprintf (stderr, GRN "end check argument\n" RESET);

            if (_CMP_OP(")"))
            {
                FRONT_DBG fprintf (stderr, CYN " \")\"\n" RESET);
                p++;

                if (_CMP_OP(";"))
                {
                    FRONT_DBG fprintf (stderr, CYN " \";\" - It is call function\n" RESET);

                    return _CALL(identificator_func_node, argument_func_node);
                }
                else if (_CMP_OP("{"))
                {
                    FRONT_DBG fprintf (stderr, CYN " \"{\" - It is function definition\n" RESET);
                    p++;

                    new_right_node_def        = _ST(NULL, NULL);

                    new_right_node_def->left  = GetOp (program);

                    new_right_node_def->right = _ST(NULL, NULL);

                    node_t* crnt_node         = new_right_node_def->right;

                    while (1)
                    {
                        if (_CMP_OP("}"))
                        {
                            FRONT_DBG fprintf (stderr, CYN " \"}\"\n" RESET);

                            p++;

                            break;
                        }

                        crnt_node->left  = GetOp (program);

                        crnt_node->right = _ST(NULL, NULL);

                        crnt_node        = crnt_node->right;
                    }
                }
                else
                {
                    fprintf (stderr, YEL "in GetFunc: token ISN'T \"{\"\n" RESET);

                    SintaxError (program, "GetFunc");
                }
            }
            else
            {
                fprintf (stderr, YEL "in GetFunc: token ISN'T \")\"\n" RESET);

                SintaxError (program, "GetFunc");
            }
        }
        else
        {
            fprintf (stderr, YEL "in GetFunc: token ISN'T \"(\"\n" RESET);

            SintaxError (program, "GetFunc");
        }
    }
    else
    {
        fprintf (stderr, YEL "in GetFunc: token ISN'T \"ID\"\n" RESET);

        SintaxError (program, "GetFunc");
    }

    new_left_node_def = _FUNC(identificator_func_node, argument_func_node);

    return _DEF(new_left_node_def, new_right_node_def);
}

//---------------------------------------------------------------------------------------

node_t* GetInput (tree_t* program)
{
    node_t* input_node = NULL;

    if (_CMP_OP("input"))
    {
        p++;

        if (_CMP_OP("("))
        {
            p++;

            if (program->tokens[p].type == ID)
            {
                input_node = _ID (program->tokens[p].value);

                program->nametable[(size_t) program->tokens[p].value].type_id = TYPE_GLOBAL;

                p++;

                if (_CMP_OP(")"))
                {
                    p++;
                }
                else
                {
                    fprintf (stderr, YEL "in GetInput: token ISN'T \")\"\n" RESET);

                    SintaxError (program, "GetInput");
                }
            }
            else
            {
                fprintf (stderr, YEL "in GetInput: token ISN'T ID\n" RESET);

                SintaxError (program, "GetInput");
            }
        }
        else
        {
            fprintf (stderr, YEL "in GetInput: token ISN'T \"input\"\n" RESET);

            SintaxError (program, "GetInput");
        }
    }
    else
    {
        fprintf (stderr, YEL "in GetInput: token ISN'T \"input\"\n" RESET);

        SintaxError (program, "GetInput");
    }

    return _INPUT(input_node);
}

node_t* GetPrint (tree_t* program)
{
    node_t* print_node = NULL;

    if (_CMP_OP("print"))
    {
        p++;

        if (_CMP_OP("{"))
        {
            p++;

            print_node = GetE (program);

            if (_CMP_OP("}"))
            {
                p++;
            }
            else
            {
                fprintf (stderr, YEL "in GetPrint: token ISN'T \"}\"\n" RESET);

                SintaxError (program, "GetPrint");
            }
        }
        else
        {
            fprintf (stderr, YEL "in GetPrint: token ISN'T \"{\"\n" RESET);

            SintaxError (program, "GetPrint");
        }
    }
    else
    {
        fprintf (stderr, YEL "in GetPrint: token ISN'T \"print\"\n" RESET);

        SintaxError (program, "GetPrint");
    }

    return _PRNT(print_node);
}

//---------------------------------------------------------------------------------------

node_t* GetIf (tree_t* program)
{
    node_t* condition_node       = NULL;

    node_t* left_condition_node  = NULL;

    node_t* right_condition_node = NULL;

    node_t* new_right_node       = NULL;

    if (_CMP_OP("if"))
    {
        FRONT_DBG fprintf (stderr, CYN "if\n" RESET);

        p++;

        if (_CMP_OP("("))
        {
            FRONT_DBG fprintf (stderr, CYN " \"(\"\n" RESET);

            p++;

            condition_node = GetE (program);

            if (_CMP_OP("<"))
            {
                FRONT_DBG fprintf (stderr, CYN " \"<\"\n" RESET);

                p++;

                left_condition_node  = condition_node;

                right_condition_node = GetE (program);

                condition_node       = _LESS(left_condition_node, right_condition_node);
            }
            else if (_CMP_OP(">"))
            {
                FRONT_DBG fprintf (stderr, CYN " \">\"\n" RESET);

                p++;

                left_condition_node  = condition_node;

                right_condition_node = GetE (program);

                condition_node       = _MORE(left_condition_node, right_condition_node);
            }

            if (_CMP_OP(")"))
            {
                p++;

                FRONT_DBG fprintf (stderr, CYN " \")\"\n" RESET);

                if (_CMP_OP("{"))
                {
                    p++;

                    FRONT_DBG fprintf (stderr, CYN " \"{\"\n" RESET);

                    new_right_node        = _ST(NULL, NULL);

                    new_right_node->left  = GetOp (program);

                    new_right_node->right = _ST(NULL, NULL);

                    node_t* crnt_node     = new_right_node->right;

                    while (1)
                    {
                        if (_CMP_OP("}"))
                        {
                            FRONT_DBG fprintf (stderr, CYN " \"}\"\n" RESET);

                            p++;

                            break;
                        }

                        crnt_node->left  = GetOp (program);

                        crnt_node->right = _ST(NULL, NULL);

                        crnt_node        = crnt_node->right;
                    }
                }
                else
                {
                    fprintf (stderr, YEL "in GetIf: token ISN'T \"{\"\n" RESET);

                    SintaxError (program, "GetIf");
                }
            }
            else
            {
                fprintf (stderr, YEL "in GetIf: token ISN'T \")\"\n" RESET);

                SintaxError (program, "GetIf");
            }
        }
        else
        {
            fprintf (stderr, YEL "in GetIf: token ISN'T \"(\"\n" RESET);

            SintaxError (program, "GetIf");
        }
    }
    else
    {
        fprintf (stderr, YEL "in GetIf: end token ISN'T '$'\n" RESET);

        SintaxError (program, "GetIf");
    }

    return _IF(condition_node, new_right_node);
}

//---------------------------------------------------------------------------------------

node_t* GetWhile (tree_t* program)
{
    node_t* condition_node       = NULL;

    node_t* left_condition_node  = NULL;

    node_t* right_condition_node = NULL;

    node_t* new_right_node       = NULL;

    if (_CMP_OP("while"))
    {
        FRONT_DBG fprintf (stderr, CYN "while\n" RESET);

        p++;

        if (_CMP_OP("("))
        {
            FRONT_DBG fprintf (stderr, CYN " \"(\"\n" RESET);

            p++;

            condition_node = GetE (program);

            if (_CMP_OP("<"))
            {
                FRONT_DBG fprintf (stderr, CYN " \"<\"\n" RESET);

                p++;

                left_condition_node  = condition_node;

                right_condition_node = GetE (program);

                condition_node       = _MORE(left_condition_node, right_condition_node);
            }
            else if (_CMP_OP(">"))
            {
                FRONT_DBG fprintf (stderr, CYN " \">\"\n" RESET);

                p++;

                left_condition_node  = condition_node;

                right_condition_node = GetE (program);

                condition_node       = _LESS(left_condition_node, right_condition_node);
            }

            if (_CMP_OP(")"))
            {
                p++;

                FRONT_DBG fprintf (stderr, CYN " \")\"\n" RESET);

                if (_CMP_OP("{"))
                {
                    p++;

                    FRONT_DBG fprintf (stderr, CYN " \"{\"\n" RESET);

                    new_right_node        = _ST(NULL, NULL);

                    new_right_node->left  = GetOp (program);

                    new_right_node->right = _ST(NULL, NULL);

                    node_t* crnt_node     = new_right_node->right;

                    while (1)
                    {
                        if (_CMP_OP("}"))
                        {
                            FRONT_DBG fprintf (stderr, CYN " \"}\"\n" RESET);

                            p++;

                            break;
                        }

                        crnt_node->left  = GetOp (program);

                        crnt_node->right = _ST(NULL, NULL);

                        crnt_node        = crnt_node->right;
                    }
                }
                else
                {
                    fprintf (stderr, YEL "in GetWhile: token ISN'T \"{\"\n" RESET);

                    SintaxError (program, "GetWhile");
                }
            }
            else
            {
                fprintf (stderr, YEL "in GetWhile: token ISN'T \")\"\n" RESET);

                SintaxError (program, "GetWhile");
            }
        }
        else
        {
            fprintf (stderr, YEL "in GetWhile: token ISN'T \"(\"\n" RESET);

            SintaxError (program, "GetWhile");
        }
    }
    else
    {
        fprintf (stderr, YEL "in GetWhile: end token ISN'T '$'\n" RESET);

        SintaxError (program, "GetWhile");
    }

    return _WHILE(condition_node, new_right_node);
}

//---------------------------------------------------------------------------------------

node_t* GetA (tree_t* program)
{
    node_t* new_right_node = NULL;

    node_t* new_left_node  = NULL;

    if (program->tokens[p].type == ID)
    {
        new_left_node = _ID (program->tokens[p].value);

        FRONT_DBG fprintf (stderr, CYN "in GetA: first token is ID\n" RESET);

        p++;

        if (_CMP_OP("="))
        {
            FRONT_DBG fprintf (stderr, CYN "in GetA: there is token '='\n" RESET);

            p++;
        }
        else
        {
            fprintf (stderr, YEL "in GetA: there ISN'T token '='\n" RESET);

            SintaxError (program, "GetA");
        }

        new_right_node = GetE (program);
    }
    else
    {
        fprintf (stderr, YEL "in GetA: first token ISN'T ID\n" RESET);

        SintaxError (program, "GetA");
    }

    return _EQU (new_left_node, new_right_node);
}

//---------------------------------------------------------------------------------------

node_t* GetE (tree_t* program)
{
    node_t* node = GetT (program);

    FRONT_DBG fprintf (stderr, GRN "in GetE Start check \"+\" or \"-\"\n" RESET);

    while (_CMP_OP("+") || _CMP_OP("-"))
    {
        FRONT_DBG fprintf (stderr, GRN "in GetE \"+\" or \"-\"\n" RESET);

        const char* op = keywords[(int)program->tokens[p].value].key_op;

        p++;

        node_t* new_node = GetT (program);

        if (strcmp (op, "+") == 0)
        {
            node = _ADD (
                        node,
                        new_node);
        }
        if (strcmp (op, "-") == 0)
        {
            node = _SUB (
                        node,
                        new_node);
        }
    }
    return node;
}

//---------------------------------------------------------------------------------------

node_t* GetT (tree_t* program)
{
    node_t* node = GetP (program);

    while (_CMP_OP("*") || _CMP_OP ("/"))
    {
        const char* op = keywords[(int)program->tokens[p].value].key_op;

        p++;

        node_t* new_node = GetP (program);

        if (strcmp (op, "*") == 0)
        {
            node = _MUL (node, new_node);
        }
        else if (strcmp (op, "/") == 0)
        {
            node = _DIV (node, new_node);
        }
    }

    return node;
}

//---------------------------------------------------------------------------------------

node_t* GetP (tree_t* program)
{
    if (_CMP_OP("("))
    {
        p++;

        node_t* node = GetE (program);

        if (!_CMP_OP(")"))
        {
            SintaxError (program, "GetP");
        }

        p++;

        return node;
    }
    if (_CMP_OP("sqrt"))
    {
        node_t* argument_node = NULL;

        p++;

        if (_CMP_OP("("))
        {
            p++;

            argument_node = GetE (program);

            if (_CMP_OP(")"))
            {
                p++;
            }
            else
            {
                printf (YEL "in GetP sqrt: token ISN'T \")\"\n" RESET);

                SintaxError (program, "GetP sqrt");
            }
        }
        else
        {
            printf (YEL "in GetP sqrt: token ISN'T \"(\"\n" RESET);

            SintaxError (program, "GetP sqrt");
        }

        return _SQRT(argument_node);
    }
    if (program->tokens[p].type == ID)
    {
        FRONT_DBG fprintf (stderr, GRN "Start check ID in GetP\n" RESET);

        double token_value = program->tokens[p].value;

        p++;

        if (_CMP_OP("("))
        {
            p--;

            FRONT_DBG fprintf (stderr, CYN "Start Function\n" RESET);

            return GetFunc (program);
        }
        else
        {
            FRONT_DBG fprintf (stderr, CYN "It is free Id\n" RESET);

            return _ID (token_value);
        }
    }
    if (program->tokens[p].type == NUM)
    {
        FRONT_DBG fprintf (stderr, GRN "Start check NUM in GetP\n" RESET);

        double token_value = program->tokens[p].value;

        p++;

        return _NUM (token_value);
    }

    /*---else---*/
    SintaxError (program, "GetP");
    return NULL;
}

//---------------------------------------------------------------------------------------

[[noreturn]]
void SintaxError (tree_t* program, const char* name_func)
{
    fprintf   (program->dbg_log_file, "SYNTAX ERROR: %s: unknown token: token[%lu].type = ", name_func, p);

    PrintType (program, program->tokens[p]);

    fprintf   (program->dbg_log_file, " token[%lu].value = %g",        p, program->tokens[p].value);

    fprintf   (stderr, YEL            "SYNTAX ERROR: %s: unknown token: token[%lu].type = %d\n" RESET,
                                                                       name_func, p, program->tokens[p].type);

    fprintf   (stderr, YEL            "token[%lu].value = %g\n" RESET, p, program->tokens[p].value);

    if (program->tokens[p].type == ID)
    {
        fprintf (stderr, YEL "\"%.20s\"\n", program->nametable[(int)program->tokens[p].value].start_pos);
    }

    exit (0);
}


