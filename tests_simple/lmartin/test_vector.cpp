/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 20:39:11 by lmartin           #+#    #+#             */
/*   Updated: 2020/08/12 04:47:51 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <limits>
#include <iomanip>
#include <vector>
#include "utils.hpp"
#include "colors.h"
#include "vector.hpp"

template <class T>
void	error_diff(ft::vector<T> myv, std::vector<T> vector)
{
	std::cout << _RED << "ERROR - DIFF" << _END << std::endl;
	std::cout << std::setw(30) << "myv.empty(): " << myv.empty() << std::endl;
	std::cout << std::setw(30) << "vector.empty(): " << vector.empty() << std::endl;
	std::cout << std::setw(30) << "myv.size(): " << myv.size() << std::endl;
	std::cout << std::setw(30) << "vector.size(): " << vector.size() << std::endl;
	std::cout << std::setw(30) << "myv : ";
	printContainer(myv);
	std::cout << std::setw(30) << "vector : ";
	printContainer(vector);
}

template <class T>
void	compareVector(std::string function, ft::vector<T> myv, std::vector<T> vector)
{
	std::cout << std::setw(30) << function << ": ";
	if (myv.empty() != vector.empty())
		error_diff(myv, vector);
	else if (myv.size() != vector.size())
		error_diff(myv, vector);
	else
	{
		typename ft::vector<T>::iterator my_it;
		typename std::vector<T>::iterator	i;
		my_it = myv.begin();
		i = vector.begin();
		while (i != vector.end())
		{
			if (*i != *my_it)
			{
				error_diff(myv, vector);
				return ;
			}
			i++;
			my_it++;
		}
		std::cout << _GREEN << "OK " << _END;
		printContainer(myv);
	}
}

void		test_vector(void)
{
	std::cout << _WHITE << "# test_vector" << _END << std::endl;
	std::cout << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                          "<< _WHITE << "BASIC TESTS" << _YELLOW << "                                   */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	std::cout << std::endl;

	ft::vector<int>	myv;
	std::vector<int> vector;

	std::cout << "ft::vector<" << _PURPLE << "int" << _END << "> myv;" << std::endl;
	std::cout << "std::vector<" << _PURPLE << "int" << _END << "> vector;" << std::endl;

	std::cout << std::endl;
	std::cout << "myv.max_size(): " << myv.max_size() << std::endl;
	std::cout << "vector.max_size(): " << vector.max_size() << std::endl;
	std::cout << std::endl;

	compareVector("vector.empty()", myv, vector);
	compareVector("vector.size()", myv, vector);

	// myv.pop_back();
	//vector.pop_back(); --> if empty std::vector segfault

	// myv.front();
	//vector.front(); --> if empty std::vector segfault

	myv.back();
	vector.back();
	
	std::cout << _WHITE << "# testing out_of_range exception" << _END << std::endl;
	std::cout << "myv.at(0):" << std::endl;
	try
	{
		myv.at(0);
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception myv: " << e.what() << std::endl;
	}
	std::cout << "vector.at(0):" << std::endl;
	try
	{
		vector.at(0);
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception vector: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl;
	myv.reserve(0);
	vector.reserve(0);
	std::cout << "myv.reserve(0);" << std::endl;
	std::cout << "vector.reserve(0);" << std::endl;
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl;
	myv.reserve(1);
	vector.reserve(1);
	std::cout << "myv.reserve(1);" << std::endl;
	std::cout << "vector.reserve(1);" << std::endl;
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << _WHITE << "# testing reserve exception" << _END << std::endl;
	std::cout << "myv.reserve(" << std::numeric_limits<size_t>::max() << ");" << std::endl;
	try
	{
		myv.reserve(std::numeric_limits<size_t>::max());
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception myv: " << e.what() << std::endl;
	}
	std::cout << "vector.reserve(" << std::numeric_limits<size_t>::max() << ");" << std::endl;
	try
	{
		vector.reserve(std::numeric_limits<size_t>::max());
	}
	catch (std::exception &e)
	{
		std::cerr << "Catching exception vector: " << e.what() << std::endl;
	}
	std::cout << std::endl;

	myv.resize(8);
	vector.resize(8);
	compareVector("vector.resize(8)", myv, vector);
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl;

	myv.push_back(4);
	vector.push_back(4);
	compareVector("vector.push_back(4)", myv, vector);
	std::cout << _WHITE << "# std::vector resize more on push_back but both works" << _END << std::endl;
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl;
	myv.erase(myv.begin());
	vector.erase(vector.begin());
	compareVector("vector.erase(vector.begin())", myv, vector);

	std::cout << _WHITE << "# launching clear twice" << _END << std::endl;
	myv.clear();
	vector.clear();
	compareVector("vector.clear()", myv, vector);
	myv.clear();
	vector.clear();
	compareVector("vector.clear()", myv, vector);
	std::cout << "myv.capacity(): " << myv.capacity() << std::endl;
	std::cout << "vector.capacity(): " << vector.capacity() << std::endl;


	std::cout << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                        "<< _WHITE << "ADVANCED TESTS" << _YELLOW << "                                  */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	std::cout << std::endl;
	myv.assign((size_t)10, 8);
	vector.assign((size_t)10, 8);
	compareVector("vector.assign(10, 8)", myv, vector);
	myv.assign(myv.begin(), myv.begin() + 4); // wtf that works
	vector.assign(vector.begin(), vector.begin() + 4);
	compareVector("vector.assign(vector.begin(), vector.begin() + 4)", myv, vector);

	ft::vector<int> myv2;
	std::vector<int> vector2;
	std::cout << "ft::vector<" << _PURPLE << "int" << _END << "> myv2;" << std::endl;
	std::cout << "std::vector<" << _PURPLE << "int" << _END << "> vector2;" << std::endl;
	myv.swap(myv2);
	vector.swap(vector2);
	compareVector("vector.swap(vector2) - vector", myv, vector);
	compareVector("vector2", myv2, vector2);
	myv.swap(myv2);
	vector.swap(vector2);
	compareVector("vector.swap(vector2) - vector", myv, vector);
	compareVector("vector2", myv2, vector2);
	myv.erase(myv.begin() + 2);
	vector.erase(vector.begin() + 2);
	compareVector("vector.erase(this->begin() + 2", myv, vector);
	myv2 = myv;
	vector2 = vector;
	compareVector("vector2 = vector", myv2, vector2);
	myv.at(2) = 1;
	vector.at(2) = 1;
	compareVector("vector.at(2) = 1", myv, vector);
	myv[1] = 0;
	vector[1] = 0;
	compareVector("vector[1] = 0", myv, vector);

	std::cout << _WHITE << "# comparaisons tests" << _END << std::endl;
	std::cout << std::setw(30) << "myv < myv2: " << (myv < myv2) << std::endl;
	std::cout << std::setw(30) << "vector < vector2: " << (vector < vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv > myv2: " << (myv > myv2) << std::endl;
	std::cout << std::setw(30) << "vector > vector2: " << (vector > vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv == myv2: " << (myv == myv2) << std::endl;
	std::cout << std::setw(30) << "vector == vector2: " << (vector == vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv != myv2: " << (myv == myv2) << std::endl;
	std::cout << std::setw(30) << "vector != vector2: " << (vector == vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv <= myv2: " << (myv <= myv2) << std::endl;
	std::cout << std::setw(30) << "vector <= vector2: " << (vector <= vector2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(30) << "myv >= myv2: " << (myv >= myv2) << std::endl;
	std::cout << std::setw(30) << "vector >= vector2: " << (vector >= vector2) << std::endl;
}
