#ifndef VECTOR_H
#define VECTOR_H


#include <memory>
#include <vector> 
#include "iterator.hpp"

namespace ft{


// template <typename T>
// struct vector_iterator
// {
// 	typedef T value_type;
// 	typedef T &reference;
// 	typedef T *pointer;

// 	typedef std::random_access_iterator_tag iterator_category;
// 	typedef std::ptrdiff_t difference_type;

// 	typedef vector_iterator<T> Self;
// 	typedef node_base::base_ptr base_ptr;
// 	typedef node<T> *link_type;

// 	vector_iterator()						: _m_node() {}
// 	vector_iterator(base_ptr ptr) throw()	: _m_node(ptr) {}

// 	reference operator*() const throw() { return *static_cast<link_type>(_m_node)->_m_dataPtr(); }
// 	pointer operator->() const throw()	{ return static_cast<link_type>(_m_node)->_m_dataPtr(); }

// 	Self &operator++() throw()	{ _m_node = _rb_tree_increment(_m_node); return *this; }
// 	Self operator++(int) throw(){ Self tmp = *this; _m_node = _rb_tree_increment(_m_node); return tmp; }

// 	Self &operator--() throw()	{ _m_node = _rb_tree_decrement(_m_node); return *this; }
// 	Self operator--(int) throw(){ Self __tmp = *this; _m_node = _rb_tree_decrement(_m_node); return __tmp; }

// 	friend bool operator==(const Self &x, const Self &y) throw() { return x._m_node == y._m_node; }
// 	friend bool operator!=(const Self &x, const Self &y) throw() { return !(x._m_node == y._m_node); }

// 	base_ptr _m_node;
// }; /* struct RbTree_iterator */




template<typename _T, typename _Alloc = std::allocator<_T> >
struct _vector_impl
{
	typedef _T*			pointer;

	pointer  _m_start;
	pointer  _m_finish;
	pointer  _m_end_of_storage;

	_vector_impl() {};

};

template<typename _T, typename _Alloc = std::allocator<_T> >
class vector
{

public:
	typedef _T								value_type;
	typedef _Alloc							allocator_type;

	typedef size_t									size_type; 
	typedef ptrdiff_t								difference_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef value_type								*pointer;
	typedef const value_type						*const_pointer;

	typedef pointer									iterator;
	typedef const_pointer							const_iterator;
	typedef reverse_iterator<iterator>				reverse_iterator;
	typedef reverse_iterator<const_iterator>		const_reverse_iterator;

private:
	_vector_impl _m_impl;
public:
	// default	
	explicit vector (const allocator_type& alloc = allocator_type()) {}
	// fill
	explicit vector (size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type())
	{
		(void)n;(void)val;(void)alloc;
	}
	// range
	template <class InputIterator>
	 vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	 {
		(void)first;(void)last;(void)alloc; 
	 }
	
	vector(const vector& other)
	{
		if (this == &other)
			return;
		// this->_m_impl = other._m_impl;
	}

	~vector() {}

	vector& operator= (const vector& x)
	{
		(void)x;
		return this;
	}

	// iterators
	iterator 				begin()			{ return 0; }
	const_iterator			begin() const	{ return 0; }
	iterator				end()			{ return 0; }
	const_iterator			end() const		{ return 0; }
	reverse_iterator 		rbegin()		{ return 0; }
	const_reverse_iterator 	rbegin() const	{ return 0; }
	reverse_iterator		rend()			{ return 0; }
	const_reverse_iterator	rend() const	{ return 0; }

	// capacity
	size_type	size() const										{ return 0; }
	size_type	max_size() const									{ return 0; }
	void		resize (size_type n, value_type val = value_type()) {(void)n; (void)val; }
	size_type	capacity() const									{ return 0; }
	bool		empty() const										{ return true;}
	void		reserve(size_type n) 								{ (void)n; }


