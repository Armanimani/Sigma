#pragma once

#include <type_traits>

#include "../Common/types.hpp"

namespace sigma
{
	template<UInt32 Value>
	using Tag = std::integral_constant<UInt32, Value>;
}
