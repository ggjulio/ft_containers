#ifndef _STL_STACK_H
#define _STL_STACK_H 1

#include <bits/concept_check.h>
#include <debug/debug.h>
#if __cplusplus >= 201103L
# include <bits/uses_allocator.h>
#endif

namespace std 
{
  /**
   *  @brief  A standard container giving FILO behavior.
   *
   *  @ingroup sequences
   *
   *  @tparam _Tp  Type of element.
   *  @tparam _Sequence  Type of underlying sequence, defaults to deque<_Tp>.
   *
   *  Meets many of the requirements of a
   *  <a href="tables.html#65">container</a>,
   *  but does not define anything to do with iterators.  Very few of the
   *  other standard container interfaces are defined.
   *
   *  This is not a true container, but an @e adaptor.  It holds
   *  another container, and provides a wrapper interface to that
   *  container.  The wrapper is what enforces strict
   *  first-in-last-out %stack behavior.
   *
   *  The second template parameter defines the type of the underlying
   *  sequence/container.  It defaults to std::deque, but it can be
   *  any type that supports @c back, @c push_back, and @c pop_back,
   *  such as std::list, std::vector, or an appropriate user-defined
   *  type.
   *
   *  Members not found in @a normal containers are @c container_type,
   *  which is a typedef for the second Sequence parameter, and @c
   *  push, @c pop, and @c top, which are standard %stack/FILO
   *  operations.
  */
template<typename _Tp, typename _Sequence = deque<_Tp> >
class stack
{
	template<typename _Tp1, typename _Seq1>
	friend bool operator==(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

	template<typename _Tp1, typename _Seq1>
	friend bool	operator<(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

public:
	  typedef typename _Sequence::value_type		value_type;
	  typedef typename _Sequence::reference		reference;
	  typedef typename _Sequence::const_reference	const_reference;
	  typedef typename _Sequence::size_type		size_type;
	  typedef	       _Sequence			container_type;

protected:
	  //  See queue::c for notes on this name.
	  _Sequence c;

public:
	  // XXX removed old def ctor, added def arg to this one to match 14882
	  /**
	   *  @brief  Default constructor creates no elements.
	   */
	  explicit
	  stack(const _Sequence& __c = _Sequence()): c(__c) { }

	/**
	 *  Returns true if the %stack is empty.
	 */
	bool
	empty() const { return c.empty(); }

	/**  Returns the number of elements in the %stack.  */
	size_type
	size() const { return c.size(); }

	/**
	 *  Returns a read/write reference to the data at the first
	 *  element of the %stack.
	 */
	reference
	top(){return c.back();}

	/**
	 *  Returns a read-only (constant) reference to the data at the first
	 *  element of the %stack.
	 */
	const_reference
	top() const {return c.back();}

	/**
	 *  @brief  Add data to the top of the %stack.
	 *  @param  __x  Data to be added.
	 *
	 *  This is a typical %stack operation.  The function creates an
	 *  element at the top of the %stack and assigns the given data
	 *  to it.  The time complexity of the operation depends on the
	 *  underlying sequence.
	 */
	void
	push(const value_type& __x) { c.push_back(__x); }

	void
	push(value_type&& __x) { c.push_back(std::move(__x)); }

	template<typename... _Args>
	void
	emplace(_Args&&... __args)
	{ c.emplace_back(std::forward<_Args>(__args)...); }


	/**
	 *  @brief  Removes first element.
	 *
	 *  This is a typical %stack operation.  It shrinks the %stack
	 *  by one.  The time complexity of the operation depends on the
	 *  underlying sequence.
	 *
	 *  Note that no data is returned, and if the first element's
	 *  data is needed, it should be retrieved before pop() is
	 *  called.
	 */
	void
	pop()
	{c.pop_back();}

	void
	swap(stack& __s)
	{
		using std::swap;
		swap(c, __s.c);
	}
 
};

/**
 *  @brief  Stack equality comparison.
 *  @param  __x  A %stack.
 *  @param  __y  A %stack of the same type as @a __x.
 *  @return  True iff the size and elements of the stacks are equal.
 *
 *  This is an equivalence relation.  Complexity and semantics
 *  depend on the underlying sequence type, but the expected rules
 *  are: this relation is linear in the size of the sequences, and
 *  stacks are considered equivalent if their sequences compare
 *  equal.
 */
template<typename _Tp, typename _Seq>
	inline bool operator==(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y) { return __x.c == __y.c; }

  /**
   *  @brief  Stack ordering relation.
   *  @param  __x  A %stack.
   *  @param  __y  A %stack of the same type as @a x.
   *  @return  True iff @a x is lexicographically less than @a __y.
   *
   *  This is an total ordering relation.  Complexity and semantics
   *  depend on the underlying sequence type, but the expected rules
   *  are: this relation is linear in the size of the sequences, the
   *  elements must be comparable with @c <, and
   *  std::lexicographical_compare() is usually used to make the
   *  determination.
  */
  template<typename _Tp, typename _Seq>
	inline bool
	operator<(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
	{ return __x.c < __y.c; }

  /// Based on operator==
  template<typename _Tp, typename _Seq>
	inline bool
	operator!=(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
	{ return !(__x == __y); }

  /// Based on operator<
  template<typename _Tp, typename _Seq>
	inline bool
	operator>(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
	{ return __y < __x; }

  /// Based on operator<
  template<typename _Tp, typename _Seq>
	inline bool
	operator<=(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
	{ return !(__y < __x); }

  /// Based on operator<
  template<typename _Tp, typename _Seq>
	inline bool
	operator>=(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
	{ return !(__x < __y); }

#if __cpp_lib_three_way_comparison
  template<typename _Tp, three_way_comparable _Seq>
	inline compare_three_way_result_t<_Seq>
	operator<=>(const stack<_Tp, _Seq>& __x, const stack<_Tp, _Seq>& __y)
	{ return __x.c <=> __y.c; }
#endif

#if __cplusplus >= 201103L
  template<typename _Tp, typename _Seq>
	inline
#if __cplusplus > 201402L || !defined(__STRICT_ANSI__) // c++1z or gnu++11
	// Constrained free swap overload, see p0185r1
	typename enable_if<__is_swappable<_Seq>::value>::type
#else
	void
#endif
	swap(stack<_Tp, _Seq>& __x, stack<_Tp, _Seq>& __y)
	noexcept(noexcept(__x.swap(__y)))
	{ __x.swap(__y); }

  template<typename _Tp, typename _Seq, typename _Alloc>
	struct uses_allocator<stack<_Tp, _Seq>, _Alloc>
	: public uses_allocator<_Seq, _Alloc>::type { };
#endif // __cplusplus >= 201103L

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

#endif /* _STL_STACK_H */