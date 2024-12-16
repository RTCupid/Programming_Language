#include <stdio.h>

#include "../../hdr/ProgramFunc.h"
#include "../../hdr/DumpProgram.h"
#include "../../hdr/Enum.h"
#include "../hdr/WriteProgramFile.h"
#include "../../hdr/DSL.h"
#include "../../hdr/colors.h"

int main ()
{
    printf (MAG "Start program\n" RESET);

    printf (RED "'*' = %d\n"
                "'=' = %d\n"
                "';' = %d\n"
                "'%c' = 54\n" RESET, '*', '=', ';', 54);

    tree_t program = {};

    ProgramCtor (&program, FRONTEND);

    printf (MAG "expr.root = %p\n" RESET, program.root);

    ProgramGraphviz (&program, FRONTEND);

    DiffDump (&program, FRONTEND);

    FILE* base_file = fopen ("Program_file.txt", "wt");

    WriteNameTable (&program, base_file);

    WriteBase (&program, program.root, base_file, 1);

    ProgramDtor (&program);

    return 0;
}
