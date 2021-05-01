/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:34:04 by juligonz          #+#    #+#             */
/*   Updated: 2021/05/01 02:20:04 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef _FT_VECTOR_H
#define _FT_VECTOR_H


#include <memory>

namespace ft{

template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
class vector : // protected _Vector_base<_Tp, _Alloc>class vector
{
public:
	typedef typename _T			value_type;
	//allocator ??
	typedef typename 			value_type;
	
	typedef typename _Container::size_type			size_type;

protected:
	_Container c;

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
