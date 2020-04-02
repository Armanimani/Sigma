#include <gtest/gtest.h>

#include <Sigma/Math/vector_utils.hpp>

using namespace sigma::math;

TEST(VectorUtils, Dot)
{
	constexpr Vector<int, 3> lhs{ 1, 2, 3 };
	constexpr Vector<int, 3> rhs{ 4, 5, 6 };

	EXPECT_EQ(dot(lhs, rhs), lhs.dot(rhs));
}

TEST(VectorUtils, Cross)
{
	constexpr Vector<int, 3> lhs{ 1, 2, 3 };
	constexpr Vector<int, 3> rhs{ 4, 5, 6 };

	EXPECT_EQ(cross(lhs, rhs), lhs.cross(rhs));
}