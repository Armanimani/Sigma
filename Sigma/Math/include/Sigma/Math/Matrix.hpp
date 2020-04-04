#pragma once

#include <array>

namespace sigma::math
{
	template <typename T, std::size_t M, std::size_t N>
	class Matrix
	{
		static_assert(M >= 2 && N >= 2);
	public:
		using value_type = T;
		constexpr static std::size_t k_row_count = M;
		constexpr static std::size_t k_column_count = N;

		template <typename U, std::size_t I, std::size_t J>
		friend class Matrix;

		constexpr Matrix() = default;
		constexpr explicit Matrix(T diagonal_value);
		constexpr explicit Matrix(const std::array<T, M* N>& data);

		[[nodiscard]] constexpr T& operator()(std::size_t row_index, std::size_t column_index) noexcept;
		[[nodiscard]] constexpr const T& operator()(std::size_t row_index, std::size_t column_index) const noexcept;

		template <typename T1, std::size_t P, std::enable_if_t<std::is_same_v<T1, T>>* = nullptr>
		[[nodiscard]] auto operator*(const Matrix<T1, N, P>& other) const;
		
		[[nodiscard]] Matrix operator+(const Matrix& other) const;
		[[nodiscard]] Matrix operator-(const Matrix& other) const;

		template <typename T1, std::size_t P, std::size_t Q, std::enable_if_t<P == Q && P == M && Q == N>* = nullptr>
		void operator*=(const Matrix<T1, P, Q>& other) noexcept;

		void operator+=(const Matrix& other) noexcept;
		void operator-=(const Matrix& other) noexcept;

		[[nodiscard]] constexpr T& at(std::size_t row_index, std::size_t column_index) noexcept;
		[[nodiscard]] constexpr const T& at(std::size_t row_index, std::size_t column_index) const noexcept;
	private:
		std::array<T, M* N> m_data{};
		
		[[nodiscard]] constexpr static std::size_t get_data_index(std::size_t row_index, std::size_t column_index) noexcept;
	};

	template <typename T, std::size_t M, std::size_t N>
	constexpr Matrix<T, M, N>::Matrix(const T diagonal_value)
	{
		static_assert(M == N);
		for (std::size_t i = 0; i != N; ++i)
		{
			at(i, i) = diagonal_value;
		}
	}

	template <typename T, std::size_t M, std::size_t N>
	constexpr Matrix<T, M, N>::Matrix(const std::array<T, M* N>& data)
		: m_data{ data } {}

	template <typename T, std::size_t M, std::size_t N>
	template <typename T1, std::size_t P, std::enable_if_t<std::is_same_v<T1, T>>*>
	auto Matrix<T, M, N>::operator*(const Matrix<T1, N, P>& other) const
	{
		Matrix<std::common_type_t<T, T>, M, P> result {};
		for (std::size_t column_index = 0; column_index != P; ++column_index)
		{
			for (std::size_t row_index = 0; row_index != M; ++row_index)
			{
				T value{};
				for (std::size_t index = 0; index != N; ++index)
				{
					value += at(row_index, index) * other.at(index, column_index);
				}
				result.at(row_index, column_index) = value;
			}
		}
		return result;
	}

	template <typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> Matrix<T, M, N>::operator+(const Matrix& other) const
	{
		Matrix<T, M, N> result{};
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), result.m_data.begin(), std::plus<T>());
		return result;
	}

	template <typename T, std::size_t M, std::size_t N>
	Matrix<T, M, N> Matrix<T, M, N>::operator-(const Matrix& other) const
	{
		Matrix<T, M, N> result{};
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), result.m_data.begin(), std::minus<T>());
		return result;
	}

	template <typename T, std::size_t M, std::size_t N>
	template <typename T1, std::size_t P, std::size_t Q, std::enable_if_t<P == Q && P == M && Q == N>*>
	void Matrix<T, M, N>::operator*=(const Matrix<T1, P, Q>& other) noexcept
	{
		const Matrix<T, M, N> mat{ m_data };
		(*this) = mat * other;		
	}

	template <typename T, std::size_t M, std::size_t N>
	void Matrix<T, M, N>::operator+=(const Matrix& other) noexcept
	{
		(*this) = (*this) + other;
	}

	template <typename T, std::size_t M, std::size_t N>
	void Matrix<T, M, N>::operator-=(const Matrix& other) noexcept
	{
		(*this) = (*this) - other;
	}

	template <typename T, std::size_t M, std::size_t N>
	constexpr T& Matrix<T, M, N>::operator()(const std::size_t row_index, const std::size_t column_index) noexcept
	{
		assert(row_index < M && column_index < N);
		auto index = get_data_index(row_index, column_index);
		return m_data[index];
	}

	template <typename T, std::size_t M, std::size_t N>
	constexpr const T& Matrix<T, M, N>::operator()(const std::size_t row_index, const std::size_t column_index) const noexcept
	{
		assert(row_index < M && column_index < N);
		const auto index = get_data_index(row_index, column_index);
		return m_data[index];
	}

	template <typename T, std::size_t M, std::size_t N>
	constexpr T& Matrix<T, M, N>::at(const std::size_t row_index, const std::size_t column_index) noexcept
	{
		return operator()(row_index, column_index);
	}

	template <typename T, std::size_t M, std::size_t N>
	constexpr const T& Matrix<T, M, N>::at(const std::size_t row_index, const std::size_t column_index) const noexcept
	{
		return operator()(row_index, column_index);
	}

	template <typename T, std::size_t M, std::size_t N>
	constexpr std::size_t Matrix<T, M, N>::get_data_index(const std::size_t row_index, const std::size_t column_index) noexcept
	{
		assert(row_index < M && column_index < N);
		return column_index * M + row_index;
	}
}
