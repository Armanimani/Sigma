#include <gtest/gtest.h>
#include <array>


#include "Sigma/Engine/DataStructures/Iterators/random_access_iterator.hpp"

using namespace sigma;

auto get_mocked_container()
{
	return std::array<int, 4>{10, 11, 12, 13};
}

TEST(RandomAccessIterator, construction_default)
{
	RandomAccessIterator<std::array<int, 4>, int, std::size_t> iterator{};
	ASSERT_TRUE(&iterator);
}

TEST(RandomAccessIterator, construction_container)
{
	auto container = get_mocked_container();
	auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container);
	ASSERT_TRUE(&iterator);
}

TEST(RandomAccessIterator, construction_container_offset)
{
	auto container = get_mocked_container();
	auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 10);
	ASSERT_TRUE(&iterator);
}

TEST(RandomAccessIterator, operator_plusEqual)
{
	auto container = get_mocked_container();
	auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container);
	ASSERT_EQ(*iterator, 10);

	iterator += 2;
	ASSERT_EQ(*iterator, 12);
}

TEST(RandomAccessIterator, operator_minusEqual)
{
	auto container = get_mocked_container();
	auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	ASSERT_EQ(*iterator, 13);

	iterator -= 2;
	ASSERT_EQ(*iterator, 11);
}

TEST(RandomAccessIterator, operator_plus_value)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container);
	ASSERT_EQ(*iterator, 10);

	const auto new_iterator = iterator + 2;
	ASSERT_EQ(*iterator, 10);
	ASSERT_EQ(*new_iterator, 12);
}

TEST(RandomAccessIterator, operator_minus_value)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	ASSERT_EQ(*iterator, 13);

	const auto new_iterator = iterator - 2;
	ASSERT_EQ(*iterator, 13);
	ASSERT_EQ(*new_iterator, 11);
}

TEST(RandomAccessIterator, operator_preIncrement)
{
	auto container = get_mocked_container();
	auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container);
	ASSERT_EQ(*iterator, 10);

	++iterator;
	ASSERT_EQ(*iterator, 11);
}

TEST(RandomAccessIterator, operator_preDecrement)
{
	auto container = get_mocked_container();
	auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	ASSERT_EQ(*iterator, 13);

	--iterator;
	ASSERT_EQ(*iterator, 12);
}

TEST(RandomAccessIterator, operator_postIncrement)
{
	auto container = get_mocked_container();
	auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container);
	ASSERT_EQ(*iterator, 10);

	const auto new_iterator = iterator++;
	ASSERT_EQ(*iterator, 10);
	ASSERT_EQ(*new_iterator, 11);
}

TEST(RandomAccessIterator, operator_postDecrement)
{
	auto container = get_mocked_container();
	auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	ASSERT_EQ(*iterator, 13);

	const auto new_iterator = iterator--;
	ASSERT_EQ(*iterator, 13);
	ASSERT_EQ(*new_iterator, 12);
}

TEST(RandomAccessIterator, operator_plus_iterator)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	const auto other_iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 1);
	ASSERT_EQ(*iterator, 13);
	ASSERT_EQ(*other_iterator, 11);

	ASSERT_EQ(iterator + other_iterator, 4);
}

TEST(RandomAccessIterator, operator_minus_iterator)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	const auto other_iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 1);
	ASSERT_EQ(*iterator, 13);
	ASSERT_EQ(*other_iterator, 11);

	ASSERT_EQ(iterator - other_iterator, 2);
}

TEST(RandomAccessIterator, operator_equality)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	const auto other_iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);

	ASSERT_TRUE(iterator == iterator);
	ASSERT_TRUE(other_iterator == other_iterator);
	ASSERT_TRUE(iterator == other_iterator);
}

TEST(RandomAccessIterator, operator_inequality)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	const auto other_iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 2);

	ASSERT_TRUE(iterator == iterator);
	ASSERT_TRUE(other_iterator == other_iterator);
	ASSERT_TRUE(iterator != other_iterator);
}

TEST(RandomAccessIterator, operator_lessThan)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	const auto other_iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 2);
	const auto clone_iterator = iterator;

	ASSERT_FALSE(iterator < iterator);
	ASSERT_TRUE(other_iterator < iterator);
	ASSERT_FALSE(iterator < other_iterator);
	ASSERT_FALSE(iterator < clone_iterator);
}

TEST(RandomAccessIterator, operator_greaterThan)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	const auto other_iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 2);
	const auto clone_iterator = iterator;

	ASSERT_FALSE(iterator > iterator);
	ASSERT_FALSE(other_iterator > iterator);
	ASSERT_TRUE(iterator > other_iterator);
	ASSERT_FALSE(iterator > clone_iterator);
}

TEST(RandomAccessIterator, operator_lessThanEqual)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	const auto other_iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 2);
	const auto clone_iterator = iterator;

	ASSERT_TRUE(iterator <= iterator);
	ASSERT_TRUE(other_iterator <= iterator);
	ASSERT_FALSE(iterator <= other_iterator);
	ASSERT_TRUE(iterator <= clone_iterator);
}

TEST(RandomAccessIterator, operator_greaterThanEqual)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 3);
	const auto other_iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 2);
	const auto clone_iterator = iterator;

	ASSERT_TRUE(iterator >= iterator);
	ASSERT_FALSE(other_iterator >= iterator);
	ASSERT_TRUE(iterator >= other_iterator);
	ASSERT_TRUE(iterator >= clone_iterator);
}

TEST(RandomAccessIterator, operator_arrow)
{
	struct Data
	{
		float value{};
	};

	std::array<Data, 2> container{};
	container[0] = Data{ 10 };
	container[1] = Data{ 20 };
	
	const auto iterator = RandomAccessIterator<std::array<Data, 2>, Data, std::size_t>(container, 1);
	ASSERT_EQ(iterator->value, 20);

	iterator->value = 99;
	ASSERT_EQ(iterator->value, 99);
}

TEST(RandomAccessIterator, operator_dereference)
{
	auto container = get_mocked_container();
	const auto iterator = RandomAccessIterator<std::array<int, 4>, int, std::size_t>(container, 2);
	ASSERT_EQ(*iterator, 12);

	*iterator = 99;
	ASSERT_EQ(*iterator, 99);
}