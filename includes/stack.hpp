#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft{

  /**
   *  A standard container giving FILO behavior.
   *
   *  @tparam _T  			Type of element.
   *  @tparam _Container  	Type of underlying sequence, defaults to deque<_T>.
   *
   *  @details
   *  Meets many of the requirements of a container,
   *  but does not define anything to do with iterators.  Very few of the
   *  other standard container interfaces are defined.
   *
   *  This is not a true container, but an adaptor. It holds
   *  another container, and provides a wrapper interface to that
   *  container.  The wrapper is what enforces strict
   *  first-in-last-out %stack behavior.
   *
   *  The second template parameter defines the type of the underlying
   *  sequence/container.  It defaults to ft::deque, but it can be
   *  any type that supports @c back, @c push_back, and @c pop_back,
   *  such as ft::list, ft::vector, or an appropriate user-defined
   *  type.
   *
   *  Members not found in normal containers are @c container_type,
   *  which is a typedef for the second template parameter, and
   *  @c push, @c pop, and @c top, which are standard %stack/FILO
   *  operations.
  */
template<class _T, class _Container = ft::vector<_T> >
class stack
{
public:
	typedef typename _Container::value_type			value_type;
	typedef typename _Container::size_type			size_type;
	typedef 		 _Container 					container_type;

protected:
	_Container c;

public:
	stack(const _Container& ctnr = _Container()): c(ctnr){}

	bool				empty(void) const 				{ return c.empty(); }
	size_type			size() const					{ return c.size(); }
	value_type&			top(void)						{ return c.back(); }
	const value_type&	top(void) const					{ return c.back(); }
	void				push(const value_type& value)	{ c.push_back(value); }
    void				pop(void)						{ c.pop_back(); }


private:
	template<class _T1, class _Container1>
	friend bool operator==(const stack<_T1, _Container1>&, const stack<_T1, _Container1>&);
	
	template<class _T1, class _Container1>
	friend bool operator<(const stack<_T1, _Container1>&, const stack<_T1, _Container1>&);
}; /* class stack */

template<class _T, class _Container>
	inline bool
	operator==(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
	{ return lhs.c == rhs.c; }

template<class _T, class _Container>
	inline bool
	operator<(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
	{ return lhs.c < rhs.c; }



template<class _T, class _Container>
	inline bool
	operator!=(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
	{ return !(lhs == rhs); }

template<class _T, class _Container>
	inline bool
	operator<=(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
	{ return !(rhs < lhs); }

template<class _T, class _Container>
	inline bool
	operator>(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
	{ return rhs < lhs; }

template<class _T, class _Container>
	inline bool
	operator>=(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs)
	{ return !(lhs < rhs); }

} /* namespace ft */

#endif /* STACK_HPP */
