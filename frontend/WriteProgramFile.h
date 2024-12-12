#ifndef WRITE_PROGRAM_FILE_H
    #define WRITE_PROGRAM_FILE_H

    struct node_t;

    void    WriteBase   (node_t* crnt_node, FILE* base_file, int level);

    void    WriteTab    (int level, FILE* file);
#endif
