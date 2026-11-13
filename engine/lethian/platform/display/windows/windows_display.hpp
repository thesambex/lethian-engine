#pragma once

#include <Windows.h>

#include <lethian/core/containers/string.hpp>

#include "../display.hpp"

namespace Leth
{
	class LETH_PLATFORM_API CWinDisplay : public ADisplay
	{
	public:
		explicit CWinDisplay(const String &title, const int &width, const int &height);
		~CWinDisplay() = default;

		bool Initialize() override;
		bool PoolEvents() override;

		const HWND &GetWindow() const
		{
			return m_Window;
		}

		const int &GetExitCode() const
		{
			return static_cast<int>(m_Msg.wParam);
		}

	private:
		String m_Title;

		HWND m_Window = nullptr;
		MSG m_Msg{};
	};
} // namespace Leth
