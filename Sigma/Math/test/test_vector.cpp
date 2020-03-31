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

TEST(Vector, AccessorsRGBA_CONST)
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