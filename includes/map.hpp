#ifndef MAP_HPP
#define MAP_HPP

#include <memory>

#include "rb_tree.hpp"
#include "function.hpp"
#include "utility.hpp"


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
	typedef rbTree<	key_type,
					value_type,
					_Select1st<value_type>,
					key_compare,
					allocator_type>
			__tree;
	__tree _tree;

public:
	typedef typename __tree::pointer						pointer;
	typedef typename __tree::const_pointer					const_pointer;
	typedef typename __tree::size_type						size_type;
	typedef typename __tree::difference_type				difference_type;
	typedef typename __tree::iterator		 				iterator;
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
		{ return (*((this->insert(value_type(k,mapped_type()))).first)).second;}

// modifiers
	pair<iterator,bool>	insert(const value_type& val)
	{
		pair<typename __tree::iterator, bool> res = _tree.insert_unique(val);
		return pair<typename __tree::iterator, bool>(res.first, res.second) ;
	}
	iterator	insert(iterator position, const value_type& val)
	{
		pair<typename __tree::iterator,bool> res = _tree.insert_unique(position, val);
		return res.first;
	}

	template <class InputIterator>
  	 void insert(InputIterator first, InputIterator last)
	   { _tree.insert_range_unique(first, last);}
	
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
	size_type		count(const key_type& k) const	{ return _tree.find(k) != _tree.end() ? 1: 0;}
	iterator		lower_bound (const key_type& k)			{ return _tree.lower_bound(k); }
	const_iterator	lower_bound (const key_type& k) const	{ return _tree.lower_bound(k); }
	iterator		upper_bound (const key_type& k)			{ return _tree.upper_bound(k); }
	const_iterator	upper_bound (const key_type& k) const	{ return _tree.upper_bound(k); }
	pair<iterator,iterator>             equal_range(const key_type& k)
											{ return _tree.equal_range(k); }
	pair<const_iterator,const_iterator> equal_range(const key_type& k) const
											{ return _tree.equal_range(k); }

	allocator_type	get_allocator() const 	{ return _tree.get_allocator(); }

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	friend bool operator==(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	friend bool operator<(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);

}; /* class map */

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool operator==(const map<_Key, _Tp, _Compare, _Alloc>& x, const map<_Key, _Tp, _Compare, _Alloc>& y)
{ return x._tree == y._tree; }

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator<(const map<_Key, _Tp, _Compare, _Alloc>& x, const map<_Key, _Tp, _Compare, _Alloc>& y)
{ return x._tree < y._tree; }

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator!=(const map<_Key, _Tp, _Compare, _Alloc>& x, const map<_Key, _Tp, _Compare, _Alloc>& y)
{ return !(x == y); }

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator>(const map<_Key, _Tp, _Compare, _Alloc>& x, const map<_Key, _Tp, _Compare, _Alloc>& y)
{ return y < x; }

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator<=(const map<_Key, _Tp, _Compare, _Alloc>& x, const map<_Key, _Tp, _Compare, _Alloc>& y)
{ return !(y < x); }

template<typename _Key, typename _Tp, typename _Compare, typename _Alloc>
inline bool
operator>=(const map<_Key, _Tp, _Compare, _Alloc>& x, const map<_Key, _Tp, _Compare, _Alloc>& y)
{ return !(x < y); }

template <class Key, class T, class Compare, class Alloc>
  void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y) { x.swap(y); }

} /* namespace ft */

#endif /* MAP_HPP */