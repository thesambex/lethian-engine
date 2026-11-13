#include <lethian/core/logger.hpp>

#include "windows_display.hpp"
#include "windows_callback.hpp"

namespace Leth
{
	const TCHAR *_className = "LethianWinClass";

	CWinDisplay::CWinDisplay(const String &title, const int &width, const int &height)
		: ADisplay(width, height), m_Title(title)
	{
	}

	bool CWinDisplay::Initialize()
	{
		const HINSTANCE hInstance = GetModuleHandle(nullptr);

		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEX));

		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.hInstance = hInstance;
		wcex.lpszClassName = _className;
		wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex.lpfnWndProc = &WindowProc;

		if (!RegisterClassEx(&wcex))
		{
			LETH_CORE_CRITICAL("Failed to register Windows class");
			return false;
		}

		m_Window = CreateWindowEx(0, _className, m_Title.CStr(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
								  width, height, nullptr, nullptr, hInstance, nullptr);

		if (!m_Window)
		{
			LETH_CORE_CRITICAL("Failed to create window");
			return false;
		}

		ShowWindow(m_Window, SW_SHOWMAXIMIZED);

		RECT rect{};
		GetClientRect(m_Window, &rect);

		width = rect.right - rect.left;
		width = rect.bottom - rect.top;

		return true;
	}

	bool CWinDisplay::PoolEvents()
	{
		while (PeekMessage(&m_Msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (m_Msg.message == WM_QUIT)
			{
				return false;
			}

			TranslateMessage(&m_Msg);
			DispatchMessage(&m_Msg);
		}
	}
} // namespace Leth
