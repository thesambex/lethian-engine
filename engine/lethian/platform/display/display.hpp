#pragma once

#include "../platform_api.hpp"

namespace Leth
{
	class LETH_PLATFORM_API ADisplay
	{
	public:
		ADisplay(const int &width, const int &height);
		virtual ~ADisplay() = default;

		virtual bool Initialize() = 0;
		virtual bool PoolEvents() = 0;

		const int &GetWidth() const
		{
			return width;
		}

		const int &GetHeight() const
		{
			return height;
		}

	protected:
		int width = 0, height = 0;
	};
} // namespace Leth
