
OBJS = RISCVSim.o Processor.o Instruction.o InstructionDecode.o \
	InstructionEncode.o InstructionType.o Register.o \
	TestEncodeDecode.o TestInstructions.o RISCV_Program.o ReadProgram.o \
	TestRandomInstructions.o TSrandom.o
LIBS = -lm 
CFLAGS = -Wall -g
#CFLAGS = -Wall -O2 -flto -march=native

all: solver

%.o: %.cpp
	g++ -std=c++14 ${CFLAGS} -c $<

solver: ${OBJS}
	g++ -std=c++14 ${CFLAGS} ${OBJS} ${LIBS} -o RISC_V_Sim
	
clean:
	rm -f ${OBJS} RISC_V_Sim