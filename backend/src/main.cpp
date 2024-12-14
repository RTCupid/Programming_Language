#include <stdio.h>

#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "../../hdr/DumpProgram.h"

int main ()
{
    tree_t bprogram = {};

    ProgramCtor (&bprogram, BACKEND);

    FILE* file_asm = RecursiveMakeAsm (&bprogram, bprogram.root);

    ProgramGraphviz (&bprogram, BACKEND);

    ProgramDtor (&bprogram);
    return 0;
}
