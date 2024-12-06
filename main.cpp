#include <stdio.h>

#include "MyLanguage.h"
#include "DumpProgram.h"
#include "DSL.h"
#include "colors.h"

int main ()
{
    printf (MAG "Start program\n" RESET);

    tree_t program = {};

    ProgramCtor (&program);

    printf (MAG "expr.root = %p\n" RESET, program.root);

    ProgramGraphviz (&program);

    ProgramDtor (&program);

    return 0;
}
