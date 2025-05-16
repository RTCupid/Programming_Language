#ifndef PROGRAMFUNC_H
#define PROGRAMFUNC_H

#include "./Enum.h"

enum err_t
{
    OK,
    ERROR,
};

typedef struct node_t
{
    size_t  type;
    double  value;
    node_t* left;
    node_t* right;
} node_t;

typedef struct identificator_t
{
    char*  start_pos;
    size_t n_symbols;
    char*  name;
} identificator_t;

struct token_t;

typedef struct keyword_t
{
    const char*  name_key;
    int          number_key;
    const char*  key_op;
} keyword_t;

const size_t N_KEYWORDS = 33;

const keyword_t keywords[N_KEYWORDS] =
{
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
    {"<",                   LESS, "<"},    //27
    {"while",               WHILE,"while"},//28
    {"call",                CALL, "call"}, //29
    {"def",                 DEF,  "def"},  //30
    {"func",                FUNC, "func"}, //31
    {"return",              RET,  "return"},//32
    {"give",                RET,  "return"},//33
};

typedef struct tree_t
{
    node_t*             root;
    node_t*             crnt_node;

    identificator_t*    nametable;
    size_t              nametable_id;

    token_t*            tokens;
    char*               data;

    int                 size_data;

    FILE*               log_file;
    FILE*               dbg_log_file;
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

//{
//! @brief   ProgramCtor    - function open log_files,
//!                           if mode is FRONTEND:  call func InputProgram to make array of program.
//!                           Also function call calloc for nametable.
//!
//! @param   program        - pointer to struct tree_t
//! @param   mode           - mode: FRONTEND or BACKEND
//!
//! @return
//!          true           - when construction structure of tree is completed
//! @code
//!          ProgramCtor (&program, BACKEND);
//! @endcode
//}
bool        ProgramCtor     (tree_t* program, modelang_t mode, const char* name_file_for_frontend = NULL);

//{
//! @brief   TreeCtor       - if mode is FRONTEND:  call func Tokenizer to make array of structs token_t,
//!                         - if mode is BACKEND:   call func MakeProgram to make tree of program.
//!
//! @param   program        - pointer to struct tree_t
//! @param   mode           - mode: FRONTEND or BACKEND
//!
//! @return
//!          true           - when construction structure of tree is completed
//! @code
//!          TreeCtor (&program, BACKEND);
//! @endcode
//}
bool        TreeCtor        (tree_t* program, modelang_t mode);

//{
//! @brief   ProgramDtor    - func to destroy elements of struct tree_t. Close log_files,
//!                           call ClearTree and ClearNameTable, free arrays.
//!
//! @param   program        - pointer to struct tree_t
//!
//! @return
//!          void
//! @code
//!          ProgramDtor (&program);
//! @endcode
//}
void        ProgramDtor     (tree_t* program);

//{
//! @brief   NewNode        - func to make new node_t node (base on calloc)
//!
//! @param   type           - type of new node (may be enum types_t)
//! @param   value          - new value
//! @param   left           - pointer to left  branch of new node
//! @param   right          - pointer to right branch of new node
//!
//! @return
//!          node_t*        - pointer to new node
//! @code
//!          NewNode (NUM, 666, NULL, NULL);
//! @endcode
//}
node_t*     NewNode         (size_t type, double value, node_t* left, node_t* right);

//{
//! @brief   ClearNameTable - func to clear nametable that from struct tree_t,
//!                           called from func ProgramDtor.
//!
//! @param   program        - pointer to struct tree_t
//!
//! @return
//!          void
//! @code
//!          ClearNameTable (&program);
//! @endcode
//}
void        ClearNameTable  (tree_t* program);

//{
//! @brief   ClearTree      - recursive func to clear tree with root in node (base on free)
//!
//! @param   node           - pointer to struct node_t
//!
//! @return
//!          void
//! @code
//!          ClearTree (&node);
//! @endcode
//}
void        ClearTree       (node_t* node);

//{
//! @brief   VerifyOpenFile - func to check opened file or not
//!
//! @param   file           - FILE* pointer to file
//! @param   namefunc       - const char* namefunc to write it if file didn't open
//!
//! @return
//!          void           - if file is open
//!          noreturn (assert) and print "ERROR:..." to consol - if file didn't open
//! @code
//!          VerifyOpenFile (base_file, "MakeProgram");
//! @endcode
//}
void        VerifyOpenFile  (FILE* file, const char* namefunc);

//{
//! @brief   KeyFromEnum    - find name key in keyword_t keywords
//!
//! @param   value          - number of key
//!
//! @return
//!          name of key    - if key is found
//!          NULL           - if it is unknown number of key
//! @code
//!          KeyFromEnum ((int)crnt_node->value));
//! @endcode
//}
const char* KeyFromEnum     (int value);
#endif
