/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juligonz <juligonz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:33:59 by juligonz          #+#    #+#             */
/*   Updated: 2021/03/10 19:08:30 by juligonz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <deque> // to remove #######################

namespace ft{

  /**
   *  A standard container giving FILO behavior.
   *
   *  @tparam _T  			Type of element.
   *  @tparam _Container  	Type of underlying sequence, defaults to deque<_T>.
   *
   *  Meets many of the requirements of a container,
   *  but does not define anything to do with iterators.  Very few of the
   *  other standard container interfaces are defined.
   *
   *  This is not a true container, but an adaptor. It holds
   *  another container, and provides a wrapper interface to that
   *  container.  The wrapper is what enforces strict
   *  first-in-last-out %stack behavior.
   *
   *  The second template parameter defines the type of the underlying
   *  sequence/container.  It defaults to ft::deque, but it can be
   *  any type that supports @c back, @c push_back, and @c pop_back,
   *  such as ft::list, ft::vector, or an appropriate user-defined
   *  type.
   *
   *  Members not found in normal containers are @c container_type,
   *  which is a typedef for the second Sequence parameter, and
   *  @c push, @c pop, and @c top, which are standard %stack/FILO
   *  operations.
  */

template<class _T, class _Container=std::deque<_T> >
class stack
{
	public:
		typedef typename _Container::value_type			value::type;
		typedef typename _Container::reference			reference;
		typedef typename _Container::const_reference	const_reference;
		typedef typename _Container::size_type			size_type;
		typedef typename _Container						container_type;
		
	protected:
		_Container c;

	public:
		stack(): c(){}
		stack(const _Container& other): c(other){}

		
		empty(){
			
		}		
	private:
		
}


}