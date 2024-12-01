

#ifndef __DOMAIN_H__
#define __DOMAIN_H__

#include <iostream>

#include <numeric>
#include <type_traits>

template <typename T> class Domain {

  // Primary template
  template <typename K, typename = void> struct make_unsigned_if_integral {
    using type = K;
  };

  // Specialization for integral types (excluding bool)
  template <typename K>
  struct make_unsigned_if_integral<
      K, std::enable_if_t<std::is_integral_v<K> && !std::is_same_v<K, bool>>> {
    using type = std::make_unsigned_t<K>;
  };

  using R = typename make_unsigned_if_integral<T>::type;

public:
  Domain()
      : Domain(std::numeric_limits<T>::min(), std::numeric_limits<T>::max()) {}
  Domain(const T min, const T max)
      : m_min(min), m_max(max),
        m_range(static_cast<R>(max) - static_cast<R>(min)) {}

  T const GetMin() const { return m_min; }
  T const GetMax() const { return m_max; }
  R const GetRange() const { return m_range; }

  template <typename K> bool const Contains(const K value) const {
    return value >= m_min && value <= m_max;
  }

  template <typename K> struct is_domain : std::false_type {};
  template <typename K> struct is_domain<Domain<K>> : std::true_type {};

private:
  const T m_min;
  const T m_max;
  const R m_range;
};

#endif // __DOMAIN_H__
