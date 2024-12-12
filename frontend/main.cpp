#include <stdio.h>

#include "../ProgramFunc.h"
#include "../DumpProgram.h"
#include "WriteProgramFile.h"
#include "../DSL.h"
#include "../colors.h"

int main ()
{
    printf (MAG "Start program\n" RESET);

    tree_t program = {};

    ProgramCtor (&program, FRONTEND);

    printf (MAG "expr.root = %p\n" RESET, program.root);

    ProgramGraphviz (&program, FRONTEND);

    DiffDump (&program);

    FILE* base_file = fopen ("Program_file.txt", "wt");

    WriteBase (program.root, base_file, 1);

    ProgramDtor (&program);

    return 0;
}
