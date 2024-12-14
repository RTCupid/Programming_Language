#ifndef DSL_H
    #define DSL_H

    #define  _ID(nametable_id)  NewNode(ID , nametable_id,  NULL, NULL)
    #define _NUM(value)         NewNode(NUM, value, NULL, NULL)

    #define  _ST(L,R)   NewNode(ST, SMC, L, R)
    #define _EQU(L,R)   NewNode(OP, EQU, L, R)
    #define _ADD(L,R)   NewNode(OP, ADD, L, R)
    #define _SUB(L,R)   NewNode(OP, SUB, L, R)
    #define _MUL(L,R)   NewNode(OP, MUL, L, R)
    #define _DIV(L,R)   NewNode(OP, DIV, L, R)
    #define _DEG(L,R)   NewNode(OP, DEG, L, R)
    #define _SIN(L)     NewNode(OP, SIN, L, NULL)
    #define _COS(L)     NewNode(OP, COS, L, NULL)
    #define  _LN(L)     NewNode(OP, LN,  L, NULL)

#endif
