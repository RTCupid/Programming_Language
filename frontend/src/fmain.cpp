#include <stdio.h>

#include "../../common/hdr/ProgramFunc.h"
#include "../../common/hdr/DumpProgram.h"
#include "../hdr/RecursiveReader.h"
#include "../../common/hdr/Enum.h"
#include "../../common/hdr/Config.h"
#include "../hdr/WriteProgramFile.h"
#include "../../common/hdr/DSL.h"
#include "../../common/hdr/colors.h"

int main ()
{
    printf (GRN "### Samurai Programming Language\n" RESET);

    tree_t program = {};

    ProgramCtor (&program, FRONTEND);

    TreeCtor    (&program, FRONTEND);

    program.root = GetG (&program);

    FRONT_DBG ProgramGraphviz (&program, FRONTEND);

    FILE* base_file = fopen ("Program_file.txt", "wb");

    WriteNameTable  (&program, base_file);

    WriteBase       (&program, program.root, base_file, 1);

    ProgramDtor     (&program);

    return 0;
}
