#pragma once

#include <Windows.h>
#include <filesystem>

#include "../file.hpp"

namespace Leth
{
	class LETH_PLATFORM_API WinFile : public IFile
	{
	public:
		explicit WinFile(const std::filesystem::path &path);
		~WinFile() override;

		bool Open();
		void Close();

		std::uint64_t Size() const override;
		std::uint64_t Tell() const override;
		bool Seek(std::uint64_t offset) override;

		std::uint64_t Read(std::span<std::byte> buffer, std::uint64_t size) override;

	private:
		std::filesystem::path m_Path;

		HANDLE m_Handle = INVALID_HANDLE_VALUE;
	};
} // namespace Leth
