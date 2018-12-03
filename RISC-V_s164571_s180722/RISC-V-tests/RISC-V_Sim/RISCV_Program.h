#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include "InstructionEncode.h"
#include "Register.h"
#include "Processor.h"

class RISCV_Program
{
private:
	std::string ProgramName;
	std::vector<uint32_t> Instructions;
	uint32_t ExpectedRegisters[32];
	uint32_t ActualRegisters[32];

	std::string GetRegisterComparison();
	bool CheckProgramResult();

public:
	RISCV_Program(const std::string name);

	void SetRegister(Regs reg, uint32_t value);
	void ExpectRegisterValue(Regs reg, uint32_t expected);
	void AddInstruction(uint32_t rawInstruction);
	void AddInstruction(MultiInstruction mInstruction);
	void RemoveLatestsInstruction();
	void EndProgram();

	void Run();
	void Test();
	void Save(const std::string& filepath) const;
	void SaveProgramResult(const std::string& filepath) const;
	std::string GetProgramName() const;
	const uint32_t* GetProgramResult() const;
	void ActualToExpectedRegisters();
	void PrintResult();
};

void CompareRISCVPrograms(RISCV_Program& p1, std::unique_ptr<RISCV_Program>& p2);

