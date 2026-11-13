#pragma once

#include <memory>

#include <lethian/core/containers/string.hpp>

#include "file.hpp"

namespace Leth
{
	class LETH_PLATFORM_API IFileSystem
	{
	public:
		virtual ~IFileSystem() = default;

		virtual bool Exists(const String &path) const = 0;

		virtual std::unique_ptr<IFile> Open(const String &path) const = 0;
	};
} // namespace Leth
