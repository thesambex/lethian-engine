#pragma once

#include <vector>

#include "filesystem.hpp"

namespace Leth
{
	class LETH_PLATFORM_API VSF
	{
	public:
		struct MountPoint
		{
			int priority;
			std::unique_ptr<IFileSystem> fileSystem;
		};

		VSF() = default;
		VSF(const VSF &) = delete;
		VSF &operator=(const VSF &) = delete;
		VSF(VSF &&) = delete;
		VSF &operator=(VSF &&) = delete;

		static VSF &Get();

		void Mount(std::unique_ptr<IFileSystem> filesystem, int priority);

		std::unique_ptr<IFile> Open(const String &path);

	private:
		std::vector<MountPoint> m_Mounts;
	};
} // namespace Leth
