#include <stdio.h>

#include "../../common/hdr/ProgramFunc.h"
#include "../hdr/Optimization.h"
#include "../../common/hdr/Config.h"
#include "../../backend/hdr/ProgramReader.h"
#include "../../frontend/hdr/WriteProgramFile.h"
#include "../../common/hdr/DumpProgram.h"

int main ()
{
    tree_t mprogram = {};

    ProgramCtor  (&mprogram, MIDDLEEND);

    TreeCtor     (&mprogram, MIDDLEEND);

    OPT_DBG ProgramGraphviz (&mprogram, MIDDLEEND);

    mprogram.root = SimplifyExpr (&mprogram, mprogram.root);

    OPT_DBG ProgramGraphviz (&mprogram, MIDDLEEND);

    FILE* base_file = fopen ("Program_file.txt", "wb");

    WriteNameTable  (&mprogram, base_file, MIDDLEEND);

    WriteBase       (&mprogram, mprogram.root, base_file, 1);

    ProgramDtor     (&mprogram);

    return 0;
}
