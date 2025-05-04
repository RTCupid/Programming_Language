#include <stdio.h>

#include "../../common/hdr/Config.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../../common/hdr/DumpProgram.h"
#include "../hdr/MakeCodeAsm.h"

int main ()
{
    tree_t bprogram = {};

    ProgramCtor     (&bprogram, BACKEND);

    TreeCtor        (&bprogram, BACKEND);

    BACK_DBG ProgramGraphviz (&bprogram, BACKEND);

    MakeAsmCode     (&bprogram);

    BACK_DBG ProgramGraphviz (&bprogram, BACKEND);

    ProgramDtor     (&bprogram);

    return 0;
}
