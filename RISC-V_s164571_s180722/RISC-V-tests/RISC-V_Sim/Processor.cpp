#include "Processor.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <vector>
#include "InstructionDecode.h"
#include "Register.h"


Processor::Processor()
{
	memory = new uint8_t[Processor::MEMORY_SIZE];
	Reset();
}

void Processor::Run(const uint32_t* rawInstructions, const size_t instructionCount)
{
	Reset();
	const std::unique_ptr<std::vector<Instruction>> instructions = DecodeInstructions(rawInstructions, instructionCount);

	//set stack pointer
	registers[static_cast<uint32_t>(Regs::sp)].word = Processor::MEMORY_SIZE;

	while (true)
	{
		const uint32_t instructionIndex = pc / 4;
		if (instructionIndex >= instructionCount)
		{
			throw std::runtime_error("Index out of bounds.\nTried to access instruction: " + std::to_string(instructionIndex));
		}

		const Instruction& instruction = instructions->at(instructionIndex);
		const bool stopProgram = RunInstruction(instruction);

		if (printExecutedInstruction || debugEnabled)
		{
			std::cout << std::to_string(instructionIndex) << ": " << InstructionAsString(instruction) << std::endl;
		}
		if (debugEnabled)
		{
			PrintRegisters();
			std::cin.get();
		}

		if (stopProgram)
		{
			break;
		}
	}
}

