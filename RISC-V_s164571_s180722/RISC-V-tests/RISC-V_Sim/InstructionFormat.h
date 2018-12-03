#pragma once

#include <cstdint>
#include "BitField.h"
#include "ImmediateFormat.h"

struct RType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> rd;
	BitField<0b0000'0000'0000'0000'0111'0000'0000'0000> funct3;
	BitField<0b0000'0000'0000'1111'1000'0000'0000'0000> rs1;
	BitField<0b0000'0001'1111'0000'0000'0000'0000'0000> rs2;
	BitField<0b1111'1110'0000'0000'0000'0000'0000'0000> funct7;

	RType(const uint32_t rawInstruction)
	{
		opcode.FromField(rawInstruction);
		rd    .FromField(rawInstruction);
		funct3.FromField(rawInstruction);
		rs1   .FromField(rawInstruction);
		rs2   .FromField(rawInstruction);
		funct7.FromField(rawInstruction);
	}
	RType()
	{ }

	uint32_t ToRawInstruction() const
	{
		return opcode.GetField() | 
			   rd    .GetField() | 
			   funct3.GetField() | 
			   rs1   .GetField() | 
			   rs2   .GetField() | 
			   funct7.GetField();
	}
};

struct IType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> rd;
	BitField<0b0000'0000'0000'0000'0111'0000'0000'0000> funct3;
	BitField<0b0000'0000'0000'1111'1000'0000'0000'0000> rs1;
	BitField<0b1111'1111'1111'0000'0000'0000'0000'0000> immediate;

	IType(const uint32_t rawInstruction)
	{
		opcode   .FromField(rawInstruction);
		rd       .FromField(rawInstruction);
		funct3   .FromField(rawInstruction);
		rs1      .FromField(rawInstruction);
		immediate.FromField(rawInstruction);
	}
	IType()
	{ }

	uint32_t ToRawInstruction() const
	{
		return opcode   .GetField() | 
			   rd       .GetField() | 
			   funct3   .GetField() | 
			   rs1      .GetField() | 
			   immediate.GetField();
	}
};

struct SType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> immediate1;
	BitField<0b0000'0000'0000'0000'0111'0000'0000'0000> funct3;
	BitField<0b0000'0000'0000'1111'1000'0000'0000'0000> rs1;
	BitField<0b0000'0001'1111'0000'0000'0000'0000'0000> rs2;
	BitField<0b1111'1110'0000'0000'0000'0000'0000'0000> immediate2;

	SType(const uint32_t rawInstruction)
	{
		opcode    .FromField(rawInstruction);
		immediate1.FromField(rawInstruction);
		funct3    .FromField(rawInstruction);
		rs1       .FromField(rawInstruction);
		rs2       .FromField(rawInstruction);
		immediate2.FromField(rawInstruction);
	}
	SType()
	{ }

	int32_t GetImmediate() const
	{
		SImmediate immediate;
		immediate.immediate1.FromInt(immediate1.GetAsInt());
		immediate.immediate2.FromInt(immediate2.GetAsInt());

		return immediate.ToImmediate();
	}
	void SetImmediate(const uint32_t value)
	{
		SImmediate immediate(value);
		immediate1.FromInt(immediate.immediate1.GetAsInt());
		immediate2.FromInt(immediate.immediate2.GetAsInt());
	}

	uint32_t ToRawInstruction() const
	{
		return opcode    .GetField() | 
			   immediate1.GetField() | 
			   funct3    .GetField() | 
			   rs1       .GetField() | 
			   rs2       .GetField() | 
			   immediate2.GetField();
	}
};

