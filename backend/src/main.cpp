#include <stdio.h>

#include "../../hdr/Enum.h"
#include "../../hdr/ProgramFunc.h"
#include "../../hdr/DumpProgram.h"
#include "../hdr/MakeCodeAsm.h"

int main ()
{
    tree_t bprogram = {};

    ProgramCtor (&bprogram, BACKEND);

    TreeCtor (&bprogram, BACKEND);

    MakeAsmCode (&bprogram);

    ProgramGraphviz (&bprogram, BACKEND);

    ProgramDtor (&bprogram);
    return 0;
}
