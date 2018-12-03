#pragma once

#include<cstdint>
#include "BitField.h"

template<uint32_t N>
int32_t SignExtend(int32_t toExtend)
{
	return (toExtend << (32 - N)) >> (32 - N);
}

struct SImmediate
{
	BitField<0b0000'0000'0000'0000'0000'0000'0001'1111> immediate1;
	BitField<0b0000'0000'0000'0000'0000'1111'1110'0000> immediate2;

	SImmediate(const uint32_t immediate)
	{
		immediate1.FromField(immediate);
		immediate2.FromField(immediate);
	}
	SImmediate()
	{ }

	uint32_t ToImmediate() const
	{
		return SignExtend<12>(immediate1.GetField() |
							  immediate2.GetField());
	}
};

struct SBImmediate
{
	BitField<0b0000'0000'0000'0000'0000'0000'0001'1110> immediate1;
	BitField<0b0000'0000'0000'0000'0000'0111'1110'0000> immediate2;
	BitField<0b0000'0000'0000'0000'0000'1000'0000'0000> immediate3;
	BitField<0b0000'0000'0000'0000'0001'0000'0000'0000> immediate4;

	SBImmediate(const uint32_t immediate)
	{
		immediate1.FromField(immediate);
		immediate2.FromField(immediate);
		immediate3.FromField(immediate);
		immediate4.FromField(immediate);
	}
	SBImmediate()
	{ }

	uint32_t ToImmediate() const
	{
		return SignExtend<13>(immediate1.GetField() |
							  immediate2.GetField() |
							  immediate3.GetField() |
							  immediate4.GetField());
	}
};

struct UJImmediate
{
	BitField<0b0000'0000'0000'0000'0000'0111'1111'1110> immediate1;
	BitField<0b0000'0000'0000'0000'0000'1000'0000'0000> immediate2;
	BitField<0b0000'0000'0000'1111'1111'0000'0000'0000> immediate3;
	BitField<0b0000'0000'0001'0000'0000'0000'0000'0000> immediate4;

	UJImmediate(const uint32_t immediate)
	{
		immediate1.FromField(immediate);
		immediate2.FromField(immediate);
		immediate3.FromField(immediate);
		immediate4.FromField(immediate);
	}
	UJImmediate()
	{ }

	uint32_t ToImmediate() const
	{
		return SignExtend<21>(immediate1.GetField() |
						      immediate2.GetField() |
						      immediate3.GetField() |
						      immediate4.GetField());
	}
};

struct UImmediate
{
	BitField<0b1111'1111'1111'1111'1111'0000'0000'0000> immediate1;

	UImmediate(const uint32_t immediate)
	{
		immediate1.FromField(immediate);
	}
	UImmediate()
	{ }

	uint32_t ToImmediate() const
	{
		return immediate1.GetField();
	}
};