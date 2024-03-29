#ifndef VECTOR_H
#define VECTOR_H

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include "utility.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft{

template<typename _T, typename _Alloc = std::allocator<_T> >
class vector
{
	template<typename __T>
	struct _vector_impl
	{
		typedef __T*			pointer;

		pointer  _m_start;
		pointer  _m_finish;
		pointer  _m_end_of_storage;

		_vector_impl()
			: _m_start(), _m_finish(), _m_end_of_storage()
		{}

		void _m_copy_data(_vector_impl& other)
		{
			_m_start = other._m_start;
			_m_finish = other._m_finish;
			_m_end_of_storage = other._m_end_of_storage;
		}
		void _m_swap_data(_vector_impl& other)
		{
			_vector_impl tmp;

			tmp._m_copy_data(*this);
			_m_copy_data(other);
			other._m_copy_data(tmp);
		}

		void _m_reset()
		{
			*this = _vector_impl();
		}
	};


public:
	typedef _T								value_type;
	typedef _Alloc							allocator_type;

	typedef size_t							size_type; 
	typedef std::ptrdiff_t					difference_type;
	typedef value_type&						reference;
	typedef const value_type&				const_reference;
	typedef value_type*						pointer;
	typedef const value_type*				const_pointer;

	typedef normal_iterator<value_type>				iterator;
	typedef normal_iterator<const value_type>		const_iterator;
	typedef ft::reverse_iterator<iterator>			reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

private:
	_vector_impl<value_type> _m_impl;
	allocator_type _m_alloc;

public:
	// default
	explicit vector (const allocator_type& alloc = allocator_type())
		: _m_alloc(alloc)
	{}
	// fill
	explicit vector (size_type n, const value_type& val = value_type(),
			const allocator_type& alloc = allocator_type())
		: _m_alloc(alloc)
	{
		_m_create_storage(n);
		_m_impl._m_finish = std::uninitialized_fill_n(_m_impl._m_start, n, val);
	}
	// range
	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
		: _m_alloc(alloc)
	{
		_m_create_storage(std::distance(first, last));
		while (first != last)
		{
			push_back(*first);
			++first;
		}
	}
	
	vector(const vector& other)
	{
		if (this == &other || other._m_impl._m_start == 0)
			return;
		const size_type otherLen = other.size();
		_m_impl._m_start = _m_allocate_and_copy(otherLen, other.begin(), other.end());
		_m_impl._m_finish = _m_impl._m_start + otherLen;
		_m_impl._m_end_of_storage = _m_impl._m_finish;
		_m_alloc = other._m_alloc;
	}

	~vector() {
		if (_m_impl._m_start)
		{
			clear();
			_m_deallocate();
		}
	}

	vector& operator= (const vector& other)
	{
		if (this == &other)
			return *this;
		const size_type otherLen = other.size();
		if (otherLen > capacity())
		{
			pointer start = _m_allocate_and_copy(otherLen, other.begin(), other.end());
			if (_m_impl._m_start)
			{
				_m_destroy();
				_m_deallocate();
			}
			_m_impl._m_start = start;
			_m_impl._m_end_of_storage = start + otherLen;
		}
		else if (size() >= otherLen)
		{
			iterator it = std::copy(other.begin(), other.end(), begin());
			_m_erase_at_end(it.base());
		}
		else
		{
			std::copy(other._m_impl._m_start, other._m_impl._m_start + size(), _m_impl._m_start);
			std::uninitialized_copy(other._m_impl._m_start + size(), other._m_impl._m_finish, _m_impl._m_finish);
		}
		_m_impl._m_finish = _m_impl._m_start + otherLen;
		return *this;
	}

	// iterators
	iterator 				begin()			{ return _m_impl._m_start; }
	const_iterator			begin() const	{ return _m_impl._m_start; }
	iterator				end()			{ return _m_impl._m_finish; }
	const_iterator			end() const		{ return _m_impl._m_finish; }
	reverse_iterator 		rbegin()		{ return end(); }
	const_reverse_iterator 	rbegin() const	{ return end(); }
	reverse_iterator		rend()			{ return begin(); }
	const_reverse_iterator	rend() const	{ return begin(); }

