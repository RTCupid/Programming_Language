#ifndef DSL_H
    #define DSL_H

    #define _VAR        NewNode(VAR,     x, NULL, NULL)
    #define _NUM(value) NewNode(NUM, value, NULL, NULL)

    #define _ADD(L,R)   NewNode(OP, ADD, L, R)
    #define _SUB(L,R)   NewNode(OP, SUB, L, R)
    #define _MUL(L,R)   NewNode(OP, MUL, L, R)
    #define _DIV(L,R)   NewNode(OP, DIV, L, R)
    #define _DEG(L,R)   NewNode(OP, DEG, L, R)
    #define _SIN(L)     NewNode(OP, SIN, L, NULL)
    #define _COS(L)     NewNode(OP, COS, L, NULL)
    #define  _LN(L)     NewNode(OP, LN,  L, NULL)

#endif
