#ifndef WRITE_PROGRAM_FILE_H
#define WRITE_PROGRAM_FILE_H

struct node_t;
struct tree_t;

void        WriteNameTable  (tree_t* program, FILE* file);

void        WriteBase       (tree_t* program, node_t* crnt_node, FILE* base_file, int level);

void        WriteTab        (int level, FILE* file);
#endif
