#pragma once

#include <cstdint>
#include "Instruction.h"
#include "Register.h"

class Processor
{
private:
	const static int32_t MEMORY_SIZE = 0x00'00'7f'ff;

	uint32_t pc = 0;
	Register registers[32];
	uint8_t* memory;
	bool debugEnabled = false;
	bool printExecutedInstruction = false;

	void VerifyMemorySpace(const int32_t index, const int32_t size);
	uint8_t  GetByteFromMemory    (const int32_t index);
	uint16_t GetHalfWordFromMemory(const int32_t index);
	uint32_t GetWordFromMemory    (const int32_t index);
	void StoreByteInMemory    (const int32_t index, const int8_t  byte    );
	void StoreHalfWordInMemory(const int32_t index, const int16_t halfWord);
	void StoreWordInMemory    (const int32_t index, const int32_t word    );
	void EnvironmentCall(bool* stopProgram);

public:
	Processor();
	void Run(const uint32_t* instructions, const size_t instructionCount);
	bool RunInstruction(const Instruction& instruction);
	void PrintInstructions(const uint32_t* rawInstructions, const uint32_t instructionCount);
	void PrintRegisters();
	void SetDebugMode(const bool useDebugMode);
	void SetPrintExecutedInstruction(const bool value);
	void CopyRegistersTo(uint32_t* copyTo);
	void Reset();

	~Processor();
};

