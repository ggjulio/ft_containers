#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <utility>

namespace ft {
template < class _Key,                                     // map::key_type
           class _T,                                       // map::mapped_type
           class _Compare = std::less<_Key>,                     // map::key_compare
           class _Alloc = std::allocator<std::pair<const _Key,_T> >    // map::allocator_type
           > 
class map
{
public:
	typedef _Key						key_type;
	typedef _T							mapped_type;
	typedef std::pair<const _Key, _T>	value_type;
	typedef _Compare					key_compare;
	typedef _Alloc						allocator_type;

private:
	

};

} /* namespace ft */

#endif /* MAP_HPP */