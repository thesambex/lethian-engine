#pragma once

#include <span>
#include <cstdint>
#include <cstddef>

#include "../platform_api.hpp"

namespace Leth
{
	class LETH_PLATFORM_API IFile
	{
	public:
		virtual ~IFile() = default;

		virtual std::uint64_t Size() const = 0;
		virtual std::uint64_t Tell() const = 0;
		virtual bool Seek(std::uint64_t offset) = 0;

		virtual std::uint64_t Read(std::span<std::byte> buffer, std::uint64_t size) = 0;
	};
} // namespace Leth
