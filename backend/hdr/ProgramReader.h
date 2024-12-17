#ifndef PROGRAMREADER_H
#define PROGRAMREADER_H

node_t* MakeProgram (tree_t* program, const char* namefile);

node_t* RunProgram  (tree_t* program, FILE* base_file);

size_t  NodeType    (char* value);
#endif
