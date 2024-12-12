#include <stdio.h>

#include "../ProgramFunc.h"
#include "MyLanguage.h"
#include "DumpProgram.h"
#include "WriteProgramFile.h"
#include "DSL.h"
#include "colors.h"

int main ()
{
    printf (MAG "Start program\n" RESET);

    tree_t program = {};

    ProgramCtor (&program);

    printf (MAG "expr.root = %p\n" RESET, program.root);

    ProgramGraphviz (&program);

    DiffDump (&program);

    FILE* base_file = fopen ("Program_file.txt", "wt");

    WriteBase (program.root, base_file, 1);

    ProgramDtor (&program);

    return 0;
}
