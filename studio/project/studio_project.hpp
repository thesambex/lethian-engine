#pragma once

#include <string>
#include <vector>
#include <filesystem>

class StudioProject
{
public:
	StudioProject() = default;
	~StudioProject() = default;

	struct Info
	{
		int versionMajor = 0;
		int versionMinor = 0;
		int versionPatch = 0;
		std::string name;
		std::vector<std::string> targetPlatforms{};
	};

public:
	static StudioProject &Get()
	{
		static StudioProject project;
		return project;
	}

	const Info &GetInfo() const
	{
		return m_Info;
	}

	const std::filesystem::path &GetProjectRoot()
	{
		return m_ProjectRoot;
	}

	std::string Create(const Info &info);
	void Load(const std::string &dir);

private:
	std::filesystem::path m_ProjectRoot;

	Info m_Info;
};
