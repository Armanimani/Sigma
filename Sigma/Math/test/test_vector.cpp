#include <gtest/gtest.h>

#include <Sigma/Math/Vector.hpp>

using namespace sigma::math;

TEST(Vector, Constructor_Default)
{
	constexpr Vector<int, 2> vec{};

	EXPECT_EQ(vec[0], 0);
	EXPECT_EQ(vec[1], 0);
}

TEST(Vector, Constructor_Fill)
{
	constexpr Vector<int, 2> vec{10};

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 10);
}

TEST(Vector, Constructor_Array)
{
	constexpr Vector<int, 2> vec{ std::array<int, 2> {10, 11}};

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 11);
}

TEST(Vector, Constructor_TwoValue)
{
	constexpr Vector<int, 2> vec{ 10, 11 };

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 11);
}

TEST(Vector, Constructor_ThreeValue)
{
	constexpr Vector<int, 3> vec{ 10, 11, 12 };

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 11);
	EXPECT_EQ(vec[2], 12);
}

TEST(Vector, Constructor_FourValue)
{
	constexpr Vector<int, 4> vec{ 10, 11, 12, 14 };

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 11);
	EXPECT_EQ(vec[2], 12);
	EXPECT_EQ(vec[3], 14);
}

TEST(Vector, OperatorBracket_Const)
{
	constexpr Vector<int, 2> vec{ 10, 11 };
	
	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 11);
}

TEST(Vector, OperatorBracket_NonConst)
{
	Vector<int, 2> vec{ 10, 11 };

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 11);

	vec[0] = 2;
	vec[1] = 5;
	
	EXPECT_EQ(vec[0], 2);
	EXPECT_EQ(vec[1], 5);
}

TEST(Vector, OperatorCall_Const)
{
	constexpr Vector<int, 2> vec{ 10, 11 };

	EXPECT_EQ(vec(0), 10);
	EXPECT_EQ(vec(1), 11);
}

TEST(Vector, OperatorCall_NonConst)
{
	Vector<int, 2> vec{ 10, 11 };

	EXPECT_EQ(vec(0), 10);
	EXPECT_EQ(vec(1), 11);

	vec(0) = 2;
	vec(1) = 5;

	EXPECT_EQ(vec(0), 2);
	EXPECT_EQ(vec(1), 5);
}

TEST(Vector, OperatorEqual_Integer)
{
	constexpr Vector<int, 2> first{ 10, 12 };
	constexpr Vector<int, 2> second{ 10, 12 };

	EXPECT_TRUE(first == second);
	EXPECT_FALSE(first != second);
}

TEST(Vector, OperatorNotEqual_Integer)
{
	constexpr Vector<int, 2> first{ 10, 12 };
	constexpr Vector<int, 2> second{ 10, 13 };

	EXPECT_TRUE(first != second);
	EXPECT_FALSE(first == second);
}

TEST(Vector, OperatorEqual_Float)
{
	constexpr Vector <float , 2 > first{ 10.0f, 12.0f };
	constexpr Vector<float, 2> second{ 10.0f, 12.0f };

	EXPECT_TRUE(first == second);
	EXPECT_FALSE(first != second);
}

TEST(Vector, OperatorNotEqual_Float)
{
	constexpr Vector <float, 2 > first{ 10.0f, 12.0f };
	constexpr Vector<float, 2> second{ 10.0001f, 12.0f };

	EXPECT_TRUE(first != second);
	EXPECT_FALSE(first == second);
}

TEST(Vector, OperatorAssignment_Vector_SameSize_SameType)
{
	constexpr Vector<int, 2> source{ 10, 11 };
	constexpr auto target{ source };
	
	EXPECT_EQ(target[0], 10);
	EXPECT_EQ(target[1], 11);
}

TEST(Vector, OperatorAssignment_Vector_SmallerSize_SameType)
{
	constexpr Vector<int, 3> source{ 10, 11, 10 };
	Vector<int, 3> target = source.get_xy();
	
	EXPECT_EQ(target[0], 10);
	EXPECT_EQ(target[1], 11);
	EXPECT_EQ(target[2], 0);
}

TEST(Vector, OperatorAssignment_Vector_SameSize_DifferentType)
{
	constexpr Vector<int16_t, 2> source{ 10, 11 };
	Vector<float, 2> target = source;
	
	EXPECT_FLOAT_EQ(target[0], 10.0f);
	EXPECT_FLOAT_EQ(target[1], 11.0f);
}

TEST(Vector, OperatorAssignment_Vector_SmallerSize_DifferentType)
{
	constexpr Vector<int16_t, 3> source{ 10, 11, 13 };
	Vector<float, 3> target = source.get_xy();

	EXPECT_FLOAT_EQ(target[0], 10.0f);
	EXPECT_FLOAT_EQ(target[1], 11.0f);
	EXPECT_FLOAT_EQ(target[2], 0.0f);
}