struct SBType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'0000'1000'0000> immediate1;
	BitField<0b0000'0000'0000'0000'0000'1111'0000'0000> immediate2;
	BitField<0b0000'0000'0000'0000'0111'0000'0000'0000> funct3;
	BitField<0b0000'0000'0000'1111'1000'0000'0000'0000> rs1;
	BitField<0b0000'0001'1111'0000'0000'0000'0000'0000> rs2;
	BitField<0b0111'1110'0000'0000'0000'0000'0000'0000> immediate3;
	BitField<0b1000'0000'0000'0000'0000'0000'0000'0000> immediate4;

	SBType(const uint32_t rawInstruction)
	{
		opcode    .FromField(rawInstruction);
		immediate1.FromField(rawInstruction);
		immediate2.FromField(rawInstruction);
		funct3    .FromField(rawInstruction);
		rs1       .FromField(rawInstruction);
		rs2       .FromField(rawInstruction);
		immediate3.FromField(rawInstruction);
		immediate4.FromField(rawInstruction);
	}
	SBType()
	{ }

	int32_t GetImmediate() const
	{
		SBImmediate immediate;
		immediate.immediate1.FromInt(immediate2.GetAsInt());
		immediate.immediate2.FromInt(immediate3.GetAsInt());
		immediate.immediate3.FromInt(immediate1.GetAsInt());
		immediate.immediate4.FromInt(immediate4.GetAsInt());

		return immediate.ToImmediate();
	}
	void SetImmediate(const uint32_t value)
	{
		const SBImmediate immediate(value);
		immediate1.FromInt(immediate.immediate3.GetAsInt());
		immediate2.FromInt(immediate.immediate1.GetAsInt());
		immediate3.FromInt(immediate.immediate2.GetAsInt());
		immediate4.FromInt(immediate.immediate4.GetAsInt());
	}

	uint32_t ToRawInstruction() const
	{
		return opcode    .GetField() | 
			   immediate1.GetField() | 
			   immediate2.GetField() | 
			   funct3    .GetField() | 
			   rs1       .GetField() | 
			   rs2       .GetField() | 
			   immediate3.GetField() | 
			   immediate4.GetField();
	}
};

struct UJType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> rd;
	BitField<0b0000'0000'0000'1111'1111'0000'0000'0000> immediate1;
	BitField<0b0000'0000'0001'0000'0000'0000'0000'0000> immediate2;
	BitField<0b0111'1111'1110'0000'0000'0000'0000'0000> immediate3;
	BitField<0b1000'0000'0000'0000'0000'0000'0000'0000> immediate4;

	UJType(const uint32_t rawInstruction)
	{
		opcode    .FromField(rawInstruction);
		rd        .FromField(rawInstruction);
		immediate1.FromField(rawInstruction);
		immediate2.FromField(rawInstruction);
		immediate3.FromField(rawInstruction);
		immediate4.FromField(rawInstruction);
	}
	UJType()
	{ }

	int32_t GetImmediate() const
	{
		UJImmediate immediate;
		immediate.immediate1.FromInt(immediate3.GetAsInt());
		immediate.immediate2.FromInt(immediate2.GetAsInt());
		immediate.immediate3.FromInt(immediate1.GetAsInt());
		immediate.immediate4.FromInt(immediate4.GetAsInt());

		return immediate.ToImmediate();
	}
	void SetImmediate(const uint32_t value)
	{
		const UJImmediate ujImmediate(value);
		immediate1.FromInt(ujImmediate.immediate3.GetAsInt());
		immediate2.FromInt(ujImmediate.immediate2.GetAsInt());
		immediate3.FromInt(ujImmediate.immediate1.GetAsInt());
		immediate4.FromInt(ujImmediate.immediate4.GetAsInt());
	}

	uint32_t ToRawInstruction() const
	{
		return opcode    .GetField() | 
			   rd        .GetField() | 
			   immediate1.GetField() | 
			   immediate2.GetField() | 
			   immediate3.GetField() | 
			   immediate4.GetField();
	}
};

struct UType
{
	BitField<0b0000'0000'0000'0000'0000'0000'0111'1111> opcode;
	BitField<0b0000'0000'0000'0000'0000'1111'1000'0000> rd;
	BitField<0b1111'1111'1111'1111'1111'0000'0000'0000> immediate;

	UType(const uint32_t rawInstruction)
	{
		opcode   .FromField(rawInstruction);
		rd       .FromField(rawInstruction);
		immediate.FromField(rawInstruction);
	}
	UType()
	{ }

	int32_t GetImmediate() const
	{
		UImmediate uImmediate;
		uImmediate.immediate1.FromInt(immediate.GetAsInt());

		return uImmediate.ToImmediate();
	}
	void SetImmediate(const uint32_t value)
	{
		const UImmediate uImmediate(value);
		immediate.FromInt(uImmediate.immediate1.GetAsInt());
	}

	uint32_t ToRawInstruction() const
	{
		return opcode   .GetField() | 
			   rd       .GetField() | 
			   immediate.GetField();
	}
};