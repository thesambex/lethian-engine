#pragma once

#include <QString>

class AssetManager
{
public:
	static int FileToAsset(const QString &sourcePath, const QString &targetPath);
};
