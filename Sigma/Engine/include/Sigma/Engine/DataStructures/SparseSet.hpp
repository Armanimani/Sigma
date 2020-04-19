#pragma once

#include <vector>

namespace sigma
{
	template <typename T>
	class SparseSet
	{
	public:
		class Iterator
		{
			friend class SparseSet<T>;
		};

		using element_type = T;
		using size_type = std::size_t;
		using iterator_type = Iterator;

		SparseSet() = default;
		explicit SparseSet(std::size_t capacity);

		template <typename... Args>
		void construct(std::size_t index, Args&& ...args);

		void reserve(std::size_t capacity);
		void sparse_reserve(std::size_t capacity);
		
		void shrink_to_fit();
		
		[[nodiscard]] std::size_t capacity() const noexcept;
		[[nodiscard]] std::size_t sparse_capacity() const noexcept;
		[[nodiscard]] std::size_t size() const noexcept;
		[[nodiscard]] std::size_t sparse_size() const noexcept;

		void clear();
	private:	
		std::vector<element_type> m_dense;
		std::vector <element_type*> m_sparse;
	};

	template <typename T>
	SparseSet<T>::SparseSet(const std::size_t capacity)
	{
		reserve(capacity);
	}

	template <typename T>
	template <typename ... Args>
	void SparseSet<T>::construct(const std::size_t index, Args&&... args)
	{
		// TODO: Ensure that nothing related to specified index is registered
		m_dense.emplace_back(std::forward<Args...>(args)...);

		if (index >=m_sparse.size())
		{
			m_sparse.resize(index);
		}

		m_sparse.insert(m_sparse.begin() + index, &(m_dense.back()));
	}

	template <typename T>
	void SparseSet<T>::reserve(const std::size_t capacity)
	{
		m_dense.reserve(capacity);
	}

	template <typename T>
	void SparseSet<T>::sparse_reserve(const std::size_t capacity)
	{
		m_sparse.reserve(capacity);
	}

	template <typename T>
	void SparseSet<T>::shrink_to_fit()
	{
		m_dense.shrink_to_fit();
	}

	template <typename T>
	std::size_t SparseSet<T>::capacity() const noexcept
	{
		return m_dense.capacity();
	}

	template <typename T>
	std::size_t SparseSet<T>::sparse_capacity() const noexcept
	{
		return m_sparse.capacity();
	}

	template <typename T>
	std::size_t SparseSet<T>::size() const noexcept
	{
		return m_dense.size();
	}

	template <typename T>
	std::size_t SparseSet<T>::sparse_size() const noexcept
	{
		return m_sparse.size();
	}

	template <typename T>
	void SparseSet<T>::clear()
	{
		m_dense.clear();
		m_sparse.clear();
	}
}
