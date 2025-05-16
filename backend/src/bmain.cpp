#include <stdio.h>
#include <string.h>

#include "../../common/hdr/Config.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/colors.h"
#include "../../common/hdr/ProgramFunc.h"
#include "../../common/hdr/DumpProgram.h"
#include "../hdr/MakeCodeAsm.h"
#include "../../x86_64_backend/hdr/MakeCodeNasm.h"

int main (int argc, char* argv[])
{
    tree_t bprogram = {};

    ProgramCtor     (&bprogram, BACKEND);

    TreeCtor        (&bprogram, BACKEND);

    BACK_DBG ProgramGraphviz (&bprogram, BACKEND);
    BACK_DBG DiffDump (&bprogram, BACKEND);

    // if (argc > 1)
    // {
    //     if (strcmp (argv[1], "NASM") == 0)
    //     {
    //         MakeNasmCode (&bprogram);
    //     }
    //     else
    //     {
    //         fprintf (stderr, RED "unknown mode\n" RESET );
    //     }
    // }
    // else
    // {
    //     MakeAsmCode  (&bprogram);
    // }

    ProgramDtor              (&bprogram);

    return 0;
}
