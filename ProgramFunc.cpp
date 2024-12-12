#include <stdio.h>
#include <stdlib.h>

#include "Enum.h"
#include "ProgramFunc.h"

node_t* NewNode (size_t type, double value, node_t* left, node_t* right)
{
    node_t* node = (node_t*) calloc (1, sizeof (*node));

    node->type = type;

    if (node->type == ID)
    {
        node->value = (size_t)value;
    }
    else
    {
        node->value = value;
    }
    node->left = left;
    node->right = right;

    return node;
}

void ClearTree (node_t* node)
{
    if (!node)
    {
        return;
    }
    if (node->left)
    {
        ClearTree (node->left);
    }
    if (node->right)
    {
        ClearTree (node->right);
    }

    free (node);
    node = NULL;
}
