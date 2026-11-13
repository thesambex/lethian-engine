#include <algorithm>

#include "windows_file.hpp"

namespace Leth
{
	WinFile::WinFile(const std::filesystem::path &path) : m_Path(path)
	{
	}

	WinFile::~WinFile()
	{
		Close();
	}

	bool WinFile::Open()
	{
		m_Handle = CreateFileW(m_Path.wstring().c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, nullptr);

		return m_Handle != INVALID_HANDLE_VALUE;
	}

	void WinFile::Close()
	{
		if (m_Handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_Handle);
			m_Handle = INVALID_HANDLE_VALUE;
		}
	}

	std::uint64_t WinFile::Size() const
	{
		if (m_Handle == INVALID_HANDLE_VALUE)
			return 0;

		LARGE_INTEGER size;
		if (GetFileSizeEx(m_Handle, &size))
		{
			return static_cast<std::uint64_t>(size.QuadPart);
		}

		return 0;
	}

	std::uint64_t WinFile::Tell() const
	{
		if (m_Handle == INVALID_HANDLE_VALUE)
			return 0;

		LARGE_INTEGER zero = {0};
		LARGE_INTEGER currentPos;

		if (SetFilePointerEx(m_Handle, zero, &currentPos, FILE_CURRENT))
		{
			return static_cast<std::uint64_t>(currentPos.QuadPart);
		}

		return 0;
	}

	bool WinFile::Seek(std::uint64_t offset)
	{
		if (m_Handle == INVALID_HANDLE_VALUE)
			return false;

		LARGE_INTEGER liOffset;
		liOffset.QuadPart = static_cast<LONGLONG>(offset);

		return ::SetFilePointerEx(m_Handle, liOffset, nullptr, FILE_BEGIN) != FALSE;
	}

	std::uint64_t WinFile::Read(std::span<std::byte> buffer, std::uint64_t size)
	{
		if (m_Handle == INVALID_HANDLE_VALUE)
			return 0;

		const DWORD bytesToRead = static_cast<DWORD>(std::min<std::uint64_t>(size, buffer.size()));
		DWORD bytesRead = 0;

		// TODO: Maybe async read in the future
		const BOOL success = ReadFile(m_Handle, buffer.data(), bytesToRead, &bytesRead, nullptr);
		if (!success)
		{
			return 0;
		}

		return static_cast<std::uint64_t>(bytesRead);
	}
} // namespace Leth
