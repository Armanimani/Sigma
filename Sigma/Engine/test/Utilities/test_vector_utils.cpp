#include <gtest/gtest.h>

#include <Sigma/Engine/Utilities/vector_utils.hpp>

using namespace sigma;

TEST(safe_assignment, no_resize)
{
	std::vector<int> vector{};
	ASSERT_EQ(vector.size(), 0);
	
	vector.resize(10);
	ASSERT_EQ(vector.capacity(), 10);
	ASSERT_EQ(vector.size(), 10);

	safe_assignment(vector, 0, 10);
	ASSERT_EQ(vector.capacity(), 10);
	ASSERT_EQ(vector.size(), 10);
	
	safe_assignment(vector, 9, 20);
	ASSERT_EQ(vector.capacity(), 10);
	ASSERT_EQ(vector.size(), 10);
}

TEST(safe_assignment, resize)
{
	std::vector<int> vector{};
	ASSERT_EQ(vector.size(), 0);

	vector.reserve(10);
	ASSERT_EQ(vector.capacity(), 10);
	ASSERT_EQ(vector.size(), 0);

	safe_assignment(vector, 0, 10);
	ASSERT_EQ(vector.capacity(), 10);
	ASSERT_EQ(vector.size(), 1);

	safe_assignment(vector, 9, 20);
	ASSERT_EQ(vector.capacity(), 10);
	ASSERT_EQ(vector.size(), 10);
}
