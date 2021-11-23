/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 04:08:02 by lmartin           #+#    #+#             */
/*   Updated: 2020/08/12 04:50:17 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <iomanip>
#include <stack>
#include <list>
#include "colors.h"
#include "utils.hpp"
#include "stack.hpp"

void		test_stack(void)
{
	std::cout << _WHITE << "# test_stack" << _END << std::endl;
	std::cout << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                          "<< _WHITE << "BASIC TESTS" << _YELLOW << "                                   */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	ft::stack<int> mystack;

	std::cout << "ft::stack<" << _PURPLE << "int" << _END << "> mystack" << std::endl;
	std::cout << std::endl;


	std::cout << _WHITE << "# empty" << _END << std::endl;
	std::cout << "mystack.empty(): " <<  mystack.empty() << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << _WHITE << "# one element" << _END << std::endl;
	mystack.push(42);
	std::cout << "mystack.push(42)" << std::endl;
	std::cout << "mystack.empty(): " <<  mystack.empty() << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << "mystack.top(): " << mystack.top() << std::endl;
	std::cout << _WHITE << "# two element" << _END << std::endl;
	mystack.push(2);
	std::cout << "mystack.push(2)" << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << "mystack.top(): " << mystack.top() << std::endl;
	std::cout << _WHITE << "# pop element" << _END << std::endl;
	mystack.pop();
	std::cout << "mystack.pop()" << std::endl;
	std::cout << "mystack.size(): " << mystack.size() << std::endl;
	std::cout << "mystack.top(): " << mystack.top() << std::endl;
	std::cout << std::endl;

	ft::stack<int, std::list<int> > mystack2;

	std::cout << "ft::stack<" << _PURPLE << "int" << _END << ", " << _PURPLE << "std::list" << _END << "> mystack2" << std::endl;
	std::cout << std::endl;


	std::cout << _WHITE << "# empty" << _END << std::endl;
	std::cout << "mystack2.empty(): " <<  mystack2.empty() << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << _WHITE << "# one element" << _END << std::endl;
	mystack2.push(42);
	std::cout << "mystack2.push(42)" << std::endl;
	std::cout << "mystack2.empty(): " <<  mystack2.empty() << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
	std::cout << _WHITE << "# two element" << _END << std::endl;
	mystack2.push(2);
	std::cout << "mystack2.push(2)" << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
	std::cout << _WHITE << "# pop element" << _END << std::endl;
	mystack2.pop();
	std::cout << "mystack2.pop()" << std::endl;
	std::cout << "mystack2.size(): " << mystack2.size() << std::endl;
	std::cout << "mystack2.top(): " << mystack2.top() << std::endl;
	std::cout << std::endl;

	std::cout << _WHITE << "# test cpy and equality" << _END << std::endl;
	ft::stack<int>	cpystack = mystack;
	std::cout << "ft::stack<" << _PURPLE << "int" << _END << "> cpystack = mystack" << std::endl;
	std::cout << std::endl;

	std::cout << "cpystack == mystack:" << (cpystack == mystack) << std::endl;
	cpystack.push(7);
	std::cout << "cpystack.push(7)" << std::endl;
	std::cout << "cpystack == mystack:" << (cpystack == mystack) << std::endl;
}
