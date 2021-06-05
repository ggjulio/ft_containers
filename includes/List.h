/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 15:30:35 by juligonz          #+#    #+#             */
/*   Updated: 2021/06/05 17:50:12 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_LIST_H
#define _FT_LIST_H

#include <memory>
#include <iterator>
#include <list> // to delete

namespace ft{

template < class _T, class _Alloc = std::allocator<_T> > 
class list
{
public:
	typedef typename _T			value_type;
	typedef typename _Alloc		allocator_type;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;
	
	typedef 		pointer;
	typedef f		const_pointer;
	
	typedef typename std::list<_T>::iterator				iterator;
	typedef typename std::list<_T>::const_iterator			const_iterator;
	typedef std::reverse_iterator<iterator>					reverse_iterator;
	typedef std::reverse_iterator<const_iterator>			const_reverse_iterator;
	
	// typedef typename f		difference_type;
	// typedef typename f		size_type;

	// default constructor
	list(const allocator_type& alloc = allocator_type()){}
	// fill constructor
	list(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){}
	// range constructor
	template <class InputIterator>
	list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()){}
	// Copy constructor
	list(const list& x){}
	~list(){}
	list& operator=(const list& x){}


// public:

// // Iterators
// 	iterator				begin()			{}
// 	const_iterator			begin() const 	{}
// 	iterator				end() 			{}
// 	const_iterator			end() const		{};
// 	reverse_iterator 		rbegin();
// 	const_reverse_iterator	rbegin() const;
// 	reverse_iterator		rend();
// 	const_reverse_iterator	rend() const;
	
// //Capacity
// 	bool			empty() const;
// 	size_type		size() const;
// 	size_type		max_size() const;

// // Element access
// 	reference		front();
// 	const_reference	front() const;
// 	reference		back();
// 	const_reference	back() const;

// //Modifiers
// template <class InputIterator>
// 	void		assign(InputIterator first, InputIterator last);
// 	void		assign(size_type n, const value_type& val);
// 	void		push_front(const value_type& val);
// 	void		pop_front();
// 	void		push_back(const value_type& val);
// 	void		pop_back();
// 	iterator	insert(iterator position, const value_type& val) {}
// 	void 		insert(iterator position, size_type n, const value_type& val) {}
// template <class InputIterator>
// 	void		insert(iterator position, InputIterator first, InputIterator last) {}
// 	iterator	erase(iterator position);
// 	iterator	erase(iterator first, iterator last);
// 	void		swap(list& x);
// 	void		resize(size_type n, value_type val = value_type());
// 	void		clear();

// //Operation
// 	void splice(iterator position, list& x);
// 	void splice(iterator position, list& x, iterator i);
// 	void splice(iterator position, list& x, iterator first, iterator last);
// 	void remove(const value_type& val);
// template <class Predicate>
// 	void remove_if (Predicate pred);
// 	void unique();
// template <class BinaryPredicate>
// 	void unique(BinaryPredicate binary_pred);
// 	void merge(list& x);
// template <class Compare>
// 	void merge(list& x, Compare comp);
// 	void sort();
// template <class Compare>
// 	void sort(Compare comp);
// 	void reverse();

	// ?? allocator_type get_allocator() const;

private:
	// operators todo
	
};

// template <class T, class Alloc>
// 	bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs){}
// template <class T, class Alloc>
// 	bool operator!=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs){}
// template <class T, class Alloc>
// 	bool operator<(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs){}
// template <class T, class Alloc>
// 	bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs){}
// template <class T, class Alloc>
// 	bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs){}
// template <class T, class Alloc>
// 	bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs){}

// template <class T, class Alloc>
//   void swap (list<T,Alloc>& x, list<T,Alloc>& y);

} // namespace

#endif /* _FT_LIST_H */