TEST(Vector, CopyConstructor)
{
	constexpr Vector<int, 2> source{ 10, 11 };
	constexpr auto target = source;

	EXPECT_EQ(target[0], 10);
	EXPECT_EQ(target[1], 11);
}

TEST(Vector, CopyAssignment)
{
	constexpr Vector<int, 2> source{ 10, 11 };
	constexpr auto target = source;

	EXPECT_EQ(target[0], 10);
	EXPECT_EQ(target[1], 11);
}

TEST(Vector, MoveConstructor)
{
	Vector<int, 2> source{ 10, 11 };
	auto target{ std::move(source) };

	EXPECT_EQ(target[0], 10);
	EXPECT_EQ(target[1], 11);
}

TEST(Vector, MoveAssignment)
{
	Vector<int, 2> source{ 10, 11 };
	auto target = std::move(source);

	EXPECT_EQ(target[0], 10);
	EXPECT_EQ(target[1], 11);
}

TEST(Vector, AccessorsXYZW_Const)
{
	constexpr Vector<int, 4> source{ 10, 11, 12, 13 };

	EXPECT_EQ(source.x(), 10);
	EXPECT_EQ(source.y(), 11);
	EXPECT_EQ(source.z(), 12);
	EXPECT_EQ(source.w(), 13);
}

TEST(Vector, AccessorsXYZW_NonConst)
{
	Vector<int, 4> source{ 10, 11, 12, 13 };

	EXPECT_EQ(source.x(), 10);
	EXPECT_EQ(source.y(), 11);
	EXPECT_EQ(source.z(), 12);
	EXPECT_EQ(source.w(), 13);

	source.x() = 20;
	source.y() = 21;
	source.z() = 22;
	source.w() = 23;

	EXPECT_EQ(source.x(), 20);
	EXPECT_EQ(source.y(), 21);
	EXPECT_EQ(source.z(), 22);
	EXPECT_EQ(source.w(), 23);
}

TEST(Vector, AccessorsRGBA_Const)
{
	constexpr Vector<int, 4> source{ 10, 11, 12, 13 };

	EXPECT_EQ(source.r(), 10);
	EXPECT_EQ(source.g(), 11);
	EXPECT_EQ(source.b(), 12);
	EXPECT_EQ(source.a(), 13);
}

TEST(Vector, NonConstAccessorsRGBA_NonConst)
{
	Vector<int, 4> source{ 10, 11, 12, 13 };

	EXPECT_EQ(source.r(), 10);
	EXPECT_EQ(source.g(), 11);
	EXPECT_EQ(source.b(), 12);
	EXPECT_EQ(source.a(), 13);

	source.r() = 20;
	source.g() = 21;
	source.b() = 22;
	source.a() = 23;

	EXPECT_EQ(source.r(), 20);
	EXPECT_EQ(source.g(), 21);
	EXPECT_EQ(source.b(), 22);
	EXPECT_EQ(source.a(), 23);
}

TEST(Vector, SliceXY)
{
	constexpr Vector<int, 4> source{ 10, 11, 12, 13 };
	const auto target{ source.get_xy() };

	EXPECT_EQ(target.x(), 10);
	EXPECT_EQ(target.y(), 11);
}

TEST(Vector, SliceXYZ)
{
	constexpr Vector<int, 4> source{ 10, 11, 12, 13 };
	const auto target{ source.get_xyz() };

	EXPECT_EQ(target.x(), 10);
	EXPECT_EQ(target.y(), 11);
	EXPECT_EQ(target.z(), 12);
}

TEST(Vector, SliceRGB)
{
	constexpr Vector<int, 4> source{ 10, 11, 12, 13 };
	const auto target{ source.get_rgb() };

	EXPECT_EQ(target.r(), 10);
	EXPECT_EQ(target.g(), 11);
	EXPECT_EQ(target.b(), 12);
}

TEST(Vector, Operator_Plus_Vector)
{
	constexpr Vector<int, 2> lhs{ 1, 2 };
	constexpr Vector<int, 2> rhs{ 3, 4 };
	const auto result = lhs + rhs;

	EXPECT_EQ(result[0], 1 + 3);
	EXPECT_EQ(result[1], 2 + 4);
}

TEST(Vector, Operator_Minus_Vector)
{
	constexpr Vector<int, 2> lhs{ 1, 2 };
	constexpr Vector<int, 2> rhs{ 3, 4 };
	const auto result = lhs - rhs;

	EXPECT_EQ(result[0], 1 - 3);
	EXPECT_EQ(result[1], 2 - 4);
}

