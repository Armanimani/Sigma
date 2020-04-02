#pragma once

#include <Sigma/Math/Vector.hpp>

namespace sigma::math
{
	template <typename T, std::size_t N>
	constexpr T dot(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		return lhs.dot(rhs);
	}

	template <typename T, std::size_t N, std::enable_if_t<N==3>* = nullptr>
	constexpr auto cross(const Vector<T, N>& lhs, const Vector<T, N>& rhs) noexcept
	{
		return lhs.cross(rhs);
	}
}