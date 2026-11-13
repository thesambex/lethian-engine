#pragma once

#include <cstdint>

#include "containers/string.hpp"
#include "core_api.hpp"

namespace Leth
{
	class LETH_CORE_API UUID
	{
	public:
		UUID() = default;
		~UUID();

		/// <summary>
		/// Generate UUID version 4
		/// </summary>
		static UUID V4();

		const std::uint64_t &Get() const
		{
			return *m_Data;
		}

		const String &ToString() const;

	private:
		std::uint64_t *m_Data = nullptr;
	};
} // namespace Leth
