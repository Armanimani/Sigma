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

		template <typename U, std::size_t N, std::enable_if_t< (D <= N) >* = nullptr>
		operator Vector<U, N>() const;
		
		[[nodiscard]] constexpr T& operator[](std::size_t index) noexcept;
		[[nodiscard]] constexpr const T& operator[](std::size_t index) const noexcept;

		[[nodiscard]] constexpr T& operator()(std::size_t index) noexcept;
		[[nodiscard]] constexpr const T& operator()(std::size_t index) const noexcept;

		constexpr bool operator==(const Vector& other) const noexcept;
		constexpr bool operator!=(const Vector& other) const noexcept;

		[[nodiscard]] constexpr Vector operator+(const Vector& other) const;
		[[nodiscard]] constexpr Vector operator-(const Vector& other) const;
		[[nodiscard]] constexpr Vector operator*(const Vector& other) const;
		[[nodiscard]] constexpr Vector operator/(const Vector& other) const;
		
		[[nodiscard]] constexpr Vector operator+(T other) const;
		[[nodiscard]] constexpr Vector operator-(T other) const;
		[[nodiscard]] constexpr Vector operator*(T other) const;
		[[nodiscard]] constexpr Vector operator/(T other) const;

		constexpr void operator+=(const Vector& other) noexcept;
		constexpr void operator-=(const Vector& other) noexcept;
		constexpr void operator*=(const Vector& other) noexcept;
		constexpr void operator/=(const Vector& other) noexcept;

		constexpr void operator+=(T other) noexcept;
		constexpr void operator-=(T other) noexcept;
		constexpr void operator*=(T other) noexcept;
		constexpr void operator/=(T other) noexcept;

		[[nodiscard]] constexpr Vector operator-() const;

		constexpr void set_values(T x, T y) noexcept;
		constexpr void set_values(T x, T y, T z) noexcept;
		constexpr void set_values(T x, T y, T z, T w) noexcept;

		[[nodiscard]] constexpr auto get_length() const noexcept;
		[[nodiscard]] constexpr T get_squared_length() const noexcept;
		[[nodiscard]] constexpr auto get_distance(const Vector& other) const noexcept;
		[[nodiscard]] constexpr T get_squared_distance(const Vector& other) const noexcept;
		
		[[nodiscard]] constexpr std::pair<T, T> find_min_max_element() const noexcept;
		[[nodiscard]] constexpr T find_min_element() const noexcept;
		[[nodiscard]] constexpr T find_max_element() const noexcept;
		
		[[nodiscard]] constexpr T dot(const Vector& other) const noexcept;

		template <std::size_t N, std::enable_if_t<N == 3>* = nullptr>
		[[nodiscard]] constexpr Vector<T, N> cross(const Vector<T, N>& other) const noexcept;
		
		constexpr void negate() noexcept;
		constexpr void fill(T value) noexcept;
		constexpr void normalize() noexcept;
		[[nodiscard]] constexpr bool is_normalized() const noexcept;

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

		static void set_normalized_tolerance(T tolerance) noexcept;
	private:
		std::array<T, D> m_data{};

		inline static T m_normalized_tolerance = std::numeric_limits<T>::epsilon() * 10;
	};

	template <typename T, std::size_t D>
	template <typename U, std::size_t N, std::enable_if_t< (D <= N) >*>
	Vector<T, D>::operator Vector<U, N>() const
	{
		std::array<U, N> buffer{};
		std::copy(m_data.cbegin(), m_data.cend(), buffer.begin());
		return Vector<U, N>(buffer);
	}

	template <typename T, std::size_t D>
	void Vector<T, D>::set_normalized_tolerance(const T tolerance) noexcept
	{
		m_normalized_tolerance = tolerance;
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
	constexpr Vector<T, D> Vector<T, D>::operator+(const Vector& other) const
	{
		Vector<T, D> result{};
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), result.m_data.begin(), std::plus<T>());
		return result;
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D> Vector<T, D>::operator-(const Vector& other) const
	{
		Vector<T, D> result{};
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), result.m_data.begin(), std::minus<T>());
		return result;
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D> Vector<T, D>::operator*(const Vector& other) const
	{
		Vector<T, D> result{};
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), result.m_data.begin(), std::multiplies<T>());
		return result;
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D> Vector<T, D>::operator/(const Vector& other) const
	{
		Vector<T, D> result{};
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), result.m_data.begin(), std::divides<T>());
		return result;
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D> Vector<T, D>::operator+(const T other) const
	{
		Vector<T, D> result{};
		std::transform(m_data.cbegin(), m_data.cend(), result.m_data.begin(),
			[=](const T value)
			{
				return value + other;
			}
		);
		return result;
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D> Vector<T, D>::operator-(const T other) const
	{
		Vector<T, D> result{};
		std::transform(m_data.cbegin(), m_data.cend(), result.m_data.begin(),
			[=](const T value)
			{
				return value - other;
			}
		);
		return result;
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D> Vector<T, D>::operator*(const T other) const
	{
		Vector<T, D> result{};
		std::transform(m_data.cbegin(), m_data.cend(), result.m_data.begin(),
			[=](const T value)
			{
				return value * other;
			}
		);
		return result;
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D> Vector<T, D>::operator/(const T other) const
	{
		Vector<T, D> result{};
		std::transform(m_data.cbegin(), m_data.cend(), result.m_data.begin(),
			[=](const T value)
			{
				return value / other;
			}
		);
		return result;
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::operator+=(const Vector& other) noexcept
	{
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), m_data.begin(), std::plus<T>());
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::operator-=(const Vector& other) noexcept
	{
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), m_data.begin(), std::minus<T>());
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::operator*=(const Vector& other) noexcept
	{
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), m_data.begin(), std::multiplies<T>());
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::operator/=(const Vector& other) noexcept
	{
		std::transform(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), m_data.begin(), std::divides<T>());
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::operator+=(const T other) noexcept
	{
		std::transform(m_data.cbegin(), m_data.cend(), m_data.begin(),
			[=](const T value)
			{
				return value + other;
			}
		);
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::operator-=(const T other) noexcept
	{
		std::transform(m_data.cbegin(), m_data.cend(), m_data.begin(),
			[=](const T value)
			{
				return value - other;
			}
		);
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::operator*=(const T other) noexcept
	{
		std::transform(m_data.cbegin(), m_data.cend(), m_data.begin(),
			[=](const T value)
			{
				return value * other;
			}
		);
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::operator/=(const T other) noexcept
	{
		std::transform(m_data.cbegin(), m_data.cend(), m_data.begin(),
			[=](const T value)
			{
				return value / other;
			}
		);
	}

	template <typename T, std::size_t D>
	constexpr Vector<T, D> Vector<T, D>::operator-() const
	{
		return (*this) * -1;
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::set_values(const T x, const T y) noexcept
	{
		m_data[0] = x;
		m_data[1] = y;
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::set_values(const T x, const T y, const T z) noexcept
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::set_values(const T x, const T y, const T z, const T w) noexcept
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
		m_data[3] = w;
	}

	template <typename T, std::size_t D>
	constexpr auto Vector<T, D>::get_length() const noexcept
	{
		return std::sqrtf(get_squared_length());
	}

	template <typename T, std::size_t D>
	constexpr T Vector<T, D>::get_squared_length() const noexcept
	{
		return std::reduce(m_data.cbegin(), m_data.cend(), T{},
			[](auto previous, auto current)
			{
				return previous += current * current;
			}
		);
	}

	template <typename T, std::size_t D>
	constexpr auto Vector<T, D>::get_distance(const Vector& other) const noexcept
	{
		return std::sqrtf(get_squared_distance(other));
	}

	template <typename T, std::size_t D>
	constexpr T Vector<T, D>::get_squared_distance(const Vector& other) const noexcept
	{
		return std::inner_product(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), T{}, std::plus<T>(),
			[](const auto element, const auto other_element)
			{
				return (element - other_element) * (element - other_element);
			}
		);
	}

	template <typename T, std::size_t D>
	constexpr std::pair<T, T> Vector<T, D>::find_min_max_element() const noexcept
	{
		auto [min_iterator, max_iterator] = std::minmax_element(m_data.cbegin(), m_data.cend());
		return std::make_pair(*min_iterator, *max_iterator);
	}

	template <typename T, std::size_t D>
	constexpr T Vector<T, D>::find_min_element() const noexcept
	{
		return *std::min_element(m_data.cbegin(), m_data.cend());
	}

	template <typename T, std::size_t D>
	constexpr T Vector<T, D>::find_max_element() const noexcept
	{
		return *std::max_element(m_data.cbegin(), m_data.cend());
	}

	template <typename T, std::size_t D>
	constexpr T Vector<T, D>::dot(const Vector& other) const noexcept
	{
		return std::inner_product(m_data.cbegin(), m_data.cend(), other.m_data.cbegin(), T{}, std::plus<T>(), std::multiplies<T>());
	}

	template <typename T, std::size_t D>
	template <std::size_t N, std::enable_if_t<N == 3>*>
	constexpr Vector<T, N> Vector<T, D>::cross(const Vector<T, N>& other) const noexcept
	{
		const auto x = m_data[1] * other[2] - m_data[2] * other[1];
		const auto y = m_data[2] * other[0] - m_data[0] * other[2];
		const auto z = m_data[0] * other[1] - m_data[1] * other[0];
		return { x, y, z };
	}


	template <typename T, std::size_t D>
	constexpr bool Vector<T, D>::is_normalized() const noexcept
	{
		return std::abs(get_squared_length() - T{ 1 }) <= m_normalized_tolerance;
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::negate() noexcept
	{
		(*this) *= (-1);
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::fill(const T value) noexcept
	{
		std::fill(m_data.begin(), m_data.end(), value);
	}

	template <typename T, std::size_t D>
	constexpr void Vector<T, D>::normalize() noexcept
	{
		const auto length = get_length();
		(*this) /= length;
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
