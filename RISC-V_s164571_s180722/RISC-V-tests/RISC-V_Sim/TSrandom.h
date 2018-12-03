#pragma once

#include <cstdint>

namespace FRandom {

	struct TCRandom
	{
		uint64_t x;
		uint64_t y;
		uint64_t z;
	};

	TCRandom GetTCRandom();
	int32_t RandomRange(TCRandom& random, const int32_t min, const int32_t max);
	bool RandomBool(TCRandom& random);
}