bool Processor::RunInstruction(const Instruction& instruction)
{
	bool stopProgram = false;

	switch (instruction.type)
	{
		case InstructionType::lb:
			registers[instruction.rd].word = static_cast<int32_t>(static_cast<int8_t>(GetByteFromMemory(registers[instruction.rs1].word + instruction.immediate)));
			pc += 4;
			break;
		case InstructionType::lh:
			registers[instruction.rd].word = static_cast<int32_t>(static_cast<int16_t>(GetHalfWordFromMemory(registers[instruction.rs1].word + instruction.immediate)));
			pc += 4;
			break;
		case InstructionType::lw: // no need to sign extend so don't cast
			registers[instruction.rd].uword = GetWordFromMemory(registers[instruction.rs1].word + instruction.immediate);
			pc += 4;
			break;
		case InstructionType::lbu:
			registers[instruction.rd].uword = static_cast<uint32_t>(GetByteFromMemory(registers[instruction.rs1].word + instruction.immediate));
			pc += 4;
			break;
		case InstructionType::lhu:
			registers[instruction.rd].uword = static_cast<uint32_t>(GetHalfWordFromMemory(registers[instruction.rs1].word + instruction.immediate));
			pc += 4;
			break;
		case InstructionType::fence:
		case InstructionType::fence_i:
			throw std::runtime_error("Instruction not implemented yet.");
		case InstructionType::addi:
			registers[instruction.rd].word = registers[instruction.rs1].word + instruction.immediate;
			pc += 4;
			break;
		case InstructionType::slli:
			registers[instruction.rd].word = registers[instruction.rs1].word << instruction.immediate;
			pc += 4;
			break;
		case InstructionType::slti:
			registers[instruction.rd].word = (registers[instruction.rs1].word < instruction.immediate) ? 1 : 0;
			pc += 4;
			break;
		case InstructionType::sltiu: // special immediate cast
			registers[instruction.rd].word = (registers[instruction.rs1].uword < static_cast<uint32_t>(instruction.immediate)) ? 1 : 0;
			pc += 4;
			break;
		case InstructionType::xori:
			registers[instruction.rd].word = registers[instruction.rs1].word ^ instruction.immediate;
			pc += 4;
			break;
		case InstructionType::srli: // special immediate cast
			registers[instruction.rd].uword = registers[instruction.rs1].uword >> static_cast<uint32_t>(instruction.immediate);
			pc += 4;
			break;
		case InstructionType::srai:
			registers[instruction.rd].word = registers[instruction.rs1].word >> instruction.immediate;
			pc += 4;
			break;
		case InstructionType::ori:
			registers[instruction.rd].word = registers[instruction.rs1].word | instruction.immediate;
			pc += 4;
			break;
		case InstructionType::andi:
			registers[instruction.rd].word = registers[instruction.rs1].word & instruction.immediate;
			pc += 4;
			break;
		case InstructionType::auipc: // cast not needed but it helps to clarify that the immediate is unsigned for u type instructions
			registers[instruction.rd].uword = pc + static_cast<uint32_t>(instruction.immediate);
			pc += 4;
			break;
		case InstructionType::sb:
			StoreByteInMemory(registers[instruction.rs1].word + instruction.immediate, registers[instruction.rs2].byte);
			pc += 4;
			break;
		case InstructionType::sh:
			StoreHalfWordInMemory(registers[instruction.rs1].word + instruction.immediate, registers[instruction.rs2].half);
			pc += 4;
			break;
		case InstructionType::sw:
			StoreWordInMemory(registers[instruction.rs1].word + instruction.immediate, registers[instruction.rs2].word);
			pc += 4;
			break;
		case InstructionType::add:
			registers[instruction.rd].word = registers[instruction.rs1].word + registers[instruction.rs2].word;
			pc += 4;
			break;
		case InstructionType::sub:
			registers[instruction.rd].word = registers[instruction.rs1].word - registers[instruction.rs2].word;
			pc += 4;
			break;
		case InstructionType::sll:
			registers[instruction.rd].word = registers[instruction.rs1].word << registers[instruction.rs2].word;
			pc += 4;
			break;
		case InstructionType::slt:
			registers[instruction.rd].word = (registers[instruction.rs1].word < registers[instruction.rs2].word) ? 1 : 0;
			pc += 4;
			break;
		case InstructionType::sltu:
			registers[instruction.rd].word = (registers[instruction.rs1].uword < registers[instruction.rs2].uword) ? 1 : 0;
			pc += 4;
			break;
		case InstructionType::xor_:
			registers[instruction.rd].word = registers[instruction.rs1].word ^ registers[instruction.rs2].word;
			pc += 4;
			break;
		case InstructionType::srl:
			registers[instruction.rd].uword = registers[instruction.rs1].uword >> registers[instruction.rs2].uword;
			pc += 4;
			break;
		case InstructionType::sra:
			registers[instruction.rd].word = registers[instruction.rs1].word >> registers[instruction.rs2].word;
			pc += 4;
			break;
		case InstructionType::or_:
			registers[instruction.rd].word = registers[instruction.rs1].word | registers[instruction.rs2].word;
			pc += 4;
			break;
		case InstructionType::and_:
			registers[instruction.rd].word = registers[instruction.rs1].word & registers[instruction.rs2].word;
			pc += 4;
			break;
		case InstructionType::lui:
			registers[instruction.rd].word = instruction.immediate;
			pc += 4;
			break;
		case InstructionType::beq:
			pc = (registers[instruction.rs1].word ==  registers[instruction.rs2].word)  ? pc + instruction.immediate : pc + 4;
			break;
		case InstructionType::bne:
			pc = (registers[instruction.rs1].word !=  registers[instruction.rs2].word)  ? pc + instruction.immediate : pc + 4;
			break;
		case InstructionType::blt:
			pc = (registers[instruction.rs1].word <   registers[instruction.rs2].word)  ? pc + instruction.immediate : pc + 4;
			break;
		case InstructionType::bge:
			pc = (registers[instruction.rs1].word >=  registers[instruction.rs2].word)  ? pc + instruction.immediate : pc + 4;
			break;
		case InstructionType::bltu:
			pc = (registers[instruction.rs1].uword <  registers[instruction.rs2].uword) ? pc + instruction.immediate : pc + 4;
			break;
		case InstructionType::bgeu:
			pc = (registers[instruction.rs1].uword >= registers[instruction.rs2].uword) ? pc + instruction.immediate : pc + 4;
			break;
		case InstructionType::jalr:
			registers[instruction.rd].uword = pc + 4;
			pc = registers[instruction.rs1].word + instruction.immediate;
			break;
		case InstructionType::jal:
			registers[instruction.rd].uword = pc + 4;
			pc = pc + instruction.immediate;
			break;
		case InstructionType::ecall:
			EnvironmentCall(&stopProgram);
			pc += 4;
			break;
		case InstructionType::ebreak:
			PrintRegisters();
			std::cin.get();
			pc += 4;
			break;
		case InstructionType::csrrw:
		case InstructionType::csrrs:
		case InstructionType::csrrc:
		case InstructionType::csrrwi:
		case InstructionType::csrrsi:
		case InstructionType::csrrci:
			throw std::runtime_error("Instruction not implemented yet.");
		case InstructionType::mul:
			registers[instruction.rd].word = registers[instruction.rs1].word * registers[instruction.rs2].word;
			pc += 4;
			break;
		case InstructionType::mulh:
			registers[instruction.rd].word = static_cast<int32_t>((static_cast<int64_t>(registers[instruction.rs1].word) * static_cast<int64_t>(registers[instruction.rs2].word)) >> 32);
			pc += 4;
			break;
		case InstructionType::mulhsu:
			registers[instruction.rd].word = (static_cast<int64_t>(registers[instruction.rs1].word) * static_cast<uint64_t>(registers[instruction.rs2].uword)) >> 32;
			pc += 4;
			break;
		case InstructionType::mulhu:
			registers[instruction.rd].uword = static_cast<uint32_t>((static_cast<uint64_t>(registers[instruction.rs1].uword) * static_cast<uint64_t>(registers[instruction.rs2].uword)) >> 32);
			pc += 4;
			break;
		case InstructionType::div:
			if (registers[instruction.rs2].word == 0)
			{
				registers[instruction.rd].word = -1;
			}
			else if (registers[instruction.rs1].word == INT32_MIN && registers[instruction.rs2].word == -1)
			{
				registers[instruction.rd].word = registers[instruction.rs1].word;
			}
			else
			{
				registers[instruction.rd].word = registers[instruction.rs1].word / registers[instruction.rs2].word;
			}
			pc += 4;
			break;
		case InstructionType::divu:
			if (registers[instruction.rs2].word == 0)
			{
				registers[instruction.rd].uword = registers[instruction.rs1].uword;
			}
			else
			{
				registers[instruction.rd].uword = registers[instruction.rs1].uword / registers[instruction.rs2].uword;
			}
			pc += 4;
			break;
		case InstructionType::rem:
			if (registers[instruction.rs2].word == 0)
			{
				registers[instruction.rd].word = registers[instruction.rs1].word;
			}
			else if (registers[instruction.rs1].word == INT32_MIN && registers[instruction.rs2].word == -1)
			{
				registers[instruction.rd].word = 0;
			}
			else
			{
				registers[instruction.rd].word = registers[instruction.rs1].word % registers[instruction.rs2].word;
			}
			pc += 4;
			break;
		case InstructionType::remu:
			if (registers[instruction.rs2].uword == 0)
			{
				registers[instruction.rd].uword = registers[instruction.rs1].uword;
			}
			else
			{
				registers[instruction.rd].uword = registers[instruction.rs1].uword % registers[instruction.rs2].uword;
			}
			pc += 4;
			break;
		default:
			throw std::runtime_error("instruction identifier not recognized. iid: " + NumberToBits(static_cast<uint32_t>(instruction.type)));
			break;
	}
	//the 0'th register can only be 0
	//so set it back to 0 in case it was changed
	registers[static_cast<uint32_t>(Regs::x0)].word = 0;

	return stopProgram;
}

