#ifdef WIN32
#include "windows/windows_file.hpp"
#endif // WIN32

#include "physical_filesystem.hpp"

namespace Leth
{
	PhysicalFileSystem::PhysicalFileSystem(const String rootPath) : m_RootPath(rootPath)
	{
	}

	bool PhysicalFileSystem::Exists(const String &path) const
	{
		const auto fullPath = std::filesystem::path(m_RootPath.CStr()) / path.CStr();

		return std::filesystem::exists(fullPath);
	}

	std::unique_ptr<IFile> PhysicalFileSystem::Open(const String &path) const
	{
		const auto fullPath = std::filesystem::path(m_RootPath.CStr()) / path.CStr();

#ifdef WIN32
		auto file = std::make_unique<WinFile>(std::filesystem::path(fullPath));
#endif // WIN32

		if (!file->Open())
		{
			return nullptr;
		}

		return file;
	}
} // namespace Leth
