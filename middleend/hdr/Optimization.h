#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

struct tree_t;

node_t*     SimplifyExpr                (tree_t* expr, node_t* node);

node_t*     SimplifyConstExpr           (tree_t* expr, node_t* node, int* n_change_elems);

node_t*     RemoveNeutralExpr           (tree_t* expr, node_t* node, int* n_change_elems);

bool        IsNotConstExpression        (tree_t* expr, node_t* node);

double      Evaluate                    (node_t* node);

#endif
