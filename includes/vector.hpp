#ifndef VECTOR_H
#define VECTOR_H


#include <memory>
#include <algorithm>
#include <cassert>
#include "utility.hpp"
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

		vector_iterator()						: _m_ptr(pointer()) {}
		vector_iterator(pointer ptr): _m_ptr(ptr) {}
		vector_iterator(const T& i) : _m_ptr(i) {}
		// vector_iterator(const Self& it) throw()	: _m_ptr(it._m_ptr) {}

		operator vector_iterator<const T> () const
			{ return (vector_iterator<const T>(this->_m_ptr)); }

		reference	operator*() const throw()		{ return *_m_ptr; }
		pointer		operator->() const throw()		{ return _m_ptr; }
		reference	operator[](size_t n) const		{ return *(_m_ptr + n); }

		Self &operator++() throw()		{ ++_m_ptr; return *this; }
		Self operator++(int) throw()	{ Self tmp = *this; ++_m_ptr; return tmp; }

		Self &operator--() throw()		{ _m_ptr -= 1; return *this; }
		Self operator--(int) throw()	{ Self tmp = *this; --_m_ptr; return tmp; }

		Self  operator+ (difference_type n) const	{ return _m_ptr + n;}
		Self& operator+=(difference_type n)			{ _m_ptr += n; return *this;}
		Self  operator- (difference_type n) const	{ return _m_ptr - n;}
		Self& operator-=(difference_type n) 		{ _m_ptr -= n; return *this;}

		// bool operator==	(const Self &other) { return (_m_ptr == other._m_ptr); };
		// bool operator!=	(const Self &other) { return (_m_ptr != other._m_ptr); };
		// bool operator<	(const Self &other) const { return (_m_ptr < other._m_ptr); };
		// bool operator>	(const Self &other) const { return (_m_ptr > other._m_ptr); };
		// bool operator<=	(const Self &other) const { return (_m_ptr <= other._m_ptr); };
		// bool operator>=	(const Self &other) const { return (_m_ptr >= other._m_ptr); };

		// friend bool operator==(const Self &x, const Self &y) throw() { return x._m_ptr == y._m_ptr; }
		// friend bool operator!=(const Self &x, const Self &y) throw() { return !(x._m_ptr == y._m_ptr); }


		pointer base() const {return _m_ptr; }

		// operator Self<const value_type > () const { return _m_ptr; }
	protected:
		pointer _m_ptr;
	}; /* struct vector_iterator */

template<typename IterL, typename IterR>
inline bool
operator==(const vector_iterator<IterL>& x, const vector_iterator<IterR>& y) throw()
{ return x.base() == y.base(); }

template<typename _T>
inline bool
operator==(const vector_iterator<_T>& x, const vector_iterator<_T>& y) throw()
{ return x.base() == y.base(); }

template<typename IterL, typename IterR>
inline bool
operator!=(const vector_iterator<IterL>& x, const vector_iterator<IterR>& y) throw()
{ return x.base() != y.base(); }

template<typename _T>
inline bool
operator!=(const vector_iterator<_T>& x, const vector_iterator<_T>& y) throw()
{ return x.base() != y.base(); }

  // Random access iterator requirements
template<typename IterL, typename IterR>
inline bool
operator<(const vector_iterator<IterL>& x, const vector_iterator<IterR>& y) throw()
{ return x.base() < y.base(); }

template<typename _T>
inline bool
operator<(const vector_iterator<_T>& x, const vector_iterator<_T>& y) throw()
{ return x.base() < y.base(); }

template<typename IterL, typename IterR>
inline bool
operator>(const vector_iterator<IterL>& x, const vector_iterator<IterR>& y) throw()
{ return x.base() > y.base(); }

template<typename _T>
inline bool
operator>(const vector_iterator<_T>& x, const vector_iterator<_T>& y) throw()
{ return x.base() > y.base(); }

template<typename IterL, typename IterR>
inline bool
operator<=(const vector_iterator<IterL>& x, const vector_iterator<IterR>& y) throw()
{ return x.base() <= y.base(); }

template<typename _T>
inline bool
operator<=(const vector_iterator<_T>& x, const vector_iterator<_T>& y) throw()
{ return x.base() <= y.base(); }

