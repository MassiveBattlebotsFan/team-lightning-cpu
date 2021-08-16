BUILD = build
CPU_SRC = cpu_src
ASM_SRC = pl2_assembler
HEADERS = $(CPU_SRC)/headers
CXXFLAGS = -std=c++2a
DBS = $(ASM_SRC)/default_opcode_dbs
ifeq ($(OS), Windows_NT)
	EXECUTABLE = pl2.exe
	ASM_EXEC = pl2asm.exe
else
	EXECUTABLE = pl2.out
	ASM_EXEC = pl2asm.out
endif

all: cpu asm

cpu: $(CPU_SRC)/*.cpp $(HEADERS)/*.hpp
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $(BUILD)/$(EXECUTABLE)

asm: $(ASM_SRC)/*.cpp
	$(CXX) $(CXXFLAGS) $? $(LDFLAGS) -o $(BUILD)/$(ASM_EXEC) && cp -r $(DBS)/* $(BUILD)
