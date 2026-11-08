#include "engine_context.hpp"

namespace Leth
{
	ApplicationInfo &EngineContext::GetAppInfo()
	{
		static ApplicationInfo info;
		return info;
	}
} // namespace Leth
