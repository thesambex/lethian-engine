#include <fstream>

#include "asset.hpp"

namespace Leth
{
	bool CAsset::Write(const std::filesystem::path &filePath, const Header &header, std::span<const std::byte> data)
	{
		std::filesystem::path targetPath = filePath;
		targetPath.replace_extension(".leth");

		std::ofstream file(targetPath, std::ios::binary);
		if (!file.is_open())
		{
			return false;
		}

		file.write(reinterpret_cast<const char *>(&header), sizeof(Header));
		file.write(reinterpret_cast<const char *>(data.data()), data.size_bytes());

		return true;
	}
} // namespace Leth
