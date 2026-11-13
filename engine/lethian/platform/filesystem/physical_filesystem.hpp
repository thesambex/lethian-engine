#pragma once

#include "filesystem.hpp"

namespace Leth
{
	class LETH_PLATFORM_API PhysicalFileSystem : public IFileSystem
	{
	public:
		explicit PhysicalFileSystem(const String rootPath);
		~PhysicalFileSystem() = default;

		bool Exists(const String &path) const override;

		std::unique_ptr<IFile> Open(const String &path) const override;

	private:
		String m_RootPath;
	};
} // namespace Leth
