#include <stdio.h>
#include <stdlib.h>

#include "../../common/hdr/colors.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/DSL.h"
#include "../../common/hdr/Config.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/Optimization.h"

node_t* SimplifyExpr (tree_t* expr, node_t* node)
{
    int n_change_elems = 1;

    while (n_change_elems != 0)
    {
        n_change_elems = 0;

        node = SimplifyConstExpr (expr, node, &n_change_elems);

        OPT_DBG fprintf (stderr, GRN "n_change_elems const expr = %d\n" RESET, n_change_elems);

        node = RemoveNeutralExpr (expr, node, &n_change_elems);
    }
    return node;
}

node_t* RemoveNeutralExpr (tree_t* expr, node_t* crnt_node, int* n_change_elems)
{
    if (crnt_node == NULL)
    {
        return NULL;
    }
    if (crnt_node->type == OP)
    {
        if ((int) crnt_node->value == ADD || (int) crnt_node->value == SUB)
        {
            if ((int) crnt_node->left->type == NUM && (int) crnt_node->left->value == 0)
            {
                *n_change_elems += 1;

                node_t* ret_node = crnt_node->right;

                free (crnt_node->left);

                crnt_node->left = NULL;

                free (crnt_node);

                crnt_node       = NULL;

                return ret_node;
            }
            if ((int) crnt_node->left->type == NUM && (int) crnt_node->right->value == 0)
            {
                *n_change_elems += 1;

                node_t* ret_node = crnt_node->left;

                free (crnt_node->right);

                crnt_node->right = NULL;

                free (crnt_node);

                crnt_node = NULL;

                return ret_node;
            }
        }

        if ((int) crnt_node->value == MUL)
        {
            if ((int) crnt_node->left->type == NUM && (int) crnt_node->left->value == 1)
            {
                *n_change_elems += 1;

                node_t* ret_node = crnt_node->right;

                free (crnt_node->left);

                crnt_node->left = NULL;

                free (crnt_node);

                crnt_node = NULL;

                return ret_node;
            }
            if ((int) crnt_node->left->type == NUM && (int) crnt_node->right->value == 1)
            {
                *n_change_elems += 1;

                node_t* ret_node = crnt_node->left;

                free (crnt_node->right);

                crnt_node->right = NULL;

                free (crnt_node);

                crnt_node = NULL;

                return ret_node;
            }
            if (((int) crnt_node->left->type == NUM && (int) crnt_node->left->value == 0) || ((int) crnt_node->right->type == NUM && (int) crnt_node->right->value == 0))
            {
                ClearTree (crnt_node);

                *n_change_elems += 1;

                return NewNode (NUM, 0, NULL, NULL);
            }
        }

        crnt_node->left  = RemoveNeutralExpr (expr, crnt_node->left,  n_change_elems);

        crnt_node->right = RemoveNeutralExpr (expr, crnt_node->right, n_change_elems);
    }
    return crnt_node;
}

node_t* SimplifyConstExpr (tree_t* expr, node_t* node, int* n_change_elems)
{
    if (node->left == NULL || node->right == NULL)
    {
        return node;
    }

    if (!IsNotConstExpression (expr, node))
    {
        node_t* new_node = NewNode (NUM, Evaluate (node), NULL, NULL);

        ClearTree (node);

        *n_change_elems += 1;

        return new_node;
    }

    //left
    node->left  = SimplifyConstExpr (expr, node->left, n_change_elems );
    //right
    node->right = SimplifyConstExpr (expr, node->right, n_change_elems);
    return node;
}

bool IsNotConstExpression (tree_t* expr, node_t* crnt_node)
{
    if (!crnt_node->left && !crnt_node->right)
    {
        if ((int) crnt_node->type == ID)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (IsNotConstExpression (expr, crnt_node->left))
    {
        return true;
    }

    if (IsNotConstExpression (expr, crnt_node->right))
    {
        return true;
    }
    return false;
}

double Evaluate (node_t* node)
{
    if (node->type == NUM)
    {
        return node->value;
    }
    if (node->type == ID)
    {
        fprintf (stderr, RED "Evaluate with identificator\n" RESET);
        exit (0);
    }
    if (node->type == OP)
    {
        if ((int) node->value == ADD)
        {
            return Evaluate (node->left) + Evaluate (node->right);
        }
        if ((int) node->value == SUB)
        {
            return Evaluate (node->left) - Evaluate (node->right);
        }
        if ((int) node->value == MUL)
        {
            return Evaluate (node->left) * Evaluate (node->right);
        }
        if ((int) node->value == DIV)
        {
            return Evaluate (node->left) / Evaluate (node->right);
        }
    }
    return 0;
}