TEST(Vector, Operator_Multiply_Vector)
{
	constexpr Vector<int, 2> lhs{ 1, 2 };
	constexpr Vector<int, 2> rhs{ 3, 4 };
	const auto result = lhs * rhs;

	EXPECT_EQ(result[0], 1 * 3);
	EXPECT_EQ(result[1], 2 * 4);
}

TEST(Vector, Operator_Divide_Vector)
{
	constexpr Vector<float, 2> lhs{ 1.0f, 2.0f };
	constexpr Vector<float, 2> rhs{ 3.0f, 4.0f };
	const auto result = lhs / rhs;

	EXPECT_FLOAT_EQ(result[0], 1.0f / 3.0f);
	EXPECT_FLOAT_EQ(result[1], 2.0f / 4.0f);
}

TEST(Vector, Operator_Plus_Type)
{
	constexpr Vector<int, 2> lhs{ 1, 2 };
	constexpr auto rhs = 2;
	const auto result = lhs + rhs;

	EXPECT_EQ(result[0], 1 + 2);
	EXPECT_EQ(result[1], 2 + 2);
}

TEST(Vector, Operator_Minus_Type)
{
	constexpr Vector<int, 2> lhs{ 1, 2 };
	constexpr auto rhs = 2;
	const auto result = lhs - rhs;

	EXPECT_EQ(result[0], 1 - 2);
	EXPECT_EQ(result[1], 2 - 2);
}

TEST(Vector, Operator_Multiply_Type)
{
	constexpr Vector<int, 2> lhs{ 1, 2 };
	constexpr auto rhs = 2;
	const auto result = lhs * rhs;

	EXPECT_EQ(result[0], 1 * 2);
	EXPECT_EQ(result[1], 2 * 2);
}

TEST(Vector, Operator_Divide_Type)
{
	constexpr Vector<float, 2> lhs{ 1.0f, 2.0f };
	constexpr auto rhs = 2.0f;
	const auto result = lhs / rhs;

	EXPECT_FLOAT_EQ(result[0], 1.0f / 2.0f);
	EXPECT_FLOAT_EQ(result[1], 2.0f / 2.0f);
}

TEST(Vector, Operator_PlusEqual_Vector)
{
	Vector<int, 2> vec{ 1, 2 };
	constexpr Vector<int, 2> other{ 3, 4 };
	vec += other;

	EXPECT_EQ(vec[0], 1 + 3);
	EXPECT_EQ(vec[1], 2 + 4);
}

TEST(Vector, Operator_MinusEqual_Vector)
{
	Vector<int, 2> vec{ 1, 2 };
	constexpr Vector<int, 2> other{ 3, 4 };
	vec -= other;

	EXPECT_EQ(vec[0], 1 - 3);
	EXPECT_EQ(vec[1], 2 - 4);
}

TEST(Vector, Operator_MultiplyEqual_Vector)
{
	Vector<int, 2> vec{ 1, 2 };
	constexpr Vector<int, 2> other{ 3, 4 };
	vec *= other;

	EXPECT_EQ(vec[0], 1 * 3);
	EXPECT_EQ(vec[1], 2 * 4);
}

TEST(Vector, Operator_DivideEqual_Vector)
{
	Vector<float, 2> vec{ 1.0f, 2.0f };
	constexpr Vector<float, 2> other{ 3.0f, 4.0f };
	vec /= other;

	EXPECT_FLOAT_EQ(vec[0], 1.0f / 3.0f);
	EXPECT_FLOAT_EQ(vec[1], 2.0f / 4.0f);
}

TEST(Vector, Operator_PlusEqual_Type)
{
	Vector<int, 2> vec{ 1, 2 };
	constexpr auto other = 2;
	vec += other;

	EXPECT_EQ(vec[0], 1 + 2);
	EXPECT_EQ(vec[1], 2 + 2);
}

TEST(Vector, Operator_MinusEqual_Type)
{
	Vector<int, 2> vec{ 1, 2 };
	constexpr auto other = 2;
	vec -= other;

	EXPECT_EQ(vec[0], 1 - 2);
	EXPECT_EQ(vec[1], 2 - 2);
}

TEST(Vector, Operator_MultiplyEqual_Type)
{
	Vector<int, 2> vec{ 1, 2 };
	constexpr auto other = 2;
	vec *= other;

	EXPECT_EQ(vec[0], 1 * 2);
	EXPECT_EQ(vec[1], 2 * 2);
}

TEST(Vector, Operator_DivideEqual_Type)
{
	Vector<float, 2> vec{ 1.0f, 2.0f };
	constexpr auto other = 2.0f;
	vec /= other;

	EXPECT_FLOAT_EQ(vec[0], 1.0f / 2.0f);
	EXPECT_FLOAT_EQ(vec[1], 2.0f / 2.0f);
}