	// capacity
	size_type	size() const										{ return _m_impl._m_finish - _m_impl._m_start; }
	size_type	max_size() const									{ return _m_alloc.max_size(); }
	void		resize (size_type n, value_type val = value_type())
	{
		if (n > size())
			_m_fill_insert(end(), n - size(), val);
		else if (n < size())
			_m_erase_at_end(_m_impl._m_start + n);
	}
	size_type	capacity() const									{ return _m_impl._m_end_of_storage - _m_impl._m_start; }
	bool		empty() const										{ return begin() == end();}
	void		reserve(size_type n)
	{
		if (n > max_size())
			throw std::length_error("AH");
		if (capacity() < n)
			_m_reallocate(n);
	}

	// Element access
	reference			operator[](size_type n)	throw()			{ return *(_m_impl._m_start + n); }
	const_reference		operator[](size_type n) const throw()	{ return *(_m_impl._m_start + n); }
	reference 			at(size_type n) 				{ _m_range_check(n); return (*this)[n]; }
	const_reference 	at(size_type n) const			{ _m_range_check(n); return (*this)[n]; }
	reference 			front()	throw()					{ return *begin(); }
	const_reference		front() const throw()			{ return *begin(); }
	reference			back() throw()					{ return *(end() - 1); }
	const_reference		back() const throw()			{ return *(end() - 1); }