void Processor::PrintInstructions(const uint32_t* rawInstructions, const uint32_t instructionCount)
{
	const std::unique_ptr<std::vector<Instruction>> instructions = DecodeInstructions(rawInstructions, instructionCount);
	for (uint32_t i = 0; i < instructionCount; i++)
	{
		const Instruction instruction = instructions->at(i);
		std::cout << std::setw(32 + 6) << InstructionToBits(rawInstructions[i]) << "  " << InstructionAsString(instruction) << std::endl;
	}
}

void Processor::EnvironmentCall(bool* stopProgram)
{
	if (registers[static_cast<uint32_t>(Regs::a0)].word == 10)
	{
		*stopProgram = true;
	}
}

void Processor::CopyRegistersTo(uint32_t* copyTo)
{
	for (uint32_t i = 0; i < 32; i++)
	{
		//don't copy stack pointer because the correct is wrong
		if (i != static_cast<uint32_t>(Regs::sp))
		{
			copyTo[i] = registers[i].uword;
		}
		else 
		{
			copyTo[i] = 0;
		}
	}
}

void Processor::SetDebugMode(const bool useDebugMode)
{
	debugEnabled = useDebugMode;
}
void Processor::SetPrintExecutedInstruction(const bool value)
{
	printExecutedInstruction = value;
}