TEST(Vector, Operator_Minus)
{
	constexpr Vector<int, 2> vec{ 1, 2 };
	constexpr auto other = -vec;

	EXPECT_EQ(other[0], -1);
	EXPECT_EQ(other[1], -2);
}

TEST(Vector, Negate)
{
	Vector<int, 2> vec{ 1, 2 };
	vec.negate();

	EXPECT_EQ(vec[0], -1);
	EXPECT_EQ(vec[1], -2);
}

TEST(Vector, Fill)
{
	Vector<int, 2> vec{ 1, 2 };
	vec.fill(11);

	EXPECT_EQ(vec[0], 11);
	EXPECT_EQ(vec[1], 11);
}

TEST(Vector, SetValues_Two)
{
	Vector<int, 4> vec{ 1, 2, 3, 4 };
	vec.set_values(10, 11);

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 11);
	EXPECT_EQ(vec[2], 3);
	EXPECT_EQ(vec[3], 4);
}

TEST(Vector, SetValues_Three)
{
	Vector<int, 4> vec{ 1, 2, 3, 4 };
	vec.set_values(10, 11, 12);

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 11);
	EXPECT_EQ(vec[2], 12);
	EXPECT_EQ(vec[3], 4);
}

TEST(Vector, SetValues_Four)
{
	Vector<int, 4> vec{ 1, 2, 3, 4 };
	vec.set_values(10, 11, 12, 13);

	EXPECT_EQ(vec[0], 10);
	EXPECT_EQ(vec[1], 11);
	EXPECT_EQ(vec[2], 12);
	EXPECT_EQ(vec[3], 13);
}

TEST(Vector, GetLength)
{
	constexpr Vector<short, 3> vec{ 0, 2, 3 };

	EXPECT_FLOAT_EQ(vec.get_length(), std::sqrtf(0 * 0 + 2 * 2 + 3 * 3));
}

TEST(Vector, GetSquaredLength)
{
	constexpr Vector<short, 3> vec{ 0, 2, 3 };

	EXPECT_EQ(vec.get_squared_length(), 0 * 0 + 2 * 2 + 3 * 3);
}

TEST(Vector, IsNormalized_ExpectTrue)
{
	constexpr Vector<float, 2> vec{ 0.6f, 0.8f };

	EXPECT_TRUE(vec.is_normalized());
}

TEST(Vector, IsNormalized_ExpectFalse)
{
	constexpr Vector<float, 2> vec{ 0.6f, 0.8001f };

	EXPECT_FALSE(vec.is_normalized());
}

TEST(Vector, Normalize_KnownValue)
{
	Vector<float, 2> vec{ 6.0f, 8.0f };
	EXPECT_FALSE(vec.is_normalized());

	vec.normalize();
	EXPECT_FLOAT_EQ(vec[0], 0.6f);
	EXPECT_FLOAT_EQ(vec[1], 0.8f);
	EXPECT_TRUE(vec.is_normalized());
}

TEST(Vector, Normalize_UnknownValue)
{
	Vector<float, 2> vec{ 6.124f, 8.134f };
	EXPECT_FALSE(vec.is_normalized());

	vec.normalize();
	EXPECT_TRUE(vec.is_normalized());
}

TEST(Vector, GeDistance)
{
	constexpr Vector<float, 3> vec{ 0.0f, 2.0f, 3.0f };
	constexpr Vector<float, 3> other{ 1.0f, -2.0f, 3.0f };

	constexpr auto expected_squared_length =
		(vec[0] - other[0]) * (vec[0] - other[0]) +
		(vec[1] - other[1]) * (vec[1] - other[1]) +
		(vec[2] - other[2]) * (vec[2] - other[2]);

	EXPECT_FLOAT_EQ(vec.get_distance(other), std::sqrt(expected_squared_length));
	EXPECT_FLOAT_EQ(other.get_distance(vec), std::sqrt(expected_squared_length));
}

TEST(Vector, GetSquaredDistance)
{
	constexpr Vector<float, 3> vec{ 0.0f, 2.0f, 3.0f };
	constexpr Vector<float, 3> other{ 1.0f, -2.0f, 3.0f };

	const auto expected_squared_length =
		(vec[0] - other[0]) * (vec[0] - other[0]) +
		(vec[1] - other[1]) * (vec[1] - other[1]) +
		(vec[2] - other[2]) * (vec[2] - other[2]);

	EXPECT_FLOAT_EQ(vec.get_squared_distance(other), expected_squared_length);
	EXPECT_FLOAT_EQ(other.get_squared_distance(vec), expected_squared_length);
}