#include <gtest/gtest.h>

#include <Sigma/Engine/DataStructures/SparseSet.hpp>

using namespace sigma;

TEST(SparseSet, construction_default)
{
	const auto set = SparseSet<int>();
	ASSERT_EQ(set.capacity(), 0);
	ASSERT_TRUE(set.is_empty());
}

TEST(SparseSet, construction_with_reservation)
{
	const auto set = SparseSet<int>(10);
	ASSERT_EQ(set.capacity(), 10);
	ASSERT_TRUE(set.is_empty());
}

TEST(SparseSet, reserve)
{
	auto set = SparseSet<int>();
	set.reserve(10);
	ASSERT_EQ(set.capacity(), 10);

	auto reserved_set = SparseSet<int>(10);
	ASSERT_EQ(reserved_set.capacity(), 10);
	
	reserved_set.reserve(20);
	ASSERT_EQ(reserved_set.capacity(), 20);
}

TEST(SparseSet, capacity)
{
	auto set = SparseSet<int>();
	ASSERT_EQ(set.capacity(), 0);

	set.reserve(20);
	ASSERT_EQ(set.capacity(), 20);
}

TEST(SparseSet, size)
{
	auto set = SparseSet<int>();
	ASSERT_EQ(set.size(), 0);

	set.reserve(1);
	ASSERT_EQ(set.size(), 0);
	
	set.emplace(1, 10);
	ASSERT_EQ(set.size(), 1);
}

TEST(SparseSet, is_empty)
{
	auto set = SparseSet<int>(1);
	ASSERT_TRUE(set.is_empty());

	set.emplace(1, 10);
	ASSERT_FALSE(set.is_empty());
}

TEST(SparseSet, is_full)
{
	auto set = SparseSet<int>();
	ASSERT_TRUE(set.is_full());

	set.reserve(1);
	ASSERT_FALSE(set.is_full());
	
	set.emplace(0, 10);
	ASSERT_TRUE(set.is_full());
}

TEST(SparseSet, has_element)
{
	auto set = SparseSet<int>();
	ASSERT_FALSE(set.has_element(0));
	ASSERT_FALSE(set.has_element(1));

	set.reserve(2);
	ASSERT_FALSE(set.has_element(0));
	ASSERT_FALSE(set.has_element(1));

	set.emplace(1, 10);
	ASSERT_FALSE(set.has_element(0));
	ASSERT_TRUE(set.has_element(1));
}

TEST(SparseSet, get_element_nonConst)
{
	auto set = SparseSet<int>(5);
	ASSERT_EQ(set.size(), 0);

	set.emplace(1, 10);
	ASSERT_EQ(set.get_element_pointer(0), nullptr);
	ASSERT_EQ(set.get_element_pointer(10), nullptr);
	ASSERT_EQ(*set.get_element_pointer(1), 10);

	*set.get_element_pointer(1) = 20;
	ASSERT_EQ(set.get_element_pointer(0), nullptr);
	ASSERT_EQ(set.get_element_pointer(10), nullptr);
	ASSERT_EQ(*set.get_element_pointer(1), 20);
}

TEST(SparseSet, get_element_const)
{
	const auto set = SparseSet<int>(5);
	ASSERT_EQ(set.size(), 0);
	ASSERT_EQ(set.get_element_pointer(0), nullptr);
	ASSERT_EQ(set.get_element_pointer(10), nullptr);
}

TEST(SparseSet, empalce_fundamental_types)
{
	auto set = SparseSet<int>(1);
	ASSERT_EQ(set.size(), 0);

	set.emplace(1, 10);
	ASSERT_EQ(set.size(), 1);
}

TEST(SparseSet, emplace_class_type)
{
	struct Data
	{
		Data() = default;
		Data(const int int_data, const float float_data) : int_value{ int_data }, float_value{ float_data } {};
		int int_value{};
		float float_value{};
	};
	
	auto set = SparseSet<Data>(2);
	ASSERT_EQ(set.size(), 0);

	set.emplace(1);
	ASSERT_EQ(set.size(), 1);

	set.emplace(2, 2, 3.5f);
	ASSERT_EQ(set.size(), 2);
}

TEST(SparseSet, emplace_constructed_object)
{
	struct Data
	{
		Data() = default;
		Data(const int int_data, const float float_data) : int_value{ int_data }, float_value{ float_data } {};
		int int_value{};
		float float_value{};
	};

	auto set = SparseSet<Data>(2);
	ASSERT_EQ(set.size(), 0);

	auto data = Data();
	set.emplace(1, data);
	ASSERT_EQ(set.size(), 1);

	set.emplace(2, 2, 3.5f);
	ASSERT_EQ(set.size(), 2);
}

TEST(SparseSet, cbegin)
{
	auto set = SparseSet<int>(2);
	ASSERT_EQ(set.size(), 0);

	set.emplace(0, 10);
	set.emplace(1, 20);
	ASSERT_EQ(set.size(), 2);

	const auto iterator = set.cbegin();
	ASSERT_EQ(*iterator, 10);
	ASSERT_EQ(*(iterator + 1), 20);
}

