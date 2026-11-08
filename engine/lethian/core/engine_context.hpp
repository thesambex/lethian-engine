#pragma once

#include "core_api.hpp"
#include "containers/string.hpp"

namespace Leth
{
	struct ApplicationInfo
	{
		String name;
		int majorVersion;
		int minorVersion;
		int versionPatch;
	};

	class LETH_CORE_API EngineContext
	{
	public:
		static ApplicationInfo &GetAppInfo();
	};

} // namespace Leth
