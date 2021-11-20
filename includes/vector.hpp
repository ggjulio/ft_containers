#ifndef VECTOR_H
#define VECTOR_H


#include <memory>
#include <algorithm>
#include <vector> 
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft{


	template <typename T>
	struct vector_iterator
	{
		typedef T	value_type;
		typedef value_type	&reference;
		typedef value_type	*pointer;

		typedef std::random_access_iterator_tag		iterator_category;
		typedef std::ptrdiff_t						difference_type;

		typedef vector_iterator<value_type> Self;

		vector_iterator()						: _m_ptr(0) {}
		vector_iterator(pointer ptr) throw()	: _m_ptr(ptr) {}
		// vector_iterator(const Self& it) throw()	: _m_ptr(it._m_ptr) {}

		reference	operator*() const throw()		{ return *_m_ptr; }
		pointer		operator->() const throw()		{ return _m_ptr; }
		reference	operator[](size_t n) const		{ return *(_m_ptr + n); }

		Self &operator++() throw()		{ ++_m_ptr; return *this; }
		Self operator++(int) throw()	{ Self tmp = *this; ++_m_ptr; return tmp; }

		Self &operator--() throw()		{ _m_ptr -= 1; return *this; }
		Self operator--(int) throw()	{ Self tmp = *this; _m_ptr -= 1; return tmp; }

		Self  operator+ (difference_type n) const	{ return _m_ptr + n;}
		Self& operator+=(difference_type n)			{ _m_ptr += n; return *this;}
		Self  operator- (difference_type n) const	{ return _m_ptr - n;}
		Self& operator-=(difference_type n) 		{ _m_ptr -= n; return *this;}

		// bool operator==	(const Self &rhs) { return (_m_ptr == rhs._m_ptr); };
		// bool operator!=	(const Self &rhs) { return (_m_ptr != rhs._m_ptr); };
		// bool operator<	(const Self &rhs) const { return (_m_ptr < rhs._m_ptr); };
		// bool operator>	(const Self &rhs) const { return (_m_ptr > rhs._m_ptr); };
		// bool operator<=	(const Self &rhs) const { return (_m_ptr <= rhs._m_ptr); };
		// bool operator>=	(const Self &rhs) const { return (_m_ptr >= rhs._m_ptr); };

		friend bool operator==(const Self &x, const Self &y) throw() { return x._m_ptr == y._m_ptr; }
		friend bool operator!=(const Self &x, const Self &y) throw() { return !(x._m_ptr == y._m_ptr); }


		pointer base() const {return _m_ptr; }

		// operator Self<const value_type > () const { return _m_ptr; }
	protected:
		pointer _m_ptr;
	}; /* struct vector_iterator */

    template <typename T>
    typename vector_iterator<T>::difference_type
     operator-(const vector_iterator<T>& lhs,
              const vector_iterator<T>& rhs)
    {
        return (lhs.base() - rhs.base());
    }

	template<typename IteratorL, typename IteratorR>
    typename vector_iterator<IteratorL>::difference_type
     operator-(const vector_iterator<IteratorL>& lhs,
              const vector_iterator<IteratorR>& rhs)
    {
        return (lhs.base() - rhs.base());
    }

	template<typename Iterator>
    vector_iterator<Iterator>
	 operator+(typename vector_iterator<Iterator>::difference_type n,
 				vector_iterator<Iterator>& i)
	{
		return i.base() + n;
	}



template<typename _T, typename _Alloc = std::allocator<_T> >
struct _vector_impl
{
	typedef _T*			pointer;

	pointer  _m_start;
	pointer  _m_finish;
	pointer  _m_end_of_storage;

	_vector_impl()
	{
		_m_start = _m_finish = _m_end_of_storage = 0;
	}

};

template<typename _T, typename _Alloc = std::allocator<_T> >
class vector
{

public:
	typedef _T								value_type;
	typedef _Alloc							allocator_type;

	typedef size_t									size_type; 
	typedef std::ptrdiff_t								difference_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef value_type								*pointer;
	typedef const value_type						*const_pointer;

	typedef vector_iterator<value_type>				iterator;
	typedef vector_iterator<const value_type>		const_iterator;
	typedef reverse_iterator<iterator>				reverse_iterator;
	// typedef reverse_iterator<const_iterator>		const_reverse_iterator;

private:
	_vector_impl<value_type> _m_impl;
	static allocator_type _m_alloc;

public:
	// default	
	explicit vector (const allocator_type& alloc = allocator_type())
	{
		(void)alloc;
	}
	// fill
	explicit vector (size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type())
	{
		(void)alloc;
		_m_create_storage(n);
		std::uninitialized_fill_n(_m_impl._m_start, n, val);
		_m_impl._m_finish += n;
	}
	// range
	template <class InputIterator,
		typename enable_if<!is_integral<InputIterator>::value, bool>::type = true>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	{
		(void)alloc;
		_m_create_storage(std::distance(first, last));
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}
	
	vector(const vector& other)
	{
		if (this == &other)
			return;
		// this->_m_impl = other._m_impl;
	}

	~vector() {}

	vector& operator= (const vector& other)
	{
		if (this != &other)
		{

		}
		return *this;
	}

	// iterators
	iterator 				begin()			{ return _m_impl._m_start; }
	const_iterator			begin() const	{ return _m_impl._m_start; }
	iterator				end()			{ return _m_impl._m_finish; }
	const_iterator			end() const		{ return _m_impl._m_finish; }
	reverse_iterator 		rbegin()		{ return end(); }
	// const_reverse_iterator 	rbegin() const	{ return end(); }
	reverse_iterator		rend()			{ return begin(); }
	// const_reverse_iterator	rend() const	{ return begin(); }

	// capacity
	size_type	size() const										{ return _m_impl._m_finish - _m_impl._m_start; }
	size_type	max_size() const									{ return _m_alloc.max_size(); }
	void		resize (size_type n, value_type val = value_type()) {(void)n; (void)val; }
	size_type	capacity() const									{ return _m_impl._m_end_of_storage - _m_impl._m_start; }
	bool		empty() const										{ return begin() == end();}
	void		reserve(size_type n) 								{ (void)n; }


	// Element access
	reference			operator[](size_type n)			{ return *(_m_impl._m_start + n); }
	const_reference		operator[](size_type n) const	{ return *(_m_impl._m_start + n); }
	reference 			at(size_type n) 				{ return (*this)[n]; }
	const_reference 	at(size_type n) const			{ return (*this)[n]; }
	reference 			front()							{ return *begin(); }
	const_reference		front() const					{ return *begin(); }
	reference			back()							{ return *(end() - 1); }
	const_reference		back() const					{ return *(end() - 1); }

	// Modifiers
	template <class InputIterator>
	 void		assign(InputIterator first, InputIterator last)	{ (void)first; (void)last;}
	void 		assign(size_type n, const value_type& val)		{ (void)n; (void)val; }
	void 		push_back(const value_type& val)
	{
		if (_m_impl._m_finish == _m_impl._m_end_of_storage)
		{
			if (_m_impl._m_start != _m_impl._m_finish)
				_m_grow();
			else
				_m_create_storage(1);
		}
		_m_alloc.construct(_m_impl._m_finish++, val);
	}
	void		pop_back() {
		_m_alloc.destroy(--_m_impl._m_finish);
	}
	iterator 	insert(iterator position, const value_type& val) {(void)position; (void)val;}
	void		insert (iterator position, size_type n, const value_type& val) {(void)position; (void)val; (void)n;}
	template <class InputIterator>
	 void		insert (iterator position, InputIterator first, InputIterator last)	{ (void)position; (void)first; (void)last; }
	iterator	erase (iterator position)											{ return _m_erase(position); }
	iterator	erase (iterator first, iterator last)								{ return _m_erase(first, last); }
	void		swap (vector& other)
	{
		if (this == &other)
			return;
		ft::swap(*this, other);
	}
	void		clear()
	{
		_m_erase_at_end(_m_impl._m_start);
	}

	// Allocator
	allocator_type get_allocator() const { return allocator_type(); }

private:

	void _m_create_storage(size_type n)
	{
		_m_impl._m_start = _m_alloc.allocate(n);
		_m_impl._m_finish = _m_impl._m_start;
		_m_impl._m_end_of_storage = _m_impl._m_start + n;
	}

	void _m_deallocate(pointer p, size_type n)
	{
		pointer it = p + n;
		while(it != p)
			_m_alloc.destroy(--it);
		_m_alloc.deallocate(p, n);
	}

	void _m_erase_at_end(pointer p)
	{
		const size_type n = _m_impl._m_finish - _m_impl._m_start;
		pointer it = p + n;
		while(it != p)
			_m_alloc.destroy(--it);
		_m_impl._m_finish = p;
	}

	iterator _m_erase(iterator position)
	{
		if (position + 1 != _m_impl._m_finish)
			std::copy(position + 1, end(), position);
		--_m_impl._m_finish;
		_m_alloc.destroy(_m_impl._m_finish);
		return position;
	}

	iterator _m_erase(iterator first, iterator last)
	{
		if (first != last)
		{
			if (last != end())
				std::copy(last, end(), first);
			_m_erase_at_end(first.base() + (end() - last));
		}
		return first;
	}

	void _m_grow()
	{
		const size_type actualSize = _m_impl._m_end_of_storage - _m_impl._m_start;
		const size_type newSize = std::max(2 * actualSize, size_type(1));

		const pointer newBuffer = _m_alloc.allocate(newSize);
		std::uninitialized_copy(_m_impl._m_start, _m_impl._m_finish, newBuffer);
		_m_deallocate(_m_impl._m_start, actualSize);
		_m_impl._m_start = newBuffer;
		_m_impl._m_finish = newBuffer + actualSize;
		_m_impl._m_end_of_storage = newBuffer + newSize;
	}



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
  void swap (vector<_T, _Alloc>& x, vector<_T, _Alloc>& y) { x.swap(y); }

template<class _T, class _Alloc>
typename vector<_T, _Alloc>::allocator_type  vector<_T, _Alloc>::_m_alloc;



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
