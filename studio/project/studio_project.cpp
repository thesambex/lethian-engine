#include <toml++/toml.hpp>

#include "studio_project.hpp"

std::string StudioProject::Create(const Info &info)
{
	toml::table tbl{
		{"project",
		 toml::table{

			 {"name", info.name},
			 {
				 "version",
				 toml::table{{"major", info.versionMajor}, {"minor", info.versionMinor}, {"patch", info.versionPatch}},

			 }}}};

	toml::array platforms{};

	for (const auto &platform : info.targetPlatforms)
	{
		platforms.push_back(platform);
	}

	if (auto project_table = tbl["project"].as_table())
	{
		project_table->insert_or_assign("platforms", std::move(platforms));
	}

	std::stringstream ss;
	ss << tbl;

	return ss.str();
}

void StudioProject::Load(const std::string &dir)
{
	const toml::table tbl = toml::parse_file(dir);

	m_Info = Info{
		.versionMajor = tbl["project"]["version"]["major"].value<int>().value(),
		.versionMinor = tbl["project"]["version"]["minor"].value<int>().value(),
		.versionPatch = tbl["project"]["version"]["patch"].value<int>().value(),
		.name = tbl["project"]["name"].value<std::string>().value(),
	};

	const auto platformsNode = tbl["project"]["platforms"];
	if (const toml::array *platforms = platformsNode.as_array())
	{
		for (const auto &el : *platforms)
		{
			if (const auto &platform = el.value<std::string>())
			{
				m_Info.targetPlatforms.push_back(platform.value());
			}
		}
	}

	std::filesystem::path path(dir);

	m_ProjectRoot = path.parent_path();
}
