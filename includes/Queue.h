/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:34:14 by juligonz          #+#    #+#             */
/*   Updated: 2021/05/01 02:03:27 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_QUEUE_H
#define _FT_QUEUE_H

#include <deque> // to remove #######################

namespace ft{

template<class _T, class _Container=std::deque<_T> >
class queue
{
public:
	typedef typename _Container::value_type			value_type;
	typedef typename _Container::size_type			size_type;
	typedef 		 _Container 					container_type;

protected:
	_Container c;

public:
	explicit queue(const container_type& ctnr = container_type()): c(ctnr){}

	bool				empty(void) const 				{ return c.empty(); }
	size_type			size() const					{ return c.size(); }
    value_type&			front()							{ return c.front(); }
	const value_type&	front() const					{ return c.front(); }
    value_type&			back()							{ return c.back(); }
	const value_type&	back() const					{ return c.back(); }
	void				push(const value_type& value)	{ c.push_back(value); }
    void				pop(void)						{ c.pop_front(); }


private:
	template<class _T1, class _Container1>
	friend bool operator==(const queue<_T1, _Container1>&, const queue<_T1, _Container1>&);
	
	template<class _T1, class _Container1>
	friend bool operator<(const queue<_T1, _Container1>&, const queue<_T1, _Container1>&);
};

template<class _T, class _Container>
	inline bool
	operator==(const queue<_T, _Container>& lhs, const queue<_T, _Container>& rhs)
	{ return lhs.c == rhs.c; }

template<class _T, class _Container>
	inline bool
	operator<(const queue<_T, _Container>& lhs, const queue<_T, _Container>& rhs)
	{ return lhs.c < rhs.c; }



template<class _T, class _Container>
	inline bool
	operator!=(const queue<_T, _Container>& lhs, const queue<_T, _Container>& rhs)
	{ return !(lhs == rhs); }

template<class _T, class _Container>
	inline bool
	operator<=(const queue<_T, _Container>& lhs, const queue<_T, _Container>& rhs)
	{ return !(rhs < lhs); }

template<class _T, class _Container>
	inline bool
	operator>(const queue<_T, _Container>& lhs, const queue<_T, _Container>& rhs)
	{ return rhs < lhs; }

template<class _T, class _Container>
	inline bool
	operator>=(const queue<_T, _Container>& lhs, const queue<_T, _Container>& rhs)
	{ return !(lhs < rhs); }

} // namespace

#endif /* _FT_QUEUE_H */
