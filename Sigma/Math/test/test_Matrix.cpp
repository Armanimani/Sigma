#include <gtest/gtest.h>

#include <Sigma/Math/Matrix.hpp>

using namespace sigma::math;

constexpr auto get_lhs_for_multiplies()
{
	Matrix<int, 2, 3> mat{};
	mat(0, 0) = 1;
	mat(0, 1) = 2;
	mat(0, 2) = 3;
	mat(1, 0) = 4;
	mat(1, 1) = 5;
	mat(1, 2) = 6;

	return mat;
}

constexpr auto get_rhs_for_multiplies()
{
	Matrix<int, 3, 2> mat{};
	mat(0, 0) = 11;
	mat(0, 1) = 12;
	mat(1, 0) = 13;
	mat(1, 1) = 14;
	mat(2, 0) = 15;
	mat(2, 1) = 16;

	return mat;
}

TEST(Matrix, ConstructorDefault)
{
	constexpr Matrix<int, 2, 2> mat{};

	EXPECT_EQ(mat(0, 0), 0);
	EXPECT_EQ(mat(0, 1), 0);
	EXPECT_EQ(mat(1, 0), 0);
	EXPECT_EQ(mat(1, 1), 0);
}

TEST(Matrix, ConstructorDiagonal)
{
	constexpr Matrix<int, 2, 2> mat{10};

	EXPECT_EQ(mat(0, 0), 10);
	EXPECT_EQ(mat(0, 1), 0);
	EXPECT_EQ(mat(1, 0), 0);
	EXPECT_EQ(mat(1, 1), 10);
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

TEST(Matrix, OperatorAt_Const)
{
	constexpr Matrix<int, 2, 2> mat{};

	EXPECT_EQ(mat.at(0, 0), 0);
	EXPECT_EQ(mat.at(0, 1), 0);
	EXPECT_EQ(mat.at(1, 0), 0);
	EXPECT_EQ(mat.at(1, 1), 0);
}

TEST(Matrix, OperatorAt_NonConst)
{
	Matrix<int, 2, 2> mat{};

	EXPECT_EQ(mat.at(0, 0), 0);
	EXPECT_EQ(mat.at(0, 1), 0);
	EXPECT_EQ(mat.at(1, 0), 0);
	EXPECT_EQ(mat(1, 1), 0);

	mat.at(0, 0) = 1;
	mat.at(0, 1) = 2;
	mat.at(1, 0) = 3;
	mat.at(1, 1) = 4;

	EXPECT_EQ(mat.at(0, 0), 1);
	EXPECT_EQ(mat.at(0, 1), 2);
	EXPECT_EQ(mat.at(1, 0), 3);
	EXPECT_EQ(mat.at(1, 1), 4);
}

TEST(Matrix, OperatorMultiplies)
{
	const auto lhs = get_lhs_for_multiplies();
	const auto rhs = get_rhs_for_multiplies();

	auto result = lhs * rhs;

	EXPECT_EQ(result.at(0, 0), 1 * 11 + 2 * 13 + 3 * 15);
	EXPECT_EQ(result.at(0, 1), 1 * 12 + 2 * 14 + 3 * 16);
	EXPECT_EQ(result.at(1, 0), 4 * 11 + 5 * 13 + 6 * 15);
	EXPECT_EQ(result.at(1, 1), 4 * 12 + 5 * 14 + 6 * 16);

	EXPECT_EQ(result.k_row_count, 2);
	EXPECT_EQ(result.k_column_count, 2);
}