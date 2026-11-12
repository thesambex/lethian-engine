#pragma once

#include <filesystem>
#include <span>
#include <cstddef>
#include <cstdint>

#include "../engine_api.hpp"

namespace Leth
{
	class LETH_ENGINE_API CAsset
	{
	public:
		enum class AssetType : std::uint8_t
		{
			Texture,
			Shader
		};

		// TODO: Create asset ID
		// TODO: Create asset specific type header
		struct Header
		{
			std::uint32_t version;
			std::uint64_t dataSize;
			AssetType type;
		};

		/// <summary>
		/// Write asset to disc
		/// </summary>
		/// <param name="filePath">Path to write asset</param>
		/// <param name="header">Asset header</param>
		/// <param name="data">Asset data</param>
		/// <returns></returns>
		static bool Write(const std::filesystem::path &filePath, const Header &header, std::span<const std::byte> data);

	private:
		Header m_Header;

		std::vector<std::byte> m_Data;
	};
} // namespace Leth
