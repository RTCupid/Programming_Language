#ifndef PROGRAMREADER_H
    #define PROGRAMREADER_H

    const size_t MAX_LEN_BUF = 20;

    node_t* MakeProgram (tree_t* program, const char* namefile);

    node_t* RunProgram  (tree_t* program, FILE* base_file);

    size_t  NodeType    (tree_t* expr, char* value);
#endif
