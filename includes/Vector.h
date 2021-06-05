/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:34:04 by juligonz          #+#    #+#             */
/*   Updated: 2021/06/05 17:52:10 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef _FT_VECTOR_H
#define _FT_VECTOR_H


#include <memory>
#include <vector> // to delete

namespace ft{

template<typename _T, typename _Alloc = std::allocator<_T> >
class vector //: protected _Vector_base<_T, _Alloc>class vector
{
public:
	typedef typename _T			value_type;
	typedef typename _Alloc		allocator_type;
	typedef value_type&			reference;
	typedef const value_type&	const_reference;
	typedef f		pointer;
	typedef f		const_pointer;
	typedef f		iterator;
	typedef f		const_iterator;
	typedef f		reverse_iterator;
	typedef f		const_reverse_iterator;
	typedef f		difference_type;

	typedef typename _Container::size_type			size_type;

protected:
	_Container ctrn;

public:
	vector(const _Container& ctnr = _Container()): c(ctnr){}

	bool				empty(void) const 				{ return c.empty(); }
	size_type			size() const					{ return c.size(); }
	value_type&			top(void)						{ return c.back(); }
	const value_type&	top(void) const					{ return c.back(); }
	void				push(const value_type& value)	{ c.push_back(value); }
    void				pop(void)						{ c.pop_back(); }


private:
	template<class _T1, class _Container1>
	friend bool operator==(const vector<_T1, _Container1>&, const vector<_T1, _Container1>&);
	
	template<class _T1, class _Container1>
	friend bool operator<(const vector<_T1, _Container1>&, const vector<_T1, _Container1>&);
};

template<class _T, class _Container>
	inline bool
	operator==(const vector<_T, _Container>& lhs, const vector<_T, _Container>& rhs)
	{ return lhs.c == rhs.c; }

template<class _T, class _Container>
	inline bool
	operator<(const vector<_T, _Container>& lhs, const vector<_T, _Container>& rhs)
	{ return lhs.c < rhs.c; }



template<class _T, class _Container>
	inline bool
	operator!=(const vector<_T, _Container>& lhs, const vector<_T, _Container>& rhs)
	{ return !(lhs == rhs); }

template<class _T, class _Container>
	inline bool
	operator<=(const vector<_T, _Container>& lhs, const vector<_T, _Container>& rhs)
	{ return !(rhs < lhs); }

template<class _T, class _Container>
	inline bool
	operator>(const vector<_T, _Container>& lhs, const vector<_T, _Container>& rhs)
	{ return rhs < lhs; }

template<class _T, class _Container>
	inline bool
	operator>=(const vector<_T, _Container>& lhs, const vector<_T, _Container>& rhs)
	{ return !(lhs < rhs); }

} // namespace

#endif /* _FT_VECTOR_H */