	// Element access
	reference			operator[](size_type n)			{ (void)n; return NULL; }
	const_reference		operator[](size_type n) const	{ (void)n; return NULL; }
	reference 			at(size_type n) 				{ (void)n; return NULL; }
	const_reference 	at(size_type n) const			{ (void)n; return NULL; }
	reference 			front()							{ return NULL; }
	const_reference		front() const					{ return NULL; }
	reference			back()							{ return NULL; }
	const_reference		back() const					{ return NULL; }

	// Modifiers
	template <class InputIterator>
	 void		assign(InputIterator first, InputIterator last)	{ (void)first; (void)last;}
	void 		assign(size_type n, const value_type& val)		{ (void)n; (void)val; }
	void 		push_back(const value_type& val)				{ (void) val; }
	void		pop_back()										{}
	iterator 	insert(iterator position, const value_type& val) {(void)position; (void)val;}
	void		insert (iterator position, size_type n, const value_type& val) {(void)position; (void)val; (void)n;}
	template <class InputIterator>
	 void		insert (iterator position, InputIterator first, InputIterator last)	{ (void)position; (void)first; (void)last; }
	iterator	erase (iterator position)											{ (void)position; }
	iterator	erase (iterator first, iterator last)								{ (void)first; (void)last; }
	void		swap (vector& other)												{ (void)other; }
	void		clear()																{  }

	// Allocator
	allocator_type get_allocator() const;





private:
	template<class _T1, class _Alloc1>
	friend bool operator==(const vector<_T1, _Alloc1>&, const vector<_T1, _Alloc1>&);
	
	template<class _T1, class _Alloc1>
	friend bool operator<(const vector<_T1, _Alloc1>&, const vector<_T1, _Alloc1>&);
}; /* class vector */

template<class _T, class _Alloc>
	inline bool
	operator==(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
	{ return lhs.c == rhs.c; }

template<class _T, class _Alloc>
	inline bool
	operator<(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
	{ return lhs.c < rhs.c; }

template<class _T, class _Alloc>
	inline bool
	operator!=(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
	{ return !(lhs == rhs); }

template<class _T, class _Alloc>
	inline bool
	operator<=(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
	{ return !(rhs < lhs); }

template<class _T, class _Alloc>
	inline bool
	operator>(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
	{ return rhs < lhs; }

template<class _T, class _Alloc>
	inline bool
	operator>=(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
	{ return !(lhs < rhs); }

template <class _T, class _Alloc>
  void swap (vector<_T, _Alloc>& x, vector<_T, _Alloc>& y) {(void)x;(void)y;}

} /* namespace ft */


/*
	/// Constructs an empty container, with no elements.
	// vector (const allocator_type& alloc = allocator_type()):
	// 	_size(0), _capacity(0), _ptrArray(NULL){(void)alloc; }
	// /// Constructs a container with n elements. Each element is a copy of val.
	// vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
	// 	_size(n), _capacity(0), _ptrArray(NULL)
	// {
	// 	_ptrArray(alloc.allocate(n));
	// 	for (size_t i = 0; i < n; i++)
	// 		alloc.construct(_ptrArray + i, val);
	// 		// _ptrArray[i] = val;
	// }

	// Range constructor
	// template <class InputIterator>
	// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
	// 	_size(0), _capacity(0), _ptrArray(NULL)
	// {
	// 	alloc.allocate();
	// 
	// }
	/// Copy constructor
	vector (const vector& other) {(void)other;}
	// assign operator
	// vector & operator=(const vector & other){}
	~vector(){}
	

	void					reserve(size_type n)
	{
		if(n <= _size)
			return;
		
		value_type  *newPtrArray = new value_type[n]; // to replace using allocator
		this->_capacity = n;
	}

	void 		push_back(const value_type& val)
	{
		if (_size == _capacity)
			reserve( 2 * _capacity + 1);
		_ptrArray[_size++] = val;
	}

*/

#endif /* VECTOR_H */