TEST(SparseSet, cend)
{
	auto set = SparseSet<int>(2);
	ASSERT_EQ(set.size(), 0);
	ASSERT_EQ(set.cbegin(), set.cend());

	set.emplace(0, 10);
	set.emplace(1, 20);
	ASSERT_EQ(set.size(), 2);
	
	const auto iterator = set.cend();
	ASSERT_EQ(*(iterator - 1), 20);
	ASSERT_EQ(*(iterator - 2), 10);
}

TEST(SparseSet, begin)
{
	auto set = SparseSet<int>(2);
	ASSERT_EQ(set.size(), 0);

	set.emplace(0, 10);
	set.emplace(1, 20);
	ASSERT_EQ(set.size(), 2);

	const auto iterator = set.begin();
	ASSERT_EQ(*iterator, 10);
	ASSERT_EQ(*(iterator + 1), 20);

	*iterator = 11;
	*(iterator + 1) = 22;
	ASSERT_EQ(*iterator, 11);
	ASSERT_EQ(*(iterator + 1), 22);
}

TEST(SparseSet, end)
{
	auto set = SparseSet<int>(2);
	ASSERT_EQ(set.size(), 0);
	ASSERT_EQ(set.begin(), set.end());

	set.emplace(0, 10);
	set.emplace(1, 20);
	ASSERT_EQ(set.size(), 2);

	const auto iterator = set.end();
	ASSERT_EQ(*(iterator - 1), 20);
	ASSERT_EQ(*(iterator - 2), 10);

	*(iterator - 2) = 11;
	*(iterator - 1) = 22;
	ASSERT_EQ(*(iterator - 1), 22);
	ASSERT_EQ(*(iterator - 2), 11);
}

TEST(SparseSet, erase)
{
	auto set = SparseSet<int>(5);
	set.emplace(0, 10);
	set.emplace(1, 11);
	set.emplace(3, 33);
	ASSERT_EQ(set.size(), 3);
	ASSERT_EQ(*set.get_element_pointer(0), 10);
	ASSERT_EQ(*set.get_element_pointer(1), 11);
	ASSERT_EQ(set.get_element_pointer(2), nullptr);
	ASSERT_EQ(*set.get_element_pointer(3), 33);
	ASSERT_EQ(set.get_element_pointer(4), nullptr);

	set.erase(0);
	ASSERT_EQ(set.size(), 2);
	ASSERT_EQ(set.get_element_pointer(0), nullptr);
	ASSERT_EQ(*set.get_element_pointer(1), 11);
	ASSERT_EQ(set.get_element_pointer(2), nullptr);
	ASSERT_EQ(*set.get_element_pointer(3), 33);
	ASSERT_EQ(set.get_element_pointer(4), nullptr);

	set.emplace(0, 99);
	ASSERT_EQ(set.size(), 3);
	ASSERT_EQ(*set.get_element_pointer(0), 99);
	ASSERT_EQ(*set.get_element_pointer(1), 11);
	ASSERT_EQ(set.get_element_pointer(2), nullptr);
	ASSERT_EQ(*set.get_element_pointer(3), 33);
	ASSERT_EQ(set.get_element_pointer(4), nullptr);
}

TEST(SparseSet, add_reference)
{
	auto set = SparseSet<int>(7);
	set.emplace(0, 10);
	ASSERT_EQ(set.size(), 1);
	ASSERT_EQ(*set.get_element_pointer(0), 10);
	
	set.emplace(1, 11);
	ASSERT_EQ(set.size(), 2);
	ASSERT_EQ(*set.get_element_pointer(1), 11);
	
	set.add_reference(2, 0);
	ASSERT_EQ(set.size(), 2);
	ASSERT_EQ(*set.get_element_pointer(2), 10);
	
	set.emplace(3, 33);
	ASSERT_EQ(set.size(), 3);
	ASSERT_EQ(*set.get_element_pointer(3), 33);
	
	set.add_reference(4, 0);
	ASSERT_EQ(set.size(), 3);
	ASSERT_EQ(*set.get_element_pointer(4), 10);
	
	set.add_reference(5, 6);
	ASSERT_EQ(set.size(), 3);
	ASSERT_EQ(set.get_element_pointer(5), nullptr);
	
	set.erase(6);
	ASSERT_EQ(set.size(), 3);
	
	set.erase(5);
	ASSERT_EQ(set.size(), 3);
	
	set.erase(4);
	ASSERT_EQ(set.size(), 3);
	
	set.erase(3);
	ASSERT_EQ(set.size(), 2);
	
	set.erase(2);
	ASSERT_EQ(set.size(), 2);
	
	set.erase(1);
	ASSERT_EQ(set.size(), 1);
	
	set.erase(0);
	ASSERT_EQ(set.size(), 0);
}