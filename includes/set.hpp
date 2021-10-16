#ifndef SET_HPP
#define SET_HPP

#include <set>

#include "rb_tree.hpp"

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
	typedef rbTree<value_type, value_compare, allocator_type> __tree;

	__tree _tree;
public:
	typedef typename __tree::pointer						pointer;
	typedef typename __tree::const_pointer					const_pointer;
	typedef typename __tree::size_type						size_type;
	typedef typename __tree::difference_type				difference_type ;
	typedef typename __tree::const_iterator 				iterator;
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
		{ return _tree.insert_unique(val);}

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
		{ return _tree.insert_unique(position, val);}
	
	template <class InputIterator>
  	 void insert(InputIterator first, InputIterator last)
	   { _tree._range_unique(first, last);}

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
	size_type				count(const value_type& val) const			{ return _tree.count_unique(val);}
	iterator				lower_bound(const value_type& val) const	{ return _tree.lower_bound(val);}
	iterator				upper_bound(const value_type& val) const	{ return _tree.upper_bound(val);}
	pair<iterator,iterator> equal_range(const value_type& val) const	{ return _tree.equal_range_unique(val);}
	allocator_type			get_allocator() const 						{ return _tree.get_allocator();}

}; /* class set */

} /* namespace ft */

#endif /* SET_HPP */