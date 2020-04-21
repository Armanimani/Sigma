# pragma once

#include <iterator>

namespace sigma
{
	// TODO: Add concept for minimum requirement of the container
	template <typename ContainerType, typename ElementType, typename SizeType>
	class RandomAccessIterator
	{
	public:
		using container_type = ContainerType;
		using value_type = ElementType;
		using difference_type = SizeType;
		using reference = ElementType&;
		using pointer = ElementType*;
		using iterator_category = std::random_access_iterator_tag;

		RandomAccessIterator() = default;
		
		explicit RandomAccessIterator(container_type& container)
			: m_container{ &(container) } {}
		
		RandomAccessIterator(container_type& container, difference_type offset)
			: m_container{ &container }, m_offset{ offset } {};

		RandomAccessIterator& operator+=(const difference_type value) noexcept
		{
			m_offset += value;
			return *this;
		}
		
		RandomAccessIterator& operator-=(const difference_type value) noexcept
		{
			m_offset -= value;
			return *this;
		}

		RandomAccessIterator operator+(const difference_type value) const noexcept
		{
			return { *m_container, m_offset + value };
		}
		
		RandomAccessIterator operator-(const difference_type value) const noexcept
		{
			return { *m_container, m_offset - value };
		}

		RandomAccessIterator& operator++() noexcept
		{
			++m_offset;
			return *this;
		}
		
		RandomAccessIterator& operator--() noexcept
		{
			--m_offset;
			return *this;
		}
		
		RandomAccessIterator operator++(int) noexcept
		{
			return { *m_container, m_offset + 1 };
		}
		
		RandomAccessIterator operator--(int) noexcept
		{
			return { *m_container, m_offset - 1 };
		}

		difference_type operator+(const RandomAccessIterator& other) const noexcept
		{
			return m_offset + other.m_offset;
		}
		
		difference_type operator-(const RandomAccessIterator& other) const noexcept
		{
			return m_offset - other.m_offset;
		}

		bool operator==(const RandomAccessIterator& other) const noexcept
		{
			return (m_container == other.m_container) && (m_offset == other.m_offset);
		}
		
		bool operator!=(const RandomAccessIterator& other) const noexcept
		{
			return !(*this == other);
		}

		bool operator<(const RandomAccessIterator& other) const noexcept
		{
			assert(m_container == other.m_container);
			return m_offset < other.m_offset;
		}
		
		bool operator>(const RandomAccessIterator& other) const noexcept
		{
			assert(m_container == other.m_container);
			return m_offset > other.m_offset;
		}

		bool operator<=(const RandomAccessIterator& other) const noexcept
		{
			return !(*this > other);
		}
		
		bool operator>=(const RandomAccessIterator& other) const noexcept
		{
			return !(*this < other);
		}

		pointer operator->() const noexcept
		{
			assert(m_offset < m_container->size());
			return &((*m_container)[m_offset]);
		}

		reference operator*() const noexcept
		{
			return *operator->();
		}

	private:
		container_type* m_container{};
		difference_type m_offset{};
	};
}
