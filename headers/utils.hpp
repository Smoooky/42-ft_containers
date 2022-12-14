//
// Created by matsony on 19.07.22.
//

#ifndef FT_CONTAINERS_FINAL_UTILS_HPP
#define FT_CONTAINERS_FINAL_UTILS_HPP

#include <typeinfo>

namespace ft
{
const bool NotConst = false;
const bool Const = true;

template<bool B, typename NotConst, typename Const>
struct conditional {typedef NotConst   type;};

template<typename NotConst, typename Const>
struct conditional<true, NotConst, Const> {typedef Const   type;};

template<bool B, typename NotConst, typename Const>
struct conditional_t
{typedef typename conditional<B, NotConst, Const>::type   type;};


template<bool B, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> {typedef T type;};


template<typename T, typename U>
struct is_same {static const bool value = false;};

template<typename T>
struct is_same<T, T> {static const bool value = true;};

template<typename T, typename U>
bool    is_same_type(const T &f, const U &s)
{
	return typeid(f) == typeid(s);
}

//ft::_is_integral: Helper for ft::is_integral.
template< bool Value, typename T>
struct _is_integral{typedef T type; static const bool value = Value;};

//ft::is_integral: Checks whether T is an integral type.
template<typename T>
struct is_integral: public _is_integral<false, T>{};

template <>
struct is_integral<bool>: public _is_integral<true, bool> {};

template <>
struct is_integral<char>: public _is_integral<true, char> {};

template <>
struct is_integral<signed char>: public _is_integral<true, signed char> {};

template <>
struct is_integral<short int>: public _is_integral<true, short int> {};

template <>
struct is_integral<int>: public _is_integral<true, int> {};

template <>
struct is_integral<long int>: public _is_integral<true, long int> {};

template <>
struct is_integral<long long int>: public _is_integral<true, long long int> {};

template <>
struct is_integral<unsigned char>: public _is_integral<true, unsigned char> {};

template <>
struct is_integral<unsigned short int>
		: public _is_integral<true, unsigned short int> {};

template <>
struct is_integral<unsigned int>: public _is_integral<true, unsigned int> {};

template <>
struct is_integral<unsigned long int>
		: public _is_integral<true, unsigned long int> {};

template <>
struct is_integral<unsigned long long int>
		: public _is_integral<true, unsigned long long int> {};

}

#endif //FT_CONTAINERS_FINAL_UTILS_HPP
