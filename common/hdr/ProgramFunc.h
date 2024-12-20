#ifndef PROGRAMFUNC_H
#define PROGRAMFUNC_H

#include "./Enum.h"

typedef struct node_t
{
    size_t type;
    double value;
    node_t* left;
    node_t* right;
} node_t;

typedef struct identificator_t
{
    char* start_pos;
    size_t n_symbols;
    char* name;
} identificator_t;

struct token_t;

typedef struct keyword_t
{
    const char*  name_key;
    int number_key;
    const char*  key_op;
} keyword_t;

const size_t N_KEYWORDS = 27;

const keyword_t keywords[N_KEYWORDS] =     //TD: only name_key without synonim
{                                          //TD: enum for keywords_number
    {"add",                 ADD,  "+"},    //1
    {"+",                   ADD,  "+"},    //2
    {"subtract",            SUB,  "-"},    //3
    {"-",                   SUB,  "-"},    //4
    {"multiply",            MUL,  "*"},    //5
    {"*",                   MUL,  "*"},    //6
    {"divide",              DIV,  "/"},    //7
    {"/",                   DIV,  "/"},    //8
    {"next",                SMC,  ";"},    //9
    {";",                   SMC,  ";"},    //10
    {"assign",              EQU,  "="},    //11
    {"=",                   EQU,  "="},    //12
    {"pong",                IF,   "if"},   //13
    {"if",                  IF,   "if"},   //14
    {"then_commit_seppuku", END,  "$"},    //15
    {"$",                   END,  "$"},    //16
    {"if_happens",          IF,   "if"},   //17
    {"(",                   LB,   "("},    //18
    {")",                   RB,   ")"},    //19
    {"{",                   RFB,  "{"},    //20
    {"}",                   LFB,  "}"},    //21
    {"write_about",         PRNT, "print"},//22
    {"print",               PRNT, "print"},//23
    {"input",               INPT, "input"},//24
    {"sqrt",                SQRT, "sqrt"}, //25
    {">",                   MORE, ">"},    //26
    {"<",                   LESS, "<"}     //27
};

typedef struct tree_t
{
    node_t* root;
    node_t* crnt_node;
    identificator_t* nametable;
    size_t nametable_id;
    token_t* tokens;
    char* data;
    int size_data;
    FILE* log_file;
    FILE* dbg_log_file;
} tree_t;

enum modelang_t
{
    FRONTEND = 0,
    BACKEND,
};

const size_t SIZE_NAMETABLE = 100;

const size_t MAX_LEN_BUF = 20;

const size_t SIZE_SIGNATURE = 20;

/*-ret-------func----------------------arguments-----------------------------------*/
bool        ProgramCtor     (tree_t* expr, modelang_t mode);

bool        TreeCtor        (tree_t* program, modelang_t mode);

void        ProgramDtor     (tree_t* expr);

node_t*     NewNode         (size_t type, double value, node_t* left, node_t* right);

void        ClearNameTable  (tree_t* program);

void        ClearTree       (node_t* node);

void        VerifyOpenFile  (FILE* file, const char* namefunc);

const char* KeyFromEnum     (int value);
#endif
