#include <random>
#include <string>
#include <sstream>

#include "uuid.hpp"

namespace Leth
{
	UUID::~UUID()
	{
		if (m_Data)
		{
			delete m_Data;
		}
	}

	UUID UUID::V4()
	{
		static std::random_device rd;
		static std::mt19937_64 gen(rd());
		static std::uniform_int_distribution<uint64_t> dist;

		std::uint64_t p1 = dist(gen);
		std::uint64_t p2 = dist(gen);

		p1 = (p1 & 0xFFFFFFFFFFFF0FFFULL) | 0x0000000000004000ULL;
		p2 = (p2 & 0x3FFFFFFFFFFFFFFFULL) | 0x8000000000000000ULL;

		UUID uuid;
		uuid.m_Data = new std::uint64_t[36];
		uuid.m_Data[0] = p1;
		uuid.m_Data[1] = p2;

		return uuid;
	}

	const String &UUID::ToString() const
	{
		thread_local String s;
		s.Reserve(36);

		const uint8_t *bytes = reinterpret_cast<const uint8_t *>(m_Data);

		snprintf(s.Data(), 37, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", bytes[0],
				 bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7], bytes[8], bytes[9], bytes[10],
				 bytes[11], bytes[12], bytes[13], bytes[14], bytes[15]);

		return s;
	}
} // namespace Leth
