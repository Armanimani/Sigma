#pragma once

#include <cassert>
#include <vector>
#include <algorithm>

#include "Sigma/Engine/Utilities/vector_utils.hpp"
#include "Sigma/Engine/DataStructures/Iterators/random_access_iterator.hpp"

namespace sigma
{
	template <typename T>
	class SparseSet
	{
	public:
		using element_type = T;
		using size_type = std::size_t;
		using iterator_type = RandomAccessIterator<std::vector<element_type>, element_type, size_type>;
		using const_iterator_type = ConstRandomAccessIterator<std::vector<element_type>, element_type, size_type>;

		SparseSet() = default;
		explicit SparseSet(size_type capacity);

		template <typename... Args>
		void emplace(size_type index, Args&& ...args);
		void add_reference(size_type index, size_type reference_index) noexcept;

		void erase(size_type index) noexcept;

		void reserve(size_type capacity);
		
		[[nodiscard]] auto capacity() const noexcept;
		[[nodiscard]] auto size() const noexcept;
		
		[[nodiscard]] bool is_empty() const noexcept;
		[[nodiscard]] bool is_full() const noexcept;

		[[nodiscard]] bool has_element(size_type index) const noexcept;

		[[nodiscard]] const_iterator_type cbegin() const noexcept;
		[[nodiscard]] const_iterator_type cend() const noexcept;
		[[nodiscard]] iterator_type begin() noexcept;
		[[nodiscard]] iterator_type end() noexcept;

		[[nodiscard]] element_type* get_element_pointer(size_type index) noexcept;
		[[nodiscard]] const element_type* get_element_pointer(size_type index) const noexcept;

		[[nodiscard]] element_type& get_element(size_type index) noexcept;
		[[nodiscard]] const element_type& get_element(size_type index) const noexcept;

		[[nodiscard]] element_type& operator[](size_type index) noexcept;
		[[nodiscard]] const element_type& operator[](size_type index) const noexcept;

		void clear();
	private:		
		std::vector<element_type> m_dense{};
		std::vector<element_type*> m_sparse{};
	};

	
	template <typename T>
	SparseSet<T>::SparseSet(const size_type capacity)
	{
		reserve(capacity);
	}

	template <typename T>
	template <typename... Args>
	void SparseSet<T>::emplace(const size_type index, Args&&... args)
	{
		assert(size() < capacity());

		erase(index);
		
		m_dense.emplace_back(std::forward<Args>(args)...);	
		safe_assignment(m_sparse, index, &m_dense.back());
	}

	template <typename T>
	void SparseSet<T>::add_reference(const size_type index, const size_type reference_index) noexcept
	{
		safe_assignment(m_sparse, index, get_element_pointer(reference_index));
	}

	template <typename T>
	void SparseSet<T>::erase(const size_type index) noexcept
	{
		if (!has_element(index))
		{
			return;
		}

		auto item_address = m_sparse[index];
		
		const auto reference_count = std::count(m_sparse.cbegin(), m_sparse.cend(), item_address);
		assert(reference_count != 0);
		if (reference_count > 1)
		{
			m_sparse[index] = nullptr;
			return;
		}
		
		auto back_address = &m_dense.back();
		std::swap(*item_address, *back_address);

		std::replace_if(m_sparse.begin(), m_sparse.end(),
			[=](const element_type* address)
			{
				return address == item_address;
			}, 
			nullptr
		);

		std::replace_if(m_sparse.begin(), m_sparse.end(),
			[=](const element_type* address)
			{
				return address == back_address;
			}, 
			item_address
		);

		m_dense.pop_back();
	}

	template <typename T>
	void SparseSet<T>::reserve(const size_type capacity)
	{
		assert(is_empty());
		m_dense.reserve(capacity);
	}

	template <typename T>
	auto SparseSet<T>::capacity() const noexcept
	{
		return m_dense.capacity();
	}

	template <typename T>
	auto SparseSet<T>::size() const noexcept
	{
		return m_dense.size();
	}

	template <typename T>
	bool SparseSet<T>::is_empty() const noexcept
	{
		return m_dense.empty();
	}

	template <typename T>
	bool SparseSet<T>::is_full() const noexcept
	{
		return m_dense.size() >= m_dense.capacity();
	}

	template <typename T>
	bool SparseSet<T>::has_element(const size_type index) const noexcept
	{
		return (index < m_sparse.size() && m_sparse[index]);
	}

	template <typename T>
	typename SparseSet<T>::const_iterator_type SparseSet<T>::cbegin() const noexcept
	{
		return { m_dense, 0 };
	}

	template <typename T>
	typename SparseSet<T>::const_iterator_type SparseSet<T>::cend() const noexcept
	{
		return { m_dense, m_dense.size() };
	}

	template <typename T>
	typename SparseSet<T>::iterator_type SparseSet<T>::begin() noexcept
	{
		return { m_dense, 0 };
	}

	template <typename T>
	typename SparseSet<T>::iterator_type SparseSet<T>::end() noexcept
	{
		return { m_dense, m_dense.size() };
	}

	template <typename T>
	typename SparseSet<T>::element_type* SparseSet<T>::get_element_pointer(const size_type index) noexcept
	{
		return has_element(index) ? m_sparse[index] : nullptr;
	}

	template <typename T>
	const typename SparseSet<T>::element_type* SparseSet<T>::get_element_pointer(const size_type index) const noexcept
	{
		return has_element(index) ? m_sparse[index] : nullptr;
	}

	template <typename T>
	typename SparseSet<T>::element_type& SparseSet<T>::get_element(const size_type index) noexcept
	{
		return *m_sparse[index];
	}

	template <typename T>
	const typename SparseSet<T>::element_type& SparseSet<T>::get_element(const size_type index) const noexcept
	{
		return *m_sparse[index];
	}

	template <typename T>
	typename SparseSet<T>::element_type& SparseSet<T>::operator[](const size_type index) noexcept
	{
		return *m_sparse[index];
	}

	template <typename T>
	const typename SparseSet<T>::element_type& SparseSet<T>::operator[](const size_type index) const noexcept
	{
		return *m_sparse[index];
	}

	template <typename T>
	void SparseSet<T>::clear()
	{
		m_dense.clear();
		m_sparse.clear();
	}
}
