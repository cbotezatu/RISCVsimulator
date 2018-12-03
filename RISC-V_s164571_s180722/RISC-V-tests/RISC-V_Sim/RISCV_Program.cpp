#include "RISCV_Program.h"
#include <stdexcept>
#include <fstream>
#include <memory>
#include <iostream>
#include <iomanip>
#include "InstructionEncode.h"
#include "InstructionDecode.h"
#include "Processor.h"
#include "ReadProgram.h"


RISCV_Program::RISCV_Program(const std::string name)
{
	ProgramName = name;
    for(uint32_t i = 0; i < 32; i++)
    {
        ExpectedRegisters[i] = 0;
		ActualRegisters[i] = 0;
    }
}
void RISCV_Program::SetRegister(Regs reg, uint32_t value)
{
    MultiInstruction mInstruction = Create_li(reg, value);
    AddInstruction(mInstruction);
    ExpectRegisterValue(reg, value);
}

void RISCV_Program::ExpectRegisterValue(Regs reg, uint32_t expected)
{
    ExpectedRegisters[static_cast<uint32_t>(reg)] = expected;
}

void RISCV_Program::AddInstruction(uint32_t rawInstruction)
{
    Instructions.push_back(rawInstruction);
}
void RISCV_Program::AddInstruction(MultiInstruction mInstruction)
{
    if (mInstruction.instruction1 != 0)
    {
        AddInstruction(mInstruction.instruction1);
    }
    if (mInstruction.instruction2 != 0)
    {
        AddInstruction(mInstruction.instruction2);
    }
}

void RISCV_Program::RemoveLatestsInstruction()
{
	Instructions.pop_back();
}

void RISCV_Program::EndProgram()
{
	SetRegister(Regs::a0, 10);
	ExpectRegisterValue(Regs::a0, 10);
	AddInstruction(Create_ecall());
}

static std::string RegistersToString(const uint32_t* regs1, const uint32_t* regs2)
{
	std::string registerSum = "";
	for(uint32_t i = 0; i < 32; i++)
	{
		//don't show stack pointer register
		//as it isn't checked
		if (i == static_cast<uint32_t>(Regs::sp))
		{
			registerSum += "sp 0 : 0";
		}
		else
		{
			registerSum += RegisterName(i);
			registerSum += " ";
			registerSum += std::to_string(regs1[i]);
			registerSum += " : ";
			registerSum += std::to_string(regs2[i]);
		}

		registerSum += "\n";
	}

	return registerSum;
}

static bool CompareRegisters(const uint32_t* regs1, const uint32_t* regs2)
{
	for(uint32_t i = 0; i < 32; i++)
	{
		if (regs1[i] != regs2[i])
		{
			return false;
		}
	}
	return true;
}

std::string RISCV_Program::GetRegisterComparison()
{
	return RegistersToString(ExpectedRegisters, ActualRegisters);
}

bool RISCV_Program::CheckProgramResult()
{
	return CompareRegisters(ExpectedRegisters, ActualRegisters);
}

void RISCV_Program::Run()
{
	Processor processor;
	processor.Run(&Instructions[0], Instructions.size());
	processor.CopyRegistersTo(ActualRegisters);
}

void RISCV_Program::Test()
{
	Run();
	if (!CheckProgramResult())
	{
		std::string registersDiff = GetRegisterComparison();
		throw std::runtime_error("Incorrect program result for " + ProgramName + ".\nExpected : Actual\n" + registersDiff);
	}
}

static void WriteFile(const std::string& filepath, const char* toWrite, const size_t size)
{
	std::ofstream file(filepath.c_str(), std::ios::binary);
	if (!file)
	{
		throw std::runtime_error("Failed to create file: " + filepath);
	}
	file.write(toWrite, size);
	file.close(); 
}

void RISCV_Program::Save(const std::string& filepath) const
{
	const std::string binFile      = filepath + ".bin";
	const std::string registerFile = filepath + ".res";
	const std::string assemblyFile = filepath + ".s";

	WriteFile(binFile     , reinterpret_cast<const char*>(&Instructions[0]) , sizeof(uint32_t) * Instructions.size());
	WriteFile(registerFile, reinterpret_cast<const char*>(ExpectedRegisters), sizeof(uint32_t) * 32);

	const std::string programAsText = GetProgramAsString(&Instructions[0], Instructions.size());
	WriteFile(assemblyFile, programAsText.c_str(), programAsText.length());
}

void RISCV_Program::SaveProgramResult(const std::string& filepath) const
{
	const std::string registerFile = filepath + ".res";
	WriteFile(registerFile, reinterpret_cast<const char*>(ActualRegisters)   , sizeof(uint32_t) * 32);
}

std::string RISCV_Program::GetProgramName() const
{
	return ProgramName;
}

const uint32_t* RISCV_Program::GetProgramResult() const
{
	return ActualRegisters;
}

void RISCV_Program::ActualToExpectedRegisters()
{
	for(uint32_t i = 0; i < 32; i++)
	{
		ExpectedRegisters[i] = ActualRegisters[i];
	}
}

void RISCV_Program::PrintResult()
{
	for(int32_t i = 0; i < 32; i++)
	{
		std::cout << std::setw(3) << RegisterName(i) << "  ";
		std::cout << std::setw(10) << std::to_string(static_cast<int32_t>(ActualRegisters[i]));
		std::cout << std::endl;
	}
}

void CompareRISCVPrograms(RISCV_Program& p1, std::unique_ptr<RISCV_Program>& p2)
{
	const uint32_t* regs1 = p1.GetProgramResult();
	const uint32_t* regs2 = p2->GetProgramResult();
	if (!CompareRegisters(regs1, regs2))
	{
		const std::string p1Name = p1.GetProgramName();
		const std::string p2Name = p2->GetProgramName();
		const std::string registersDiff = RegistersToString(regs1, regs2);

		throw std::runtime_error("Program " + p1Name + " and " + p2Name + " does not give the same result.\n" + registersDiff);
	}
}
