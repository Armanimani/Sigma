#include <gtest/gtest.h>

#include <Sigma/Engine/DataStructures/SparseSet.hpp>

using namespace sigma;

TEST(SparseSet, Construction_Default)
{
	auto set = SparseSet<int>();
}

TEST(SparseSet, Construction_WithReservation)
{
	auto set = SparseSet<int>(10);
}

TEST(SparseSet, Reserve)
{
	auto set = SparseSet<int>();
	set.reserve(10);
	ASSERT_EQ(set.capacity(), 10);

	auto reserved_set = SparseSet<int>(10);
	ASSERT_EQ(reserved_set.capacity(), 10);
	
	reserved_set.reserve(20);
	ASSERT_EQ(reserved_set.capacity(), 20);
}

TEST(SparseSet, SparseReserve)
{
	auto set = SparseSet<int>();
	set.sparse_reserve(10);
	ASSERT_EQ(set.sparse_capacity(), 10);

	auto reserved_set = SparseSet<int>(10);
	ASSERT_EQ(reserved_set.sparse_capacity(), 0);

	reserved_set.sparse_reserve(20);
	ASSERT_EQ(reserved_set.sparse_capacity(), 20);
}

TEST(SparseSet, Capacity)
{
	auto set = SparseSet<int>();
	ASSERT_EQ(set.capacity(), 0);

	set.reserve(20);
	ASSERT_EQ(set.capacity(), 20);
}

TEST(SparseSet, SparseCapacity)
{
	auto set = SparseSet<int>();
	ASSERT_EQ(set.sparse_capacity(), 0);

	set.sparse_reserve(20);
	ASSERT_EQ(set.sparse_capacity(), 20);
}

TEST(SparseSet, ShrinkToFit)
{
	auto set = SparseSet<int>();
	ASSERT_EQ(set.capacity(), 0);

	set.reserve(10);
	ASSERT_EQ(set.capacity(), 10);

	set.shrink_to_fit();
	ASSERT_EQ(set.capacity(), 0);
}

TEST(SparseSet, Size)
{
	auto set = SparseSet<int>();
	ASSERT_EQ(set.size(), 0);

	set.construct(1, 10);
	ASSERT_EQ(set.size(), 1);
}

TEST(SparseSet, SparseSize)
{
	auto set = SparseSet<int>();
	ASSERT_EQ(set.size(), 0);

	constexpr std::size_t index{ 1 };
	set.construct(index, 10);
	ASSERT_TRUE(set.sparse_size() >= index);
}

TEST(SparseSet, Construct_NativeTypes)
{
	auto set = SparseSet<int>();
	ASSERT_EQ(set.size(), 0);

	set.construct(1, 10);

	ASSERT_EQ(set.size(), 1);
}