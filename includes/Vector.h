/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:34:04 by juligonz          #+#    #+#             */
/*   Updated: 2021/05/01 02:02:27 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef _FT_VECTOR_H
#define _FT_VECTOR_H


namespace ft{

template<class _T, class _Container=std::deque<_T> >
class vector
{
public:
	typedef typename _Container::value_type			value_type;
	typedef typename _Container::size_type			size_type;
	typedef 		 _Container 					container_type;

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
