#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <utility>
#include <map>

#include "utility.hpp"
#include "rb_tree.hpp"
namespace ft
{
template <
	class _Key,												// map::key_type
	class _T,												// map::mapped_type
	class _Compare = std::less<_Key>,						// map::key_compare
	class _Alloc = std::allocator<pair<const _Key, _T> >	// map::allocator_type
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

	class value_compare
	{
		friend class map;
	protected:
		_Compare comp;
		value_compare(_Compare c) : comp(c) {}
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
	typedef rbTree<value_type, value_compare, allocator_type> __tree;
	__tree _tree;

public:
	typedef typename __tree::pointer						pointer;
	typedef typename __tree::const_pointer					const_pointer;
	typedef typename __tree::size_type						size_type;
	typedef typename __tree::difference_type				difference_type;
	typedef typename __tree::const_iterator 				iterator;
	typedef typename __tree::const_iterator 				const_iterator;
	typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;


// construct
	explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type())
	: _tree(comp, alloc) {}
	
	template <class InputIterator>
 	 map(InputIterator first, InputIterator last,
	  	const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
	: _tree(comp, alloc)
	{
		insert(first, last);
	}

	map(const map& other): _tree(other._tree) {}
	~map(){}

	map& operator= (const map& other)
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

// element access 
	mapped_type& operator[] (const key_type& k)
		{ return (*((this->insert(make_pair(k,mapped_type()))).first)).second;}

// modifiers
	pair<iterator,bool>	insert (const value_type& val)
		{ return _tree.insert_unique(val);}
	iterator			insert(iterator position, const value_type& val)
		{ return _tree.insert_unique(position, val);}

	template <class InputIterator>
  	 void insert(InputIterator first, InputIterator last)
	   { _tree._range_unique(first, last);}
	
	void		erase(iterator position)			{ _tree.erase(position); }
	size_type	erase(const key_type& k)			{ return _tree.erase_unique(k); }
    void		erase(iterator first, iterator last)	{ _tree.erase(first, last); }
	void 		swap(map& other)						{ _tree.swap(other._tree); }
	void 		clear()									{ _tree.clear();}

// observers
	key_compare	key_comp() const		{ return _tree.key_comp();}
	value_compare value_comp() const	{ return _tree.key_comp();}

// operations
    iterator		find(const key_type& k)			{ return _tree.find(k);}
	const_iterator	find(const key_type& k) const	{ return _tree.find(k);}
	size_type		count(const key_type& k) const	{ return _tree.count_unique(k);}
	iterator		lower_bound (const key_type& k)			{ return _tree.lower_bound(k); }
	const_iterator	lower_bound (const key_type& k) const	{ return _tree.lower_bound(k); }
	iterator		upper_bound (const key_type& k)			{ return _tree.upper_bound(k); }
	const_iterator	upper_bound (const key_type& k) const	{ return _tree.upper_bound(k); }
	pair<const_iterator,const_iterator> equal_range(const key_type& k) const
											{ return _tree.equal_range_unique(k); }
	pair<iterator,iterator>             equal_range(const key_type& k)
											{ return _tree.equal_range_unique(k); }

	allocator_type	get_allocator() const 	{ return _tree.get_allocator(); }


}; /* class map */

} /* namespace ft */

#endif /* MAP_HPP */