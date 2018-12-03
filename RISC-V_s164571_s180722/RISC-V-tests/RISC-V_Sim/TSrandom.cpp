#include <mutex> 
#include <cstdint>
#include "TSrandom.h"

namespace FRandom {
	static std::mutex initRandomLock;

	static uint64_t init_x = 236432356;
	static uint64_t init_y = 395824682;
	static uint64_t init_z = 443425897;

	TCRandom GetTCRandom()
	{
		initRandomLock.lock();
		const TCRandom newRandom =
		{
			init_x,
			init_y,
			init_z
		};

		init_x++;
		init_y++;
		init_z++;
		initRandomLock.unlock();

		return newRandom;
	}

	static inline uint64_t FastRandom(TCRandom& random)
	{
		random.x ^= random.x << 16;
		random.x ^= random.x >> 5;
		random.x ^= random.x << 1;

		const uint64_t t = random.x;
		random.x = random.y;
		random.y = random.z;
		random.z = t ^ random.x ^ random.y;

		return random.z;
	}

	int32_t RandomRange(TCRandom& random, const int32_t min, const int32_t max)
	{
		const uint64_t z = FastRandom(random);

		return min + (z % (max - min + 1));
	}

	bool RandomBool(TCRandom& random)
	{
		return FastRandom(random) & 1;
	}
}
