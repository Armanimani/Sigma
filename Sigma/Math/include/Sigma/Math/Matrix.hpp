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

		[[nodiscard]] constexpr T& operator()(std::size_t row_index, std::size_t column_index) noexcept;
		[[nodiscard]] constexpr const T& operator()(std::size_t row_index, std::size_t column_index) const noexcept;
	private:
		std::array<T, M* N> m_data{};
		
		[[nodiscard]] constexpr static std::size_t get_data_index(std::size_t row_index, std::size_t column_index) noexcept;
	};

	template <typename T, std::size_t M, std::size_t N>
	constexpr T& Matrix<T, M, N>::operator()(const std::size_t row_index, const std::size_t column_index) noexcept
	{
		assert(row_index < M&& column_index < N);
		auto index = get_data_index(row_index, column_index);
		return m_data[index];
	}

	template <typename T, std::size_t M, std::size_t N>
	constexpr const T& Matrix<T, M, N>::operator()(const std::size_t row_index, const std::size_t column_index) const noexcept
	{
		assert(row_index < M&& column_index < N);
		const auto index = get_data_index(row_index, column_index);
		return m_data[index];
	}

	template <typename T, std::size_t M, std::size_t N>
	constexpr std::size_t Matrix<T, M, N>::get_data_index(const std::size_t row_index, const std::size_t column_index) noexcept
	{
		assert(row_index < M&& column_index < N);
		return row_index * N + column_index;
	}
}
