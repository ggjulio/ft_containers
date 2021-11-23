/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 02:50:36 by lmartin           #+#    #+#             */
/*   Updated: 2020/08/12 04:46:08 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include "colors.h"

template <class Container>
void	printContainer(Container c)
{
	int								n;
	typename Container::iterator	i;
	
	i = c.begin();
	n = 0;
	std::cout << _YELLOW << "---------------------- " << "[" << _GREEN;
	while (i != c.end())
	{
		if (n != 0)
			std::cout << ", ";
		std::cout << _GREEN << *i << _END;
		i++;
		n++;
	}
	std::cout << _YELLOW << "]" << _END << std::endl;
	std::cout << std::endl;
}

void		test_queue(void);
void		test_map(void);
void		test_stack(void);
void		test_list(void);
void		test_vector(void);

#endif
