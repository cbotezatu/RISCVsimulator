#pragma once

#include <cstdint>
#include <string>

union Register
{
	int8_t byte;
	uint8_t ubyte;
	int16_t half;
	uint16_t uhalf;
	int32_t word;
	uint32_t uword;
};

enum class Regs : uint32_t
{
	x0,
	ra,
	sp,
	gp,
	tp,
	t0,
	t1,
	t2,
	s0,
	s1,
	a0,
	a1,
	a2,
	a3,
	a4,
	a5,
	a6,
	a7,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	s8,
	s9,
	s10,
	s11,
	t3,
	t4,
	t5,
	t6
};

const std::string& RegisterName(const uint32_t registerIndex);