#pragma once

#include <array>
#include <numeric>


namespace sigma::math
{
	template <typename T, std::size_t D>
	class Vector
	{
		static_assert(D > 0);
	public:
		using value_type = T;
		constexpr static std::size_t k_dimension = D;

		constexpr Vector() = default;
		constexpr explicit Vector(T fill_value);
		constexpr Vector(T x, T y);
		constexpr Vector(T x, T y, T z);
		constexpr Vector(T x, T y, T z, T w);

		constexpr Vector(const Vector&) = default;
		constexpr Vector(Vector&& other) noexcept = default;
		constexpr Vector& operator=(const Vector& other) = default;
		constexpr Vector& operator=(Vector&& other) noexcept = default;
		~Vector() = default;

		[[nodiscard]] constexpr T& operator[](std::size_t index) noexcept;
		[[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept;

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
	private:
		std::array<T, D> m_data{};
	};

	
	template <typename T, std::size_t D>
	constexpr Vector<T, D>::Vector(T fill_value)
	{
		std::fill(m_data.begin(), m_data.end(), fill_value);
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D>::Vector(const T x, const T y)
		: m_data{x, y}
	{
		static_assert(D >= 2);
	}

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
		return m_data[index];
	}

	template <typename T, std::size_t D>
	constexpr const T& Vector<T, D>::operator[](const std::size_t index) const noexcept
	{
		return m_data[index];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::x() noexcept
	{
		return m_data[0];
	}

	template <typename T, std::size_t D>
	constexpr T& Vector<T, D>::y() noexcept
	{
		static_assert(D >= 2);
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
		static_assert(D >= 2);
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
		static_assert(D >= 2);
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
		static_assert(D >= 2);
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
}
