#ifndef SET_HPP
#define SET_HPP

#include "rb_tree.hpp"
#include "function.hpp"

namespace ft 
{

template < class _T,                        // set::key_type/value_type
           class _Compare = std::less<_T>,        // set::key_compare/value_compare
           class _Alloc = std::allocator<_T>      // set::allocator_type
           >
class set
{
public:
	typedef _T					key_type;
	typedef _T					value_type;
	typedef _Compare			key_compare;
	typedef _Compare			value_compare;
	typedef _Alloc				allocator_type;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;

private:
	typedef rbTree<	key_type,
					value_type,
					_Identity<value_type>,
					value_compare,
					allocator_type>
			__tree;
	__tree _tree;
public:
	typedef typename __tree::pointer						pointer;
	typedef typename __tree::const_pointer					const_pointer;
	typedef typename __tree::size_type						size_type;
	typedef typename __tree::difference_type				difference_type ;
	typedef typename __tree::const_iterator 				iterator; 	// this is not an error, iterator is required to be modifiable,
																		//  but this allows modification of keys. libstdc++ does that too
	typedef typename __tree::const_iterator 				const_iterator;
	typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;


// construct
	explicit set(const value_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	: _tree(comp, alloc) {}

	template <class InputIterator>
	 set(InputIterator first, InputIterator last,
	 	const value_compare& comp = key_compare(),
	 	const allocator_type& alloc = allocator_type())
	 : _tree(comp, alloc)
	 {
	 	insert(first, last);
	 }
	
	set(const set& other): _tree(other._tree) {}
	~set(){}

	set& operator=(const set& other)
	{
		if (this != &other)
			_tree = other._tree;
		return *this;
	}

// iterator
	iterator		begin()			{ return _tree.begin();}
	const_iterator	begin() const	{ return _tree.begin();}
	iterator		end()			{ return _tree.end();}
	const_iterator	end() const		{ return _tree.end();}

	reverse_iterator		rbegin()		{ return _tree.rbegin();}
	const_reverse_iterator	rbegin() const	{ return _tree.rbegin();}
    reverse_iterator		rend()			{ return _tree.rend();}
	const_reverse_iterator	rend() const	{ return _tree.rend();}

// capacity
	bool		empty() const		{ return _tree.empty();}
	size_type	size() const		{ return _tree.size();}
	size_type	max_size() const	{ return _tree.max_size();}

// modifiers
	/// Insert single element
	pair<iterator,bool>	insert (const value_type& val)
	{
		pair<typename __tree::iterator,bool> res = _tree.insert_unique(val);
		return pair<iterator,bool>(res.first, res.second);
	}

	/**
	 *  @brief Attempts to insert an element into the %set.
	 *  @param  __position  An iterator that serves as a hint as to where the
	 *                    element should be inserted.
	 *  @param  __x  Element to be inserted.
	 *  @return An iterator that points to the element with key of
	 *           @a __x (may or may not be the element passed in).
	 *
	 *  This function is not concerned about whether the insertion took place,
	 *  and thus does not return a boolean like the single-argument insert()
	 *  does.  Note that the first parameter is only a hint and can
	 *  potentially improve the performance of the insertion process.  A bad
	 *  hint would cause no gains in efficiency.
	 *
	 *  For more on @a hinting, see:
	 *  https://gcc.gnu.org/onlinedocs/libstdc++/manual/associative.html#containers.associative.insert_hints
	 *
	 *  Insertion requires logarithmic time (if the hint is not taken).
	 */
	iterator			insert(iterator position, const value_type& val)
	{
		pair<typename __tree::iterator,bool> res = _tree.insert_unique(position, val);
		return res.first;
	}
	
	template <class InputIterator>
  	 void insert(InputIterator first, InputIterator last)
	   { _tree.insert_range_unique(first, last);}

	void		erase(iterator position)				{ _tree.erase(position); }
	size_type	erase(const value_type& val)			{ return _tree.erase_unique(val); }
    void		erase(iterator first, iterator last)	{ _tree.erase(first, last);}
	void 		swap(set& other)						{ _tree.swap(other._tree); }
	void 		clear()									{ _tree.clear();}

// observers
	key_compare key_comp() const		{ return _tree.key_comp();}
	value_compare value_comp() const	{ return _tree.key_comp();}

// operations:
	iterator				find(const value_type& val) const			{ return _tree.find(val);}
	size_type				count(const value_type& val) const			{ return _tree.find(val) != _tree.end() ? 1: 0;}
	iterator				lower_bound(const value_type& val) const	{ return _tree.lower_bound(val);}
	iterator				upper_bound(const value_type& val) const	{ return _tree.upper_bound(val);}
	pair<iterator,iterator> equal_range(const value_type& val) const	{ return _tree.equal_range(val);}
	allocator_type			get_allocator() const 						{ return _tree.get_allocator();}


    template<typename _K1, typename _C1, typename _A1>
	friend bool operator==(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);

	template<typename _K1, typename _C1, typename _A1>
	friend bool operator<(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);


}; /* class set */

template<typename _Key, typename _Compare, typename _Alloc>
inline bool
operator==(const set<_Key, _Compare, _Alloc>& x, const set<_Key, _Compare, _Alloc>& y)
{ return x._tree == y._tree; }

template<typename _Key, typename _Compare, typename _Alloc>
inline bool
operator<(const set<_Key, _Compare, _Alloc>& x, const set<_Key, _Compare, _Alloc>& y)
{ return x._tree < y._tree; }

template<typename _Key, typename _Compare, typename _Alloc>
inline bool
operator!=(const set<_Key, _Compare, _Alloc>& x, const set<_Key, _Compare, _Alloc>& y)
{ return !(x == y); }

template<typename _Key, typename _Compare, typename _Alloc>
inline bool
operator>(const set<_Key, _Compare, _Alloc>& x, const set<_Key, _Compare, _Alloc>& y)
{ return y < x; }

template<typename _Key, typename _Compare, typename _Alloc>
inline bool
operator<=(const set<_Key, _Compare, _Alloc>& x, const set<_Key, _Compare, _Alloc>& y)
{ return !(y < x); }

template<typename _Key, typename _Compare, typename _Alloc>
inline bool
operator>=(const set<_Key, _Compare, _Alloc>& x, const set<_Key, _Compare, _Alloc>& y)
{ return !(x < y); }

} /* namespace ft */

#endif /* SET_HPP */