	// Modifiers
	template <class InputIterator>
	 void		assign(InputIterator first, InputIterator last,
	 					typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
	 {
		_m_assign_aux(first, last);
     }
	void 		assign(size_type n, const value_type& val)
	{
		clear();
		_m_fill_insert(begin(), n, val);
	}
	void 		push_back(const value_type& val)
	{
		if (_m_impl._m_finish == _m_impl._m_end_of_storage)
		{
			if (_m_impl._m_start == 0)
				_m_create_storage(1);
			else
				_m_grow();
		}
		_m_alloc.construct(_m_impl._m_finish++, val);
	}
	void		pop_back() {
		_m_alloc.destroy(--_m_impl._m_finish);
	}
	iterator 	insert(iterator position, const value_type& val)					{ return  _m_insert_val(position, val); }
	void		insert(iterator position, size_type n, const value_type& val)		{ _m_fill_insert(position, n, val); }
	template <class InputIterator>
	 void		insert(iterator position, InputIterator first, InputIterator last,
		 				typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
	 { 
		if (first == last)
			return;
		const size_type n = std::distance(first, last);
		if (size_type(_m_impl._m_end_of_storage - _m_impl._m_finish) >= n)
		{
			const size_type elemsAfter = end() - position;
			pointer oldFinish(_m_impl._m_finish);
			if (elemsAfter > n)
			{
				std::uninitialized_copy(_m_impl._m_finish - n, _m_impl._m_finish, end().base());
				std::copy_backward(position.base(), oldFinish - n, oldFinish);
				std::copy(first, last, position);
				_m_impl._m_finish += n;
			}
			else
			{
				InputIterator mid = first;
				std::advance(mid, elemsAfter);
				std::uninitialized_copy(mid, last, _m_impl._m_finish);
				_m_impl._m_finish += n - elemsAfter;
				std::uninitialized_copy(position.base(), oldFinish, _m_impl._m_finish);
				_m_impl._m_finish += elemsAfter;
				std::copy(first, mid, position);
			}
		}
		else
		{
			const size_type len = _m_check_len(n);
			pointer newStart = _m_allocate(len);
			std::uninitialized_copy(begin().base(), position.base(), newStart);
			std::uninitialized_copy(first, last, newStart + (position.base() - _m_impl._m_start));
			pointer newFinish = std::uninitialized_copy(position.base(), end().base(), newStart + (position.base() - _m_impl._m_start) + n);
			_m_destroy();
			_m_deallocate();
			_m_impl._m_start = newStart;
			_m_impl._m_finish = newFinish;
			_m_impl._m_end_of_storage = newStart + len;
		}
	}
	iterator	erase (iterator position)											{ return _m_erase(position); }
	iterator	erase (iterator first, iterator last)								{ return _m_erase(first, last); }
	void		swap (vector& other)
	{
		if (this == &other)
			return;
		ft::swap(_m_impl._m_start, other._m_impl._m_start);
		ft::swap(_m_impl._m_finish, other._m_impl._m_finish);
		ft::swap(_m_impl._m_end_of_storage, other._m_impl._m_end_of_storage);
		ft::swap(_m_alloc, other._m_alloc);
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
		_m_impl._m_start = _m_allocate(n);
		_m_impl._m_finish = _m_impl._m_start;
		_m_impl._m_end_of_storage = _m_impl._m_start + n;
	}

	pointer _m_allocate(size_type n)
	{
		return n == 0 ? pointer() : _m_alloc.allocate(n);
	}

	template<typename _Iter>
	pointer _m_allocate_and_copy(size_type n, _Iter first, _Iter last)
	{
		pointer result = _m_allocate(n);
		std::uninitialized_copy(first, last, result);
		return result;
	}

	void _m_deallocate()
	{
		_m_deallocate(_m_impl._m_start, _m_impl._m_end_of_storage - _m_impl._m_start);
		_m_impl._m_reset();
	}
	void _m_deallocate(pointer p, size_type n)
	{
		_m_alloc.deallocate(p, n);
	}

	void _m_destroy()
	{
		_m_destroy_range(_m_impl._m_start, _m_impl._m_finish);
		_m_impl._m_finish = _m_impl._m_start;
	}
	void _m_destroy_range(pointer first, pointer last)
	{
		while(first != last)
			_m_alloc.destroy(--last);
	}

	void _m_erase_at_end(pointer p)
	{
		const size_type n = _m_impl._m_finish - p;
		pointer it = p + n;
		if (n)
		{
			while(it != p)
				_m_alloc.destroy(--it);
			_m_impl._m_finish = p;
		}
	}

	iterator _m_erase(iterator position)
	{
		if (position.base() + 1 != _m_impl._m_finish)
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

	template <class _Iter>
	 void _m_assign_aux(_Iter first, _Iter last)
	 {
		const size_type len = std::distance(first, last);
		if (len > capacity())
		{
			pointer newStart = _m_allocate_and_copy(len, first, last);
			_m_destroy();
			_m_deallocate();
			_m_impl._m_start = newStart;
			_m_impl._m_finish = newStart + len;
			_m_impl._m_end_of_storage = _m_impl._m_finish;
		}
		else if (size() >= len)
			_m_erase_at_end(std::copy(first, last, _m_impl._m_start));
		else
		{
			_Iter mid = first;
			std::advance(mid, size());
			std::copy(first, mid, _m_impl._m_start);
			_m_impl._m_finish = std::uninitialized_copy(mid, last, _m_impl._m_finish);
		}
	 }

	iterator _m_insert_val(iterator pos, const value_type& val)
	{
		const size_type n = pos - begin();
		
		if (_m_impl._m_finish != _m_impl._m_end_of_storage)
		{
			if (pos == end())
				_m_alloc.construct(_m_impl._m_finish++, val);
			else
				_m_insert_aux(begin() + n, val);
		}
		else
			_m_insert_aux(begin() + n, val);
		return iterator(_m_impl._m_start + n);
	}

	void _m_insert_aux(iterator pos, const value_type& val)
	{
		if (_m_impl._m_finish != _m_impl._m_end_of_storage)
		{
			_m_alloc.construct(_m_impl._m_finish, *(_m_impl._m_finish-1));
			std::copy_backward(pos.base(), _m_impl._m_finish - 1, _m_impl._m_finish);
			*pos = val;
			++_m_impl._m_finish;
		}
		else
		{
			const size_type len = _m_check_len(size_type(1));
			pointer newStart = _m_alloc.allocate(len);
			std::uninitialized_copy(_m_impl._m_start, pos.base(), newStart);
			_m_alloc.construct(newStart + (pos - begin()), val);
			std::uninitialized_copy(pos, end(), newStart + (pos - begin()) + 1);
			const size_type oldSize = size();
			_m_destroy();
			_m_deallocate();
			_m_impl._m_end_of_storage = newStart + len;
			_m_impl._m_start = newStart;
			_m_impl._m_finish = newStart + oldSize + 1;
		}
	}

	size_type _m_check_len(size_type n) const
	{
		if (max_size() - size() < n)
			throw std::length_error("AH");
		const size_type len = size() + std::max(size(), n);
		return ( len < size() || len > max_size()) ? max_size() : len;
	}

	void _m_range_check(size_type n) const
	{
		if (n >= size())
			throw std::out_of_range("AH");
	}

	void _m_fill_insert(iterator pos, size_type n, const value_type& val)
	{
		if (n == 0)
			return;
		if (size_type(_m_impl._m_end_of_storage - _m_impl._m_finish) >= n)
		{
			const size_type elemsAfter = end() - pos;
			pointer oldFinish = _m_impl._m_finish;
			if (elemsAfter > n)
			{
				std::uninitialized_copy(_m_impl._m_finish - n, _m_impl._m_finish, _m_impl._m_finish);
				std::copy_backward(pos.base(), oldFinish - n, oldFinish);
				std::fill(pos.base(), pos.base() + n, val);
			}
			else
			{
				std::uninitialized_fill_n(_m_impl._m_finish, n - elemsAfter, val);
				std::uninitialized_copy(pos.base(), oldFinish, _m_impl._m_finish);
				std::fill(pos.base(), oldFinish, val);
			}
			_m_impl._m_finish += n;
		}
		else
		{
			const size_type len = _m_check_len(size_type(n));
	    	const size_type elemsBefore = pos - begin();
			pointer newStart(_m_allocate(len));
			pointer newFinish(newStart);

			std::uninitialized_fill_n(newStart + elemsBefore, n, val);
			newFinish = std::uninitialized_copy(_m_impl._m_start, pos.base(), newStart);
			newFinish += n;
			newFinish = std::uninitialized_copy(pos.base(), _m_impl._m_finish, newFinish);
		
			_m_destroy();
			_m_deallocate(_m_impl._m_start, _m_impl._m_end_of_storage - _m_impl._m_start);
			_m_impl._m_start = newStart;
			_m_impl._m_finish = newFinish;
			_m_impl._m_end_of_storage = newStart + len;

		}
	}

	void _m_reallocate(size_type n)
	{
		pointer newStart(_m_allocate(n));
		pointer newFinish(std::uninitialized_copy(_m_impl._m_start, _m_impl._m_finish, newStart));
		_m_destroy();
		_m_deallocate(_m_impl._m_start, _m_impl._m_end_of_storage - _m_impl._m_start);
		_m_impl._m_start = newStart;
		_m_impl._m_finish = newFinish;
		_m_impl._m_end_of_storage = newStart + n;
	}

	void _m_grow()
	{
		const size_type actualSize = _m_impl._m_end_of_storage - _m_impl._m_start;
		const size_type newSize = std::max(2 * actualSize, size_type(1));

		const pointer newStart = _m_alloc.allocate(newSize);
		std::uninitialized_copy(_m_impl._m_start, _m_impl._m_finish, newStart);
		_m_destroy();
		_m_deallocate(_m_impl._m_start, actualSize);
		_m_impl._m_start = newStart;
		_m_impl._m_finish = newStart + actualSize;
		_m_impl._m_end_of_storage = newStart + newSize;
	}

}; /* class vector */

template<typename _T, typename _Alloc>
inline bool
operator==(const vector<_T, _Alloc>& x, const vector<_T, _Alloc>& y)
{ return (x.size() == y.size()
	&& std::equal(x.begin(), x.end(), y.begin())); }

template<typename _T, typename _Alloc>
inline bool
operator<(const vector<_T, _Alloc>& x, const vector<_T, _Alloc>& y)
{ return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template<typename _T, typename _Alloc>
inline bool
operator!=(const vector<_T, _Alloc>& x, const vector<_T, _Alloc>& y)
{ return !(x == y); }

template<typename _T, typename _Alloc>
inline bool
operator>(const vector<_T, _Alloc>& x, const vector<_T, _Alloc>& y)
{ return y < x; }

template<typename _T, typename _Alloc>
inline bool
operator<=(const vector<_T, _Alloc>& x, const vector<_T, _Alloc>& y)
{ return !(y < x); }

template<typename _T, typename _Alloc>
inline bool
operator>=(const vector<_T, _Alloc>& x, const vector<_T, _Alloc>& y)
{ return !(x < y); }

template <class _T, class _Alloc>
  void swap (vector<_T, _Alloc>& x, vector<_T, _Alloc>& y) { x.swap(y); }

} /* namespace ft */

#endif /* VECTOR_H */
