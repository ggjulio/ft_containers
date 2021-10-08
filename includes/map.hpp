#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <utility>
#include <map>

namespace ft
{
template <
	class _Key,													// map::key_type
	class _T,													// map::mapped_type
	class _Compare = std::less<_Key>,							// map::key_compare
	class _Alloc = std::allocator<std::pair<const _Key, _T> > // map::allocator_type
	>
class map
{
public:
	// types:
	typedef _Key					key_type;
	typedef _T						mapped_type;
	typedef pair<const _Key, _T>	value_type;
	typedef _Compare				key_compare;
	typedef _Alloc					allocator_type;
	typedef value_type&				reference;
	typedef const value_type&		const_reference;
	// typedef implementation-defined	iterator; // see 23.2
	// typedef implementation-defined	const_iterator; // see 23.2
	// typedef implementation-defined size_type; // see 23.2
	// typedef implementation-defined difference_type;// see 23.2
	typedef typename allocator_traits<Allocator>::pointer		pointer;
	typedef typename allocator_traits<Allocator>::const_pointer	const_pointer;
	typedef reverse_iterator<iterator> reverse_iterator;
	typedef reverse_iterator<const_iterator> const_reverse_iterator;

	class value_compare
	{
		friend class map;

	protected:
		Compare comp;
		value_compare(Compare c) : comp(c) {}

	public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		bool operator()(const value_type &x, const value_type &y) const
		{
			return comp(x.first, y.first);
		}
	};

	private:
	};

} /* namespace ft */

#endif /* MAP_HPP */