#include "string.hpp"

namespace Leth
{
	template class StringBase<char>;
	template class DynamicString<char, 32>;
} // namespace Leth
