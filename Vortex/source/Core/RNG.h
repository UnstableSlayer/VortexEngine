#pragma once
#include "Core.h"

namespace Vortex
{
	class RNG
	{
	public:
		static uint32_t Rand()
		{
			m_Seed += 0xe120fc15;
			uint64_t tmp;
			tmp = (uint64_t)m_Seed * 0x4a39b70d;
			uint32_t m1 = (tmp >> 32) ^ tmp;
			tmp = (uint64_t)m1 * 0x12fad5c9;
			uint32_t m2 = (tmp >> 32) ^ tmp;
			return m2;
		}

		static uint32_t RandRange(uint32_t min, uint32_t max)
		{
			return min + Rand() % ((max + 1) - min);
		}

		static float RandFloat()
		{
			return (float)(Rand() % 10001) / 10000.f;
		}

		inline static uint32_t m_Seed;
	};
}