#ifndef ENUM_H
#define ENUM_H
enum types_t
{
    OP  = 1,
    NUM = 2,
    ID  = 3,
    ST  = 4,
};

enum type_id_t
{
    TYPE_NONE   = 0,
    TYPE_LOCAL  = 1,
    TYPE_FUNC   = 2,
    TYPE_GLOBAL = 3,
};

enum OP_t
{
    ADD = 1,
    SUB,
    MUL,
    DIV,
    SMC,
    EQU,
    IF,
    WHILE,
    SIN,
    COS,
    LN,
    END,
    RB,
    LB,
    RFB,
    LFB,
    PRNT,
    INPT,
    SQRT,
    MORE,
    LESS,
    DEF,
    FUNC,
    CALL,
    RET,
};
#endif
