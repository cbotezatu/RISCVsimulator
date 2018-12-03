#include "Instruction.h"
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <memory>
#include "Register.h"

template<uint32_t SIZE, uint32_t BITS>
static std::string InstructionToBits(uint64_t n, const uint32_t* sizes)
{
	//i should make this method return
	//a uniwue_ptr but i haven't worked
	//with it yet, so i would probably do
	//it wrong and blow things up instead.
	char bits[SIZE + BITS];
	bits[SIZE + BITS - 1] = '\0';

	int32_t index = SIZE + BITS - 2;
	for(uint32_t i = 0; i < SIZE; i++)
	{
		for(uint32_t x = 0; x < sizes[i]; x++)
		{
			bits[index] = (n & 1) ? '1' : '0';
			if (index == 0)
			{
				return std::string(bits);
			}

			index--;
			n >>= 1;
		}

		bits[index] = ' ';
		index--;
	}

	throw std::runtime_error("For some reason index never became 0 or SIZE was 0.");
}

std::string NumberToBits(const uint32_t n)
{
	const uint32_t sizes[4] = { 8, 8, 8, 8};
	return InstructionToBits<4, 32>(n, sizes);
}

std::string InstructionToBits(const uint32_t n)
{
	const uint32_t Rsizes [6] = { 7, 5, 3, 5, 5, 7 };
	const uint32_t Isizes [5] = { 7, 5, 3, 5, 12 };
	const uint32_t Ssizes [6] = { 7, 5, 3, 5, 5, 7 };
	const uint32_t SBsizes[6] = { 7, 5, 3, 5, 5, 7 };
	const uint32_t Usizes [3] = { 7, 5, 20 };
	const uint32_t UJsizes[3] = { 7, 5, 20 };
	switch (n & 127)
	{
		case 0b0000'0011:
		case 0b0000'1111:
		case 0b0001'0011:
		case 0b0110'0111:
		case 0b0111'0011:
			return InstructionToBits<5, 32>(n, Isizes);
			break;
		case 0b0001'0111:
		case 0b0011'0111:
			return InstructionToBits<3, 32>(n, Usizes);
			break;
		case 0b0010'0011:
			return InstructionToBits<6, 32>(n, Ssizes);
			break;
		case 0b0011'0011:
			return InstructionToBits<6, 32>(n, Rsizes);
			break;
		case 0b0110'0011:
			return InstructionToBits<6, 32>(n, SBsizes);
			break;
		case 0b0110'1111:
			return InstructionToBits<3, 32>(n, UJsizes);
			break;
		default:
			throw std::runtime_error("Invalid opcode. opcode: " + std::to_string(n & 127));
	}
}

static std::string GetNameOfInstructionType(const InstructionType type)
{
	switch (type)
	{
		case InstructionType::lb:
			return "lb";
		case InstructionType::lh:
			return "lh";
		case InstructionType::lw:
			return "lw";
		case InstructionType::lbu:
			return "lbu";
		case InstructionType::lhu:
			return "lhu";
		case InstructionType::fence:
			return "fence";
		case InstructionType::fence_i:
			return "fence_i";
		case InstructionType::addi:
			return "addi";
		case InstructionType::slli:
			return "slli";
		case InstructionType::slti:
			return "slti";
		case InstructionType::sltiu:
			return "sltiu";
		case InstructionType::xori:
			return "xori";
		case InstructionType::srli:
			return "srli";
		case InstructionType::srai:
			return "srai";
		case InstructionType::ori:
			return "ori";
		case InstructionType::andi:
			return "andi";
		case InstructionType::auipc:
			return "auipc";
		case InstructionType::sb:
			return "sb";
		case InstructionType::sh:
			return "sh";
		case InstructionType::sw:
			return "sw";
		case InstructionType::add:
			return "add";
		case InstructionType::sub:
			return "sub";
		case InstructionType::sll:
			return "sll";
		case InstructionType::slt:
			return "slt";
		case InstructionType::sltu:
			return "sltu";
		case InstructionType::xor_:
			return "xor";
		case InstructionType::srl:
			return "srl";
		case InstructionType::sra:
			return "sra";
		case InstructionType::or_:
			return "or";
		case InstructionType::and_:
			return "and";
		case InstructionType::lui:
			return "lui";
		case InstructionType::beq:
			return "beq";
		case InstructionType::bne:
			return "bne";
		case InstructionType::blt:
			return "blt";
		case InstructionType::bge:
			return "bge";
		case InstructionType::bltu:
			return "bltu";
		case InstructionType::bgeu:
			return "bgeu";
		case InstructionType::jalr:
			return "jalr";
		case InstructionType::jal:
			return "jal";
		case InstructionType::ecall:
			return "ecall";
		case InstructionType::ebreak:
			return "ebreak";
		case InstructionType::csrrw:
			return "csrrw";
		case InstructionType::csrrs:
			return "csrrs";
		case InstructionType::csrrc:
			return "csrrc";
		case InstructionType::csrrwi:
			return "csrrwi";
		case InstructionType::csrrsi:
			return "csrrsi";
		case InstructionType::csrrci:
			return "csrrci";
		case InstructionType::mul:
			return "mul";
		case InstructionType::mulh:
			return "mulh";
		case InstructionType::mulhsu:
			return "mulhsu";
		case InstructionType::mulhu:
			return "mulhu";
		case InstructionType::div:
			return "div";
		case InstructionType::divu:
			return "divu";
		case InstructionType::rem:
			return "rem";
		case InstructionType::remu:
			return "remu";
		default:
			throw std::runtime_error("Invalid instruction type. Type: " + NumberToBits(static_cast<uint32_t>(type)));
	}
}

std::string InstructionAsString(const Instruction& instruction)
{
	char text[50];
	std::string type = GetNameOfInstructionType(instruction.type);
	std::string rdText = RegisterName(instruction.rd);
	std::string rs1Text = RegisterName(instruction.rs1);
	std::string rs2Text = RegisterName(instruction.rs2);

	switch (InstructionTypeGetOpCode(instruction.type))
	{
		case 0b0000'0011:
			sprintf(text, "%s %s %i(%s)", type.c_str(), rdText.c_str(), instruction.immediate, rs1Text.c_str());
			break;
		case 0b0000'1111:
		case 0b0001'0011:
		case 0b0110'0111:
			sprintf(text, "%s %s %s %i", type.c_str(), rdText.c_str(), rs1Text.c_str(), instruction.immediate);
			break;
		case 0b0111'0011:
			sprintf(text, "%s", type.c_str());
			break;
		case 0b0001'0111:
		case 0b0011'0111:
			sprintf(text, "%s %s %i", type.c_str(), rdText.c_str(), static_cast<uint32_t>(instruction.immediate) >> 12);
			break;
		case 0b0010'0011:
			sprintf(text, "%s %s %i(%s)", type.c_str(), rs2Text.c_str(), instruction.immediate, rs1Text.c_str());
			break;
		case 0b0011'0011:
			sprintf(text, "%s %s %s %s", type.c_str(), rdText.c_str(), rs1Text.c_str(), rs2Text.c_str());
			break;
		case 0b0110'0011:
			sprintf(text, "%s %s %s %i", type.c_str(), rs1Text.c_str(), rs2Text.c_str(), instruction.immediate);
			break; 
		case 0b0110'1111:
			sprintf(text, "%s %s %i", type.c_str(), rdText.c_str(), instruction.immediate);
			break;
		default:
			throw std::runtime_error("Invalid opcode. opcode: " + std::to_string(InstructionTypeGetOpCode(instruction.type)));
	}

	return std::string(text);
}
