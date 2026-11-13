#include "vsf.hpp"

namespace Leth
{
	VSF &VSF::Get()
	{
		static VSF vsf;
		return vsf;
	}

	void VSF::Mount(std::unique_ptr<IFileSystem> filesystem, int priority)
	{
		m_Mounts.push_back({.priority = priority, .fileSystem = std::move(filesystem)});
	}

	std::unique_ptr<IFile> VSF::Open(const String &path)
	{
		for (const auto &mount : m_Mounts)
		{
			auto file = mount.fileSystem->Open(path);
			if (file)
				return file;
		}

		return nullptr;
	}
} // namespace Leth
