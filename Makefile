CC = g++
LINUXFLAGSDEBUG = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations \
         -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
         -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd \
         -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel \
         -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default \
         -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers \
         -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow \
         -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla \
         -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr


CFLAGS = $(LINUXFLAGSDEBUG)

DEPFLAGS = -MT $@ -MMD -MP -MF ./build/dep/$*.d

FRONTEND_SOURCES = frontend/src/fmain.cpp \
                   frontend/src/RecursiveReader.cpp \
                   frontend/src/Tokenizer.cpp \
                   frontend/src/WriteProgramFile.cpp

BACKEND_SOURCES = backend/src/bmain.cpp \
                  backend/src/MakeCodeAsm.cpp \
                  backend/src/ProgramReader.cpp

COMMON_SOURCES = common/src/DumpProgram.cpp \
                 common/src/ProgramFunc.cpp

FRONTEND_OBJECTS = $(FRONTEND_SOURCES:frontend/src/%.cpp=build/obj/%.o)
BACKEND_OBJECTS = $(BACKEND_SOURCES:backend/src/%.cpp=build/obj/%.o)
COMMON_OBJECTS = $(COMMON_SOURCES:common/src/%.cpp=build/obj/%.o)

FRONTEND_DEPENDS = $(FRONTEND_OBJECTS:build/obj/%.o=build/dep/%.d)
BACKEND_DEPENDS = $(BACKEND_OBJECTS:build/obj/%.o=build/dep/%.d)
COMMON_DEPENDS = $(COMMON_OBJECTS:build/obj/%.o=build/dep/%.d)

INCLUDES = -I./frontend/hdr -I./common/hdr -I./backend/hdr

.PHONY: all build clean

all: build
	@echo -e "\033[33mCompilation complete. Run the programs using './build/bin/frontend' and './build/bin/backend'.\033[0m"

build: ./build/bin/frontend ./build/bin/backend

./build/bin/frontend: $(FRONTEND_OBJECTS) $(COMMON_OBJECTS) ./build/obj/ProgramReader.o
	@mkdir -p $(@D) ./build/dep
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

./build/bin/backend: $(BACKEND_OBJECTS) $(COMMON_OBJECTS) ./build/obj/Tokenizer.o ./build/obj/ReсursiveReader.o
	@mkdir -p $(@D) ./build/dep
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

./build/obj/%.o: frontend/src/%.cpp
	@mkdir -p $(@D) ./build/dep
	@if ! $(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@; then \
		rm -f $@; exit 1; \
	fi

./build/obj/%.o: backend/src/%.cpp
	@mkdir -p $(@D) ./build/dep
	@if ! $(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@; then \
		rm -f $@; exit 1; \
	fi

./build/obj/%.o: common/src/%.cpp
	@mkdir -p $(@D) ./build/dep
	@if ! $(CC) $(CFLAGS) $(INCLUDES) $(DEPFLAGS) -c $< -o $@; then \
		rm -f $@; exit 1; \
	fi

-include $(wildcard $(FRONTEND_DEPENDS)) $(wildcard $(BACKEND_DEPENDS)) $(wildcard $(COMMON_DEPENDS))

clean:
	@rm -rf ./build/bin/* ./build/obj/* ./build/dep/*
	@echo "Build files and dependencies removed"
