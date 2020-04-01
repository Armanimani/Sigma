#pragma once

#include <array>
#include <numeric>
#include <limits>


namespace sigma::math
{
	template <typename T, std::size_t D>
	class Vector
	{
		static_assert(D >= 2);
	public:
		using value_type = T;	
		constexpr static std::size_t k_dimension = D;

		template<typename U, std::size_t N>
		friend class Vector;

		constexpr Vector() = default;
		constexpr explicit Vector(T fill_value);
		constexpr explicit Vector(const std::array<T, D>& data);
		constexpr Vector(T x, T y);
		constexpr Vector(T x, T y, T z);
		constexpr Vector(T x, T y, T z, T w);

		template<typename U, std::size_t N>
		operator Vector<U, N>() const;
		
		[[nodiscard]] constexpr T& operator[](std::size_t index) noexcept;
		[[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept;

		[[nodiscard]] constexpr T& operator()(std::size_t index) noexcept;
		[[nodiscard]] constexpr const T& operator()(std::size_t index) const noexcept;

		constexpr bool operator==(const Vector& other) const noexcept;
		constexpr bool operator!=(const Vector& other) const noexcept;

		[[nodiscard]] constexpr T& x() noexcept;
		[[nodiscard]] constexpr T& y() noexcept;
		[[nodiscard]] constexpr T& z() noexcept;
		[[nodiscard]] constexpr T& w() noexcept;
		[[nodiscard]] constexpr const T& x() const noexcept;
		[[nodiscard]] constexpr const T& y() const noexcept;
		[[nodiscard]] constexpr const T& z() const noexcept;
		[[nodiscard]] constexpr const T& w() const noexcept;
		[[nodiscard]] constexpr T& r() noexcept;
		[[nodiscard]] constexpr T& g() noexcept;
		[[nodiscard]] constexpr T& b() noexcept;
		[[nodiscard]] constexpr T& a() noexcept;
		[[nodiscard]] constexpr const T& r() const noexcept;
		[[nodiscard]] constexpr const T& g() const noexcept;
		[[nodiscard]] constexpr const T& b() const noexcept;
		[[nodiscard]] constexpr const T& a() const noexcept;

		[[nodiscard]] constexpr Vector<T, 2> get_xy() const;	
		[[nodiscard]] constexpr Vector<T, 3> get_xyz() const;
		[[nodiscard]] constexpr Vector<T, 3> get_rgb() const;
	private:
		std::array<T, D> m_data{};
	};

	template <typename T, std::size_t D>
	template <typename U, std::size_t N>
	Vector<T, D>::operator Vector<U, N>() const
	{
		static_assert(D <= N);
		std::array<U, N> buffer{};
		std::copy(m_data.cbegin(), m_data.cend(), buffer.begin());
		return Vector<U, N>(buffer);
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D>::Vector(T fill_value)
	{
		std::fill(m_data.begin(), m_data.end(), fill_value);
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D>::Vector(const std::array<T, D>& data)
		: m_data{ data } {}

	template <typename T, std::size_t D>
	constexpr Vector<T, D>::Vector(const T x, const T y)
		: m_data{x, y} {}

	template <typename T, std::size_t D>
	constexpr Vector<T, D>::Vector(const T x, const T y, const T z)
		: m_data{ x, y, z }
	{
		static_assert(D >= 3);
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D>::Vector(const T x, const T y, const T z, const T w)
		: m_data{ x, y, z, w }
	{
		static_assert(D >= 4);
	}
	
	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::operator[](const std::size_t index) noexcept
	{
		assert(index < D);
		return m_data[index];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::operator[](const std::size_t index) const noexcept
	{
		assert(index < D);
		return m_data[index];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::operator()(std::size_t index) noexcept
	{
		assert(index < D);
		return m_data[index];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::operator()(std::size_t index) const noexcept
	{
		assert(index < D);
		return m_data[index];
	}

	template <typename T, std::size_t D>
	constexpr bool Vector<T, D>::operator==(const Vector& other) const noexcept
	{
		constexpr auto tolerance = std::numeric_limits<T>::epsilon();
		return std::equal(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(),
			[=](const auto first_element, const auto second_element)
			{
				return std::abs(first_element - second_element) <= tolerance;
			}
		);
	}

	template <typename T, std::size_t D>
	constexpr bool Vector<T, D>::operator!=(const Vector& other) const noexcept
	{
		return !(*this == other);
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::x() noexcept
	{
		return m_data[0];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::y() noexcept
	{
		return m_data[1];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::z() noexcept
	{
		static_assert(D >= 3);
		return m_data[2];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::w() noexcept
	{
		static_assert(D >= 4);
		return m_data[3];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::x() const noexcept
	{
		return m_data[0];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::y() const noexcept
	{
		return m_data[1];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::z() const noexcept
	{
		static_assert(D >= 3);
		return m_data[2];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::w() const noexcept
	{
		static_assert(D >= 4);
		return m_data[3];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::r() noexcept
	{
		return m_data[0];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::g() noexcept
	{
		return m_data[1];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::b() noexcept
	{
		static_assert(D >= 3);
		return m_data[2];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::a() noexcept
	{
		static_assert(D >= 4);
		return m_data[3];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::r() const noexcept
	{
		return m_data[0];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::g() const noexcept
	{
		return m_data[1];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::b() const noexcept
	{
		static_assert(D >= 3);
		return m_data[2];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::a() const noexcept
	{
		static_assert(D >= 4);
		return m_data[3];
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, 2> Vector<T, D>::get_xy() const
	{
		return { m_data[0], m_data[1] };
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, 3> Vector<T, D>::get_xyz() const
	{
		static_assert(D >= 3);
		return { m_data[0], m_data[1], m_data[2] };
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, 3> Vector<T, D>::get_rgb() const
	{
		static_assert(D >= 3);
		return { m_data[0], m_data[1], m_data[2] };
	}
}