template<typename IterL, typename IterR>
inline bool
operator>=(const vector_iterator<IterL>& x, const vector_iterator<IterR>& y) throw()
{ return x.base() >= y.base(); }

template<typename _T>
inline bool
operator>=(const vector_iterator<_T>& x, const vector_iterator<_T>& y) throw()
{ return x.base() >= y.base(); }



	template <typename T>
	typename vector_iterator<T>::difference_type
	 operator-(const vector_iterator<T>& x,
			  const vector_iterator<T>& other)
	{
		return (x.base() - other.base());
	}

	template<typename IteratorL, typename IteratorR>
	typename vector_iterator<IteratorL>::difference_type
	 operator-(const vector_iterator<IteratorL>& x,
			  const vector_iterator<IteratorR>& other)
	{
		return (x.base() - other.base());
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
		: _m_start(), _m_finish(), _m_end_of_storage()
	{}

	void _m_reset()
	{
		*this = _vector_impl();
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
	typedef ft::reverse_iterator<iterator>				reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

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
	// template <class InputIterator,
	// 	typename enable_if<!is_integral<InputIterator>::value, bool>::type = true>
	template <class InputIterator>
	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
		typename enable_if<!is_integral<InputIterator>::value, bool>::type = true)
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

	~vector() {
		if (_m_impl._m_start)
			_m_deallocate();
	}

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
	iterator 	insert(iterator position, const value_type& val) {return  _m_insert_val(position, val); }
	void		insert (iterator position, size_type n, const value_type& val) {(void)position; (void)val; (void)n;}
	template <class InputIterator>
	 void		insert (iterator position, InputIterator first, InputIterator last)	{ (void)position; (void)first; (void)last; }
	iterator	erase (iterator position)											{ return _m_erase(position); }
	iterator	erase (iterator first, iterator last)								{ return _m_erase(first, last); }
	void		swap (vector& other)
	{
		if (this == &other)
			return;
		ft::swap(_m_impl._m_start, other._m_impl._m_start);
		ft::swap(_m_impl._m_finish, other._m_impl._m_finish);
		ft::swap(_m_impl._m_end_of_storage, other._m_impl._m_end_of_storage);
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

	pointer _m_allocate(size_type n)
	{
		return n == 0 ? pointer() : _m_alloc.allocate(n);
	}
	void _m_deallocate()
	{
		_m_deallocate(_m_impl._m_start, _m_impl._m_end_of_storage - _m_impl._m_start);
		_m_impl._m_reset();
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
			_m_deallocate();
			_m_impl._m_end_of_storage = newStart + len;
			_m_impl._m_start = newStart;
			_m_impl._m_finish = newStart + oldSize + 1;
		}
	}

	size_type _m_check_len(size_type n) const
	{
		if (max_size() - size() < n)
			assert(false); // do we need to throw ?
		const size_type len = size() + std::max(size(), n);
		return ( len < size() || len > max_size()) ? max_size() : len;
	}

	void _m_fill_insert(iterator pos, size_type n, const value_type& val)
	{
		if (!n)
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
			throw "shit";
		}
	}

	void _m_grow()
	{
		const size_type actualSize = _m_impl._m_end_of_storage - _m_impl._m_start;
		const size_type newSize = std::max(2 * actualSize, size_type(1));

		const pointer newStart = _m_alloc.allocate(newSize);
		std::uninitialized_copy(_m_impl._m_start, _m_impl._m_finish, newStart);
		_m_deallocate(_m_impl._m_start, actualSize);
		_m_impl._m_start = newStart;
		_m_impl._m_finish = newStart + actualSize;
		_m_impl._m_end_of_storage = newStart + newSize;
	}

	void _m_grow(size_type n)
	{
		const size_type actualSize = _m_impl._m_end_of_storage - _m_impl._m_start;
		const size_type doubleSize = std::max(2 * actualSize, size_type(1));
		const size_type newSize = n > doubleSize ? n : doubleSize;
		// const size_type newSize = std::max(2 * actualSize, size_type(1));

		const pointer newStart = _m_alloc.allocate(newSize);
		std::uninitialized_copy(_m_impl._m_start, _m_impl._m_finish, newStart);
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

template<class _T, class _Alloc>
typename vector<_T, _Alloc>::allocator_type  vector<_T, _Alloc>::_m_alloc;


} /* namespace ft */

#endif /* VECTOR_H */
