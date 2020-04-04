#include <gtest/gtest.h>

#include <Sigma/Math/Matrix.hpp>

using namespace sigma::math;

constexpr auto get_default_2x3()
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

constexpr auto get_default_3x2()
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

constexpr auto get_default_2x2()
{
	Matrix<int, 2, 2> mat{};
	mat(0, 0) = 11;
	mat(0, 1) = 12;
	mat(1, 0) = 13;
	mat(1, 1) = 14;

	return mat;
}

constexpr auto get_alternative_2x2()
{
	Matrix<int, 2, 2> mat{};
	mat(0, 0) = 1;
	mat(0, 1) = 2;
	mat(1, 0) = 3;
	mat(1, 1) = 4;
	
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

TEST(Matrix, ConstructorArray)
{
	constexpr std::array<int, 6> data{ 1, 2, 3, 4, 5, 6 };
	constexpr Matrix<int, 2, 3> mat_2x3{ data };

	EXPECT_EQ(mat_2x3(0, 0), 1);
	EXPECT_EQ(mat_2x3(0, 1), 3);
	EXPECT_EQ(mat_2x3(0, 2), 5);
	EXPECT_EQ(mat_2x3(1, 0), 2);
	EXPECT_EQ(mat_2x3(1, 1), 4);
	EXPECT_EQ(mat_2x3(1, 2), 6);

	constexpr Matrix<int, 3, 2> mat_3x2{ data };

	EXPECT_EQ(mat_3x2(0, 0), 1);
	EXPECT_EQ(mat_3x2(0, 1), 4);
	EXPECT_EQ(mat_3x2(1, 0), 2);
	EXPECT_EQ(mat_3x2(1, 1), 5);
	EXPECT_EQ(mat_3x2(2, 0), 3);
	EXPECT_EQ(mat_3x2(2, 1), 6);
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

TEST(Matrix, OperatorMultiply)
{
	const auto lhs = get_default_2x3();
	const auto rhs = get_default_3x2();
	auto result = lhs * rhs;

	EXPECT_EQ(result.at(0, 0), lhs(0, 0) * rhs(0, 0) + lhs(0, 1) * rhs(1, 0) + lhs(0, 2) * rhs(2, 0));
	EXPECT_EQ(result.at(0, 1), lhs(0, 0) * rhs(0, 1) + lhs(0, 1) * rhs(1, 1) + lhs(0, 2) * rhs(2, 1));
	EXPECT_EQ(result.at(1, 0), lhs(1, 0) * rhs(0, 0) + lhs(1, 1) * rhs(1, 0) + lhs(1, 2) * rhs(2, 0));
	EXPECT_EQ(result.at(1, 1), lhs(1, 0) * rhs(0, 1) + lhs(1, 1) * rhs(1, 1) + lhs(1, 2) * rhs(2, 1));

	EXPECT_EQ(result.k_row_count, 2);
	EXPECT_EQ(result.k_column_count, 2);
}

TEST(Matrix, OperatorPlus)
{
	constexpr auto lhs = get_default_2x2();
	constexpr auto rhs = get_alternative_2x2();
	auto result = lhs + rhs;

	EXPECT_EQ(result(0, 0), lhs(0, 0) + rhs(0, 0));
	EXPECT_EQ(result(0, 1), lhs(0, 1) + rhs(0, 1));
	EXPECT_EQ(result(1, 0), lhs(1, 0) + rhs(1, 0));
	EXPECT_EQ(result(1, 1), lhs(1, 1) + rhs(1, 1));
}

TEST(Matrix, OperatorMinus)
{
	constexpr auto lhs = get_default_2x2();
	constexpr auto rhs = get_alternative_2x2();
	auto result = lhs - rhs;
	
	EXPECT_EQ(result(0, 0), lhs(0, 0) - rhs(0, 0));
	EXPECT_EQ(result(0, 1), lhs(0, 1) - rhs(0, 1));
	EXPECT_EQ(result(1, 0), lhs(1, 0) - rhs(1, 0));
	EXPECT_EQ(result(1, 1), lhs(1, 1) - rhs(1, 1));
}

TEST(Matrix, OperatorMultiplyEqual)
{
	auto mat = get_default_2x2();
	auto original = mat;
	constexpr auto other = get_alternative_2x2();
	mat *= other;

	EXPECT_EQ(mat.at(0, 0), original(0, 0) * other(0, 0) + original(0, 1) * other(1, 0));
	EXPECT_EQ(mat.at(0, 1), original(0, 0) * other(0, 1) + original(0, 1) * other(1, 1));
	EXPECT_EQ(mat.at(1, 0), original(1, 0) * other(0, 0) + original(1, 1) * other(1, 0));
	EXPECT_EQ(mat.at(1, 1), original(1, 0) * other(0, 1) + original(1, 1) * other(1, 1));

	EXPECT_EQ(mat.k_row_count, 2);
	EXPECT_EQ(mat.k_column_count, 2);
}

TEST(Matrix, OperatorPlusEqual)
{
	auto mat = get_default_2x2();
	auto original = mat;
	constexpr auto other = get_alternative_2x2();
	mat += other;

	EXPECT_EQ(mat.at(0, 0), original(0, 0) + other(0, 0));
	EXPECT_EQ(mat.at(0, 1), original(0, 1) + other(0, 1));
	EXPECT_EQ(mat.at(1, 0), original(1, 0) + other(1, 0));
	EXPECT_EQ(mat.at(1, 1), original(1, 1) + other(1, 1));

	EXPECT_EQ(mat.k_row_count, 2);
	EXPECT_EQ(mat.k_column_count, 2);
}

TEST(Matrix, OperatorMinusEqual)
{
	auto mat = get_default_2x2();
	auto original = mat;
	constexpr auto other = get_alternative_2x2();
	mat -= other;

	EXPECT_EQ(mat.at(0, 0), original(0, 0) - other(0, 0));
	EXPECT_EQ(mat.at(0, 1), original(0, 1) - other(0, 1));
	EXPECT_EQ(mat.at(1, 0), original(1, 0) - other(1, 0));
	EXPECT_EQ(mat.at(1, 1), original(1, 1) - other(1, 1));

	EXPECT_EQ(mat.k_row_count, 2);
	EXPECT_EQ(mat.k_column_count, 2);
}