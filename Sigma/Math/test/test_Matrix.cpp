#include <gtest/gtest.h>

#include <Sigma/Math/Matrix.hpp>

using namespace sigma::math;

TEST(Matrix, DefaultConstructor)
{
	constexpr Matrix<int, 2, 2> mat{};

	EXPECT_EQ(mat(0, 0), 0);
	EXPECT_EQ(mat(0, 1), 0);
	EXPECT_EQ(mat(1, 0), 0);
	EXPECT_EQ(mat(1, 1), 0);
}

TEST(Matrix, OperatorCall_Const)
{
	constexpr Matrix<int, 2, 2> mat{};

	EXPECT_EQ(mat(0, 0), 0);
	EXPECT_EQ(mat(0, 1), 0);
	EXPECT_EQ(mat(1, 0), 0);
	EXPECT_EQ(mat(1, 1), 0);
}

TEST(Matrix, OperatorCall_NonConst)
{
	Matrix<int, 2, 2> mat{};

	EXPECT_EQ(mat(0, 0), 0);
	EXPECT_EQ(mat(0, 1), 0);
	EXPECT_EQ(mat(1, 0), 0);
	EXPECT_EQ(mat(1, 1), 0);

	mat(0, 0) = 1;
	mat(0, 1) = 2;
	mat(1, 0) = 3;
	mat(1, 1) = 4;

	EXPECT_EQ(mat(0, 0), 1);
	EXPECT_EQ(mat(0, 1), 2);
	EXPECT_EQ(mat(1, 0), 3);
	EXPECT_EQ(mat(1, 1), 4);
}