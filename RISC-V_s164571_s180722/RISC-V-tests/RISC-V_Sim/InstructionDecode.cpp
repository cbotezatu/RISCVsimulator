#include "InstructionDecode.h"
#include <cstdint>
#include <stdexcept>
#include <memory>
#include <vector>
#include "Instruction.h"
#include "InstructionFormat.h"
#include "ImmediateFormat.h"

static uint32_t GetImmediateMask(uint16_t instructionIdentifier)
{
	const uint32_t removefunct7    = 0b00000000'00000000'00000000'00011111;
	const uint32_t wholeidentifier = 0b11111111'11111111'11111111'11111111;
	switch (instructionIdentifier)
	{
		case 0b000000'001'0010011:
		case 0b000000'101'0010011:
			return removefunct7;
		default:
			return wholeidentifier;
	}
}

static uint16_t GetInstructionIdentifierMask(uint16_t instructionIdentifier)
{
	const uint16_t onlyOpCodeAndFunct3 = 0b000000'111'1111111;
	const uint16_t wholeidentifier     = 0b111111'111'1111111;
	switch (instructionIdentifier & onlyOpCodeAndFunct3)
	{
		case 0b000000'001'0010011:
		case 0b000000'101'0010011:
		case 0b000000'000'0110011:
		case 0b000000'001'0110011:
		case 0b000000'010'0110011:
		case 0b000000'011'0110011:
		case 0b000000'100'0110011:
		case 0b000000'101'0110011:
		case 0b000000'110'0110011:
		case 0b000000'111'0110011:
		case 0b000000'000'1110011:
			return wholeidentifier;
		default:
			return onlyOpCodeAndFunct3;
	}
}

static InstructionType GetInstructionType(const uint32_t opcode, const uint32_t funct3, const uint32_t funct7OrImmediate)
{
	const uint16_t instructionIdentifier = static_cast<uint16_t>((opcode            <<  0) |
																 (funct3            <<  7) |
																 (funct7OrImmediate << 10));
	const uint16_t mask = GetInstructionIdentifierMask(instructionIdentifier);

	const uint16_t instructionType = instructionIdentifier & mask;
	return static_cast<InstructionType>(instructionType);
}

static Instruction DecodeRType(const uint32_t rawInstruction)
{
	RType rType(rawInstruction);
	Instruction decoded;
	decoded.rd   = rType.rd.GetAsInt();
	decoded.rs1  = rType.rs1.GetAsInt();
	decoded.rs2  = rType.rs2.GetAsInt();
	decoded.type = GetInstructionType(rType.opcode.GetAsInt(), rType.funct3.GetAsInt(), rType.funct7.GetAsInt());

	return decoded;
}

static Instruction DecodeIType(const uint32_t rawInstruction)
{
	const IType iType(rawInstruction);

	Instruction decoded = { 0 };
	decoded.rd         = iType.rd.GetAsInt();
	decoded.rs1        = iType.rs1.GetAsInt();
	decoded.immediate  = SignExtend<12>(iType.immediate.GetAsInt());
	decoded.type       = GetInstructionType(iType.opcode.GetAsInt(), iType.funct3.GetAsInt(), iType.immediate.GetAsInt() >> 5);
	decoded.immediate &= GetImmediateMask((iType.funct3.GetAsInt() << 7) | iType.opcode.GetAsInt());

	return decoded;
}

static Instruction DecodeSType(const uint32_t rawInstruction)
{
	const SType sType(rawInstruction);
	Instruction decoded = { 0 };
	decoded.rs1 = sType.rs1.GetAsInt();
	decoded.rs2 = sType.rs2.GetAsInt();
	decoded.immediate = sType.GetImmediate();
	decoded.type = GetInstructionType(sType.opcode.GetAsInt(), sType.funct3.GetAsInt(), 0);

	return decoded;
}

static Instruction DecodeSBType(const uint32_t rawInstruction)
{
	const SBType sbType(rawInstruction);
	Instruction decoded = { 0 };
	decoded.rs1 = sbType.rs1.GetAsInt();
	decoded.rs2 = sbType.rs2.GetAsInt();
	decoded.immediate = sbType.GetImmediate();
	decoded.type = GetInstructionType(sbType.opcode.GetAsInt(), sbType.funct3.GetAsInt(), 0);

	return decoded;
}

static Instruction DecodeUJType(const uint32_t rawInstruction)
{
	const UJType ujType(rawInstruction);
	Instruction decoded = { 0 };
	decoded.rd = ujType.rd.GetAsInt();
	decoded.immediate = ujType.GetImmediate();
	decoded.type = GetInstructionType(ujType.opcode.GetAsInt(), 0, 0);

	return decoded;
}

static Instruction DecodeUType(const uint32_t rawInstruction)
{
	const UType uType(rawInstruction);
	Instruction decoded = { 0 };
	decoded.rd = uType.rd.GetAsInt();
	decoded.immediate = uType.GetImmediate();
	decoded.type = GetInstructionType(uType.opcode.GetAsInt(), 0, 0);

	return decoded;
}

Instruction DecodeInstruction(const uint32_t rawInstruction)
{
	//opcode is the first 7 bits
	const uint32_t opcode = rawInstruction & 127;

	switch (opcode)
	{
		case 0b0000011:
		case 0b0001111:
		case 0b0010011:
		case 0b1100111:
		case 0b1110011:
			return DecodeIType(rawInstruction);
		case 0b0010111:
		case 0b0110111:
			return DecodeUType(rawInstruction);
		case 0b0100011:
			return DecodeSType(rawInstruction);
		case 0b0110011:
			return DecodeRType(rawInstruction);
		case 0b1100011:
			return DecodeSBType(rawInstruction);
		case 0b1101111:
			return DecodeUJType(rawInstruction);
		default:
			throw std::runtime_error("Invalid opcode. opcode: " + std::to_string(opcode));
	}
}

std::unique_ptr<std::vector<Instruction>> DecodeInstructions(const uint32_t* rawInstructions, const size_t instructionsCount)
{
	std::unique_ptr<std::vector<Instruction>> instructions = std::make_unique<std::vector<Instruction>>();

	for (size_t i = 0; i < instructionsCount; i++)
	{
		const uint32_t rawInstruction = rawInstructions[i];
		const Instruction instruction = DecodeInstruction(rawInstruction);
		instructions->push_back(instruction);
	}

	return instructions;
}

std::string GetProgramAsString(const uint32_t* rawInstructions, const size_t instructionCount)
{
	std::string program;
	for(size_t i = 0; i < instructionCount; i++)
	{
		const Instruction instruction = DecodeInstruction(rawInstructions[i]);
		program += InstructionAsString(instruction) + "\n";
	}

	return program;
}