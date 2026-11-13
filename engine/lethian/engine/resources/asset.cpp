#include <fstream>

#include <lethian/core/logger.hpp>

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

	CAsset CAsset::CreateFromFS(std::unique_ptr<IFile> file)
	{
		CAsset asset;

		const auto fileSize = file->Size();

		std::vector<std::byte> fileBuffer(fileSize);
		std::span fileData(fileBuffer);

		const int bytesReaded = file->Read(fileData, fileSize);
		if (bytesReaded == 0)
		{
			LETH_CORE_WARN("Failed to load asset");

			return asset;
		}

		// Parse asset data
		if (fileData.size_bytes() < sizeof(Header))
		{
			LETH_CORE_WARN("Asset to small");

			return asset;
		}

		Header header;
		std::memcpy(&header, fileData.data(), sizeof(Header));
		asset.m_Header = header;

		std::span<const std::byte> assetData = fileData.subspan(sizeof(Header));
		asset.m_DataBuffer.assign(assetData.begin(), assetData.end());
		asset.m_Data = std::span<std::byte>(asset.m_DataBuffer);

		return asset;
	}
} // namespace Leth
