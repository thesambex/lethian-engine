#pragma once

#include <filesystem>
#include <span>
#include <vector>
#include <cstddef>
#include <cstdint>

#include <lethian/platform/filesystem/file.hpp>

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

		// TODO: Create asset specific type header
#pragma pack(push, 1)
		struct Header
		{
			std::uint64_t id;
			std::uint32_t version = 1;
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

		/// <summary>
		/// Parse asset from file
		/// </summary>
		/// <param name="file">File from VSF</param>
		/// <returns></returns>
		static CAsset CreateFromFS(std::unique_ptr<IFile> file);

		const Header &GetHeader() const
		{
			return m_Header;
		}

		const std::span<std::byte> &GetData() const
		{
			return m_Data;
		}

	private:
		Header m_Header{};

		std::vector<std::byte> m_DataBuffer;
		std::span<std::byte> m_Data;
	};
} // namespace Leth
