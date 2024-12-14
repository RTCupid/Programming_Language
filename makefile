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

run: ./bin/front.exe ./bin/back.exe
	./bin/front.exe
	./bin/back.exe

./bin/front.exe: ./bin/ReсursiveReader.o ./bin/DumpProgram.o ./bin/WriteProgramFile.o ./bin/ProgramFunc.o ./bin/ProgramReader.o ./bin/fmain.o
	$(CC) ./bin/ReсursiveReader.o ./bin/DumpProgram.o ./bin/WriteProgramFile.o ./bin/ProgramFunc.o ./bin/ProgramReader.o ./bin/fmain.o -o ./bin/front.exe $(FLAGS)

./bin/back.exe: ./bin/ProgramReader.o ./bin/DumpProgram.o ./bin/MakeCodeAsm.o ./bin/bmain.o ./bin/ProgramFunc.o ./bin/ReсursiveReader.o
	$(CC) ./bin/ProgramReader.o ./bin/DumpProgram.o ./bin/MakeCodeAsm.o ./bin/ProgramFunc.o ./bin/ReсursiveReader.o ./bin/bmain.o -o ./bin/back.exe $(FLAGS)

./bin/DumpProgram.o: src/DumpProgram.cpp hdr/DumpProgram.h
	$(CC) -c ./src/DumpProgram.cpp -o ./bin/DumpProgram.o $(FLAGS)

./bin/ReсursiveReader.o: frontend/src/ReсursiveReader.cpp frontend/hdr/RecursiveReader.h hdr/DSL.h hdr/ProgramFunc.h hdr/Enum.h
	$(CC) -c ./frontend/src/ReсursiveReader.cpp -o ./bin/ReсursiveReader.o $(FLAGS)

./bin/WriteProgramFile.o: frontend/src/WriteProgramFile.cpp frontend/hdr/WriteProgramFile.h
	$(CC) -c ./frontend/src/WriteProgramFile.cpp -o ./bin/WriteProgramFile.o $(FLAGS)

./bin/fmain.o: frontend/src/main.cpp  frontend/hdr/WriteProgramFile.h hdr/DumpProgram.h hdr/Enum.h hdr/ProgramFunc.h
	$(CC) -c ./frontend/src/main.cpp -o ./bin/fmain.o $(FLAGS)

./bin/ProgramFunc.o: src/ProgramFunc.cpp hdr/Enum.h hdr/ProgramFunc.h frontend/hdr/RecursiveReader.h backend/hdr/ProgramReader.h
	$(CC) -c ./src/ProgramFunc.cpp -o ./bin/ProgramFunc.o $(FLAGS)

./bin/MakeCodeAsm.o: backend/src/MakeCodeAsm.cpp backend/hdr/MakeCodeAsm.h hdr/ProgramFunc.h hdr/Enum.h hdr/colors.h
	$(CC) -c ./backend/src/MakeCodeAsm.cpp -o ./bin/MakeCodeAsm.o $(FLAGS)

./bin/ProgramReader.o: backend/src/ProgramReader.cpp backend/hdr/ProgramReader.h
	$(CC) -c ./backend/src/ProgramReader.cpp -o ./bin/ProgramReader.o $(FLAGS)

./bin/bmain.o: backend/src/main.cpp hdr/Enum.h hdr/ProgramFunc.h hdr/DumpProgram.h
	$(CC) -c ./backend/src/main.cpp -o ./bin/bmain.o $(FLAGS)

clean:
	rm -f main ./bin/*.o ./bin/png/*.png
