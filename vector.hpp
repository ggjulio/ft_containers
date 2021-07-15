/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:34:04 by juligonz          #+#    #+#             */
/*   Updated: 2021/07/15 18:00:08 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef _FT_VECTOR_H
#define _FT_VECTOR_H


#include <memory>
#include <vector> // to delete
#include <iterator>

namespace ft{

// template<typename _T, typename _Alloc = std::allocator<_T> >
// struct _Vector_base<_T, _Alloc>
// {
	
// }

template<typename _T, typename _Alloc = std::allocator<_T> >
class vector: /// protected _Vector_base<_T, _Alloc>class vector
{
public:
	typedef typename _T								value_type;
	typedef typename _Alloc							allocator_type;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	// typedef allocator_type::pointer					pointer;
	// typedef allocator_type::connst_pointer			const_pointer;
	// typedef pointer							iterator;
	// typedef const								const_iterator;
	typedef 			reverse_iterator;
	typedef 	const_reverse_iterator;
	typedef ptrdiff_t		difference_type;
	typedef size_t			size_type; 

private:
	int _size;
	int _capacity;
	_T *_ptrArray;

public:
	/// Constructs an empty container, with no elements.
	vector (const allocator_type& alloc = allocator_type()):
		_size(0), _capacity(0) _ptrArray(NULL){}
	/// Constructs a container with n elements. Each element is a copy of val.
	vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
		_size(n), _capacity(0), _ptrArray(NULL)
	{
		_ptrArray(alloc.allocate(n));
		for (size_t i = 0; i < n; i++)
			alloc.construct(_ptrArray + i, val);
			// _ptrArray[i] = val;
	}
	// Range constructor
	// template <class InputIterator>
	// vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()):
	// 	_size(0), _capacity(0), _ptrArray(NULL)
	// {
	// 	alloc.allocate();
	// 
	// }
	/// Copy constructor
	vector (const vector& other) {}
	// assign operator
	// vector & operator=(const vector & other){}
	~vector(){}

	// iterators
	iterator 				begin();
	// const_iterator			begin() const;
	// iterator				end();
	// const_iterator			end() const;
	// reverse_iterator 		rbegin();
	// const_reverse_iterator 	rbegin() const;
	// reverse_iterator		rend();
	// const_reverse_iterator	rend() const;
	
	// capacity
	size_type				size() const;
	size_type				max_size() const;
	void					resize (size_type n, value_type val = value_type());
	size_type				capacity() const;
	bool					empty() const;
	void					reserve(size_type n)
	{
		if(n <= _size)
			return;
		
		value_type  *newPtrArray = new value_type[n]; // to replace using allocator
		this->_capacity = n;
	}

	// Element access
	reference				operator[](size_type n)			{ return _ptrArray[n];} // throw exeception out of range ?
	const_reference			operator[](size_type n) const	{ return _ptrArray[n];}
	reference 				at(size_type n) 				{ }
	const_reference 		at(size_type n) const			{ }
	reference 				front();
	const_reference			front() const;
	reference				back();
	const_reference			back() const;

	// Modifiers
	template <class InputIterator>
	  void		assign(InputIterator first, InputIterator last) {}
	void 		assign(size_type n, const value_type& val) {}
	void 		push_back(const value_type& val)
	{
		if (_size == _capacity)
			reserve( 2 * _capacity + 1);
		_ptrArray[_size++] = val;
	}
	// void		pop_back() {}
	// iterator 	insert(iterator position, const value_type& val) {}
	// void		insert (iterator position, size_type n, const value_type& val) {}
	// template <class InputIterator>
    //   void		insert (iterator position, InputIterator first, InputIterator last){}
	// iterator	erase (iterator position) {}
	// iterator	erase (iterator first, iterator last) {}
	// void		swap (vector& other);
	// void		clear();

	// Allocator
	allocator_type get_allocator() const;

	
private:
	// template<class _T1, class _Alloc1>
	// friend bool operator==(const vector<_T1, _Alloc1>&, const vector<_T1, _Alloc1>&);
	
	// template<class _T1, class _Alloc1>
	// friend bool operator<(const vector<_T1, _Alloc1>&, const vector<_T1, _Alloc1>&);
};

// template<class _T, class _Alloc>
// 	inline bool
// 	operator==(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
// 	{ return lhs.c == rhs.c; }

// template<class _T, class _Alloc>
// 	inline bool
// 	operator<(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
// 	{ return lhs.c < rhs.c; }



// template<class _T, class _Alloc>
// 	inline bool
// 	operator!=(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
// 	{ return !(lhs == rhs); }

// template<class _T, class _Alloc>
// 	inline bool
// 	operator<=(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
// 	{ return !(rhs < lhs); }

// template<class _T, class _Alloc>
// 	inline bool
// 	operator>(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
// 	{ return rhs < lhs; }

// template<class _T, class _Alloc>
// 	inline bool
// 	operator>=(const vector<_T, _Alloc>& lhs, const vector<_T, _Alloc>& rhs)
// 	{ return !(lhs < rhs); }

// template <class _T, class _Alloc>
//   void swap (vector<_T, _Alloc>& x, vector<_T, _Alloc>& y) {}

} // namespace

#endif /* _FT_VECTOR_HPP */
