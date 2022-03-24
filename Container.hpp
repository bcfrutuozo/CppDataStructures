#include <type_traits>

template<typename T>
class Container
{
protected:

	
};

// Compare function to handle with const char*
// Char* must always be compared with strcmp() function
template<typename T>
static inline constexpr typename std::enable_if<std::is_same<T, const char*>::value, bool>::type Equals(const T& a, const T& b) noexcept
{
	return (strcmp(a, b) == 0);
}

// Compare function for primitive and classes which contain implementation of operator==()
template <typename T>
static inline constexpr typename std::enable_if<!std::is_same<T, const char*>::value, bool>::type Equals(const T& a, const T& b) noexcept
{
	return (a == b);
}