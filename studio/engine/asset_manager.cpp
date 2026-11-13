#include <QMimeDatabase>
#include <QMimeType>
#include <QFile>

#include <lethian/engine/resources/asset.hpp>
#include <lethian/core/uuid.hpp>

#include "asset_manager.hpp"

int AssetManager::FileToAsset(const QString &sourcePath, const QString &targetPath)
{
	// Read file contents
	QFile file(sourcePath);
	if (!file.open(QIODevice::ReadOnly))
	{
		return 2;
	}

	const QByteArray fileData = file.readAll();

	file.close();

	if (fileData.isEmpty())
	{
		return 3;
	}

	const std::span<const std::byte> assetData(reinterpret_cast<const std::byte *>(fileData.constData()),
											   fileData.size());

	// Get file type
	QMimeDatabase db;
	const QMimeType mime = db.mimeTypeForData(fileData);

	Leth::CAsset::AssetType assetType;
	if (mime.name().startsWith("image/"))
	{
		assetType = Leth::CAsset::AssetType::Texture;
	}
	else if (mime.preferredSuffix() == "hlsl" || sourcePath.endsWith(".hlsl", Qt::CaseInsensitive))
	{
		assetType = Leth::CAsset::AssetType::Shader;
	}
	else
	{
		return 1;
	}

	// Write asset
	const Leth::CAsset::Header assetHeader{
		.id = Leth::UUID::V4().Get(),
		.version = 1,
		.dataSize = static_cast<std::uint64_t>(fileData.size()),
		.type = assetType,
	};

	std::filesystem::path assetPath(targetPath.toStdString());

	return Leth::CAsset::Write(assetPath, assetHeader, assetData) ? 0 : -1;
}
