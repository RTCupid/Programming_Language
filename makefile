CC = g++
FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ \
	-Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations \
	-Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion \
	-Wctor-dtor-privacy -Wempty-body -Wformat-nonliteral -Wformat-security \
	-Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd \
	-Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow \
	-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
	-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand \
	-Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers \
	-Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector \
	-fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wlarger-than=580192 -Wstack-usage=8192 -pie -fPIE -Werror=vla \
	-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,$\
	nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,$\
	signed-integer-overflow,undefined,unreachable,vla-bound,vptr

OBJ_DIR=./build/obj
BIN_DIR=./build/bin

run: ${BIN_DIR}/front.exe ${BIN_DIR}/back.exe ./processor/Asm.exe ./processor/Run.exe
	${BIN_DIR}/front.exe
	${BIN_DIR}/back.exe
	./processor/Asm.exe Asm_file.txt
	./processor/Run.exe Programm_code.txt

${BIN_DIR}/front.exe: $(OBJ_DIR)/ReсursiveReader.o $(OBJ_DIR)/Tokenizer.o $(OBJ_DIR)/DumpProgram.o $(OBJ_DIR)/WriteProgramFile.o $(OBJ_DIR)/ProgramFunc.o $(OBJ_DIR)/ProgramReader.o $(OBJ_DIR)/fmain.o
	$(CC) $(OBJ_DIR)/ReсursiveReader.o $(OBJ_DIR)/Tokenizer.o $(OBJ_DIR)/DumpProgram.o $(OBJ_DIR)/WriteProgramFile.o $(OBJ_DIR)/ProgramFunc.o $(OBJ_DIR)/ProgramReader.o $(OBJ_DIR)/fmain.o -o ${BIN_DIR}/front.exe $(FLAGS)

${BIN_DIR}/back.exe: $(OBJ_DIR)/ProgramReader.o $(OBJ_DIR)/Tokenizer.o $(OBJ_DIR)/DumpProgram.o $(OBJ_DIR)/MakeCodeAsm.o $(OBJ_DIR)/bmain.o $(OBJ_DIR)/ProgramFunc.o $(OBJ_DIR)/ReсursiveReader.o
	$(CC) $(OBJ_DIR)/ProgramReader.o $(OBJ_DIR)/Tokenizer.o $(OBJ_DIR)/DumpProgram.o $(OBJ_DIR)/MakeCodeAsm.o $(OBJ_DIR)/ProgramFunc.o $(OBJ_DIR)/ReсursiveReader.o $(OBJ_DIR)/bmain.o -o ${BIN_DIR}/back.exe $(FLAGS)

$(OBJ_DIR)/DumpProgram.o: common/src/DumpProgram.cpp common/hdr/DumpProgram.h
	$(CC) -c ./common/src/DumpProgram.cpp -o $(OBJ_DIR)/DumpProgram.o $(FLAGS)

$(OBJ_DIR)/ReсursiveReader.o: frontend/src/ReсursiveReader.cpp frontend/hdr/RecursiveReader.h common/hdr/DSL.h common/hdr/ProgramFunc.h common/hdr/Enum.h
	$(CC) -c ./frontend/src/ReсursiveReader.cpp -o $(OBJ_DIR)/ReсursiveReader.o $(FLAGS)

$(OBJ_DIR)/Tokenizer.o: frontend/src/Tokenizer.cpp frontend/hdr/Tokenizer.h common/hdr/Enum.h
	$(CC) -c ./frontend/src/Tokenizer.cpp -o $(OBJ_DIR)/Tokenizer.o $(FLAGS)

$(OBJ_DIR)/WriteProgramFile.o: frontend/src/WriteProgramFile.cpp frontend/hdr/WriteProgramFile.h
	$(CC) -c ./frontend/src/WriteProgramFile.cpp -o $(OBJ_DIR)/WriteProgramFile.o $(FLAGS)

$(OBJ_DIR)/fmain.o: frontend/src/main.cpp  frontend/hdr/WriteProgramFile.h common/hdr/DumpProgram.h common/hdr/Enum.h common/hdr/ProgramFunc.h
	$(CC) -c ./frontend/src/main.cpp -o $(OBJ_DIR)/fmain.o $(FLAGS)

$(OBJ_DIR)/ProgramFunc.o: common/src/ProgramFunc.cpp common/hdr/Enum.h common/hdr/ProgramFunc.h frontend/hdr/RecursiveReader.h frontend/hdr/Tokenizer.h backend/hdr/ProgramReader.h
	$(CC) -c ./common/src/ProgramFunc.cpp -o $(OBJ_DIR)/ProgramFunc.o $(FLAGS)

$(OBJ_DIR)/MakeCodeAsm.o: backend/src/MakeCodeAsm.cpp backend/hdr/MakeCodeAsm.h common/hdr/ProgramFunc.h common/hdr/Enum.h common/hdr/colors.h
	$(CC) -c ./backend/src/MakeCodeAsm.cpp -o $(OBJ_DIR)/MakeCodeAsm.o $(FLAGS)

$(OBJ_DIR)/ProgramReader.o: backend/src/ProgramReader.cpp backend/hdr/ProgramReader.h
	$(CC) -c ./backend/src/ProgramReader.cpp -o $(OBJ_DIR)/ProgramReader.o $(FLAGS)

$(OBJ_DIR)/bmain.o: backend/src/main.cpp common/hdr/Enum.h common/hdr/ProgramFunc.h common/hdr/DumpProgram.h
	$(CC) -c ./backend/src/main.cpp -o $(OBJ_DIR)/bmain.o $(FLAGS)

clean:
	rm -f main $(OBJ_DIR)/*.o $(OBJ_DIR)/png/*.png
