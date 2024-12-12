#include <stdio.h>

#include "../Enum.h"
#include "../ProgramFunc.h"
#include "../DumpProgram.h"

int main ()
{
    tree_t bprogram = {};

    ProgramCtor (&bprogram, BACKEND);

    ProgramGraphviz (&bprogram, BACKEND);

    ProgramDtor (&bprogram);
    return 0;
}
