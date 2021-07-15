/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:34:07 by juligonz          #+#    #+#             */
/*   Updated: 2021/07/15 18:08:02 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <memory>
#include <utility>

namespace ft {
template < class _Key,                                     // map::key_type
           class _T,                                       // map::mapped_type
           class _Compare = std::less<Key>,                     // map::key_compare
           class _Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
           > 
class map
{
	
}

} /* _FT_MAP_HPP */
