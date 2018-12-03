#pragma once

#include <cstdint>


template<uint32_t MASK>
class BitField
{
private:
	uint32_t field;

public:
	void FromField(const uint32_t rawInstruction);
	void FromInt(const uint32_t value);
	uint32_t GetField() const;
	uint32_t GetAsInt() const;
};


template<uint32_t MASK>
constexpr uint32_t Shift_From_Mask()
{
	if (MASK & 1 || MASK == 0)
	{
		return 0;
	}
	const uint32_t newMask = MASK >> 1;
	return Shift_From_Mask<newMask>() + 1;
}

template<uint32_t MASK>
void BitField<MASK>::FromField(const uint32_t rawInstruction)
{
	field = rawInstruction & MASK;
}

template<uint32_t MASK>
void BitField<MASK>::FromInt(const uint32_t value)
{
	field = (value << Shift_From_Mask<MASK>()) & MASK;
}

template<uint32_t MASK>
uint32_t BitField<MASK>::GetField() const
{
	return field;
}

template<uint32_t MASK>
uint32_t BitField<MASK>::GetAsInt() const
{
	return field >> Shift_From_Mask<MASK>();
}