#pragma once

#include <cstdint>
#include <string>
#include "InstructionType.h"

struct Instruction
{
	int32_t immediate;
	InstructionType type;
	uint8_t rd;
	uint8_t rs1;
	uint8_t rs2;
};

std::string NumberToBits(const uint32_t n);
std::string InstructionToBits(const uint32_t n);
std::string InstructionAsString(const Instruction& instruction);