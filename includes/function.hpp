#ifndef FUNCTION_HPP
#define FUNCTION_HPP

namespace ft
{
template <typename T>
struct _Identity
	: public std::unary_function<T, T>
{
	T &operator()(T &__x) const				{ return __x; }
	const T &operator()(const T &__x) const { return __x; }
};
// Partial specialization, avoids confusing errors in e.g. std::set<const T>.
template <typename T> struct _Identity<const T> : _Identity<T> {};

template <typename Pair>
struct _Select1st
	: public std::unary_function<Pair, typename Pair::first_type>
{
	typename Pair::first_type &
	operator()(Pair &__x) const			{ return __x.first; }

	const typename Pair::first_type &
	operator()(const Pair &__x) const	{ return __x.first;}

};

} /* namespace ft */

#endif /* FUNCTION_HPP */