void Processor::PrintRegisters()
{
	std::cout << "Registers:" << std::endl;
	uint32_t index = 0;
	for(Register x : registers)
	{
		std::cout << std::setw(3) << RegisterName(index) << "  ";
		std::cout << std::setw(10) << std::to_string(x.word) << "  ";
		std::cout << NumberToBits(x.uword) << "   ";
		std::cout << std::setw(3) << std::to_string(index * 4 + 32 * 4 * 0) << ": " << std::setw(10) << GetWordFromMemory(index * 4 + 32 * 4 * 0) << "  ";
		std::cout << std::setw(3) << std::to_string(index * 4 + 32 * 4 * 1) << ": " << std::setw(10) << GetWordFromMemory(index * 4 + 32 * 4 * 1) << "  ";
		std::cout << std::setw(3) << std::to_string(index * 4 + 32 * 4 * 2) << ": " << std::setw(10) << GetWordFromMemory(index * 4 + 32 * 4 * 2) << "  ";
		std::cout << std::setw(3) << std::to_string(index * 4 + 32 * 4 * 3) << ": " << std::setw(10) << GetWordFromMemory(index * 4 + 32 * 4 * 3) << std::endl;
		index++;
	}
	std::cout << std::endl;
}

void Processor::VerifyMemorySpace(const int32_t index, const int32_t size)
{
	if (index < 0 || index + size > Processor::MEMORY_SIZE)
	{
		throw std::runtime_error("Memory access out of range.\nTried to access memory address " + std::to_string(index));
	}
}

uint8_t Processor::GetByteFromMemory(const int32_t index)
{
	VerifyMemorySpace(index, 1);

	return memory[index];
}
uint16_t Processor::GetHalfWordFromMemory(const int32_t index)
{
	VerifyMemorySpace(index, 2);

	const uint16_t t1 = static_cast<uint16_t>(memory[index + 0]);
	const uint16_t t2 = static_cast<uint16_t>(memory[index + 1]);

	return (t1 << 0) |
		   (t2 << 8);
}
uint32_t Processor::GetWordFromMemory(const int32_t index)
{
	VerifyMemorySpace(index, 4);

	const uint32_t t1 = static_cast<uint32_t>(memory[index + 0]);
	const uint32_t t2 = static_cast<uint32_t>(memory[index + 1]);
	const uint32_t t3 = static_cast<uint32_t>(memory[index + 2]);
	const uint32_t t4 = static_cast<uint32_t>(memory[index + 3]);

	return (t1 <<  0) |
		   (t2 <<  8) |
		   (t3 << 16) |
		   (t4 << 24);
}

void Processor::StoreByteInMemory(const int32_t index, const int8_t byte)
{
	VerifyMemorySpace(index, 1);

	memory[index] = static_cast<uint8_t>(byte);
}
void Processor::StoreHalfWordInMemory(const int32_t index, const int16_t halfWord)
{
	VerifyMemorySpace(index, 2);

	memory[index + 0] = static_cast<uint8_t>(static_cast<uint16_t>(halfWord) >> 0);
	memory[index + 1] = static_cast<uint8_t>(static_cast<uint16_t>(halfWord) >> 8);
}
void Processor::StoreWordInMemory(const int32_t index, const int32_t word)
{
	VerifyMemorySpace(index, 4);

	memory[index + 0] = static_cast<uint8_t>(static_cast<uint32_t>(word) >>  0);
	memory[index + 1] = static_cast<uint8_t>(static_cast<uint32_t>(word) >>  8);
	memory[index + 2] = static_cast<uint8_t>(static_cast<uint32_t>(word) >> 16);
	memory[index + 3] = static_cast<uint8_t>(static_cast<uint32_t>(word) >> 24);
}

void Processor::Reset()
{
	std::fill(memory, memory + Processor::MEMORY_SIZE, 0);
	for(uint32_t i = 0; i < 32; i++)
	{
		registers[i].word = 0;
	}
	pc = 0;
}

Processor::~Processor()
{
	delete[] memory;
}
