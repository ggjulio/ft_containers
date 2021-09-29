#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft{


template< class T >
void swap( T& a, T& b ) throw() { T c(a); a=b; b=c; }


template<class T1, class T2>
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	pair()							: first(), second() {}
	pair(T1 pFirst, T2 pSecond)		: first(pFirst), second(pSecond) {}
	pair(const pair<T1,T2>& other)	: first(other.first), second(other.second) {}
	pair&	operator=(const pair& other)
	{
		if (this == &other)
			return *this;
		first=other.first;
		second=other.second;
		return *this;
	}
	~pair() {}

	void swap(pair& other)
	{
		if (this == &other)
			return;
		ft::swap(first, other.first);
		ft::swap(second, other.second);
	}
};

template< class T1, class T2 >
inline void swap( pair<T1,T2>& x, pair<T1,T2>& y ) throw() { x.swap(y); }

template< class T1, class T2 >
pair<T1,T2> make_pair(T1 first, T2 second ) { return pair<T1, T2>(first, second);}

template< class T1, class T2 >
inline bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{ return lhs.first == rhs.first && lhs.second == rhs.second;}

template< class T1, class T2 >
inline bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{ return !(lhs == rhs);}

template< class T1, class T2 >
inline bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return lhs.first < rhs.first
		||  (!(lhs.first > rhs.first) && lhs.second < rhs.second)
	;
}

template< class T1, class T2 >
inline bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{ return !(rhs < lhs);}

template< class T1, class T2 >
inline bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{ return rhs < lhs;}


template< class T1, class T2 >
inline bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{ return !(lhs < rhs);}

} /* namespace ft */

#endif /* UTILITY_HPP */
