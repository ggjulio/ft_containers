/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:58:37 by lmartin           #+#    #+#             */
/*   Updated: 2020/08/12 04:48:21 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <map>
#include "colors.h"
#include "map.hpp"

template <class Container>
void	printMap(Container c)
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
		std::cout << _GREEN << i->first << _END << ":" << _GREEN << i->second << _END;
		i++;
		n++;
	}
	std::cout << _YELLOW << "]" << _END << std::endl;
	std::cout << std::endl;
}

template <class Key, class T>
void	error_diff(ft::map<Key, T> mymap, std::map<Key, T> map)
{
	std::cout << _RED << "ERROR - DIFF" << _END << std::endl;
	std::cout << std::setw(30) << "mymap.empty(): " << mymap.empty() << std::endl;
	std::cout << std::setw(30) << "map.empty(): " << map.empty() << std::endl;
	std::cout << std::setw(30) << "mymap.size(): " << mymap.size() << std::endl;
	std::cout << std::setw(30) << "map.size(): " << map.size() << std::endl;
	std::cout << std::setw(30) << "mymap : ";
	printMap(mymap);
	std::cout << std::setw(30) << "map : ";
	printMap(map);
}

template <class Key, class T>
void	compareMap(std::string function, ft::map<Key, T> mymap, std::map<Key, T> map)
{
	std::cout << std::setw(30) << function << ": ";
	if (mymap.empty() != map.empty())
		error_diff(mymap, map);
	else if (mymap.size() != map.size())
		error_diff(mymap, map);
	else
	{
		typename std::map<Key, T>::iterator	it = map.begin();
		size_t				i;

		i = 0;
		while (i < map.size())
		{
			typename ft::map<Key, T>::iterator it2 = mymap.find(it->first);
			if (it2 == mymap.end())
				error_diff(mymap, map);
			if (it2->first != it->first || it2->second != it->second)
				error_diff(mymap, map);
			it++;
			i++;
		}
		std::cout << _GREEN << "OK " << _END;
		printMap(mymap);
	}
}

void		test_map(void)
{
	std::cout << _WHITE << "# test_map" << _END << std::endl;
	std::cout << _YELLOW <<  "/* ********************************************************************** */" << std::endl;
	std::cout << "/*                          "<< _WHITE << "BASIC TESTS" << _YELLOW << "                                   */" << std::endl;
	std::cout << "/* ********************************************************************** */" << _END << std::endl;
	std::cout << std::endl;


	ft::map<std::string, int> mymap;
	std::map<std::string, int> map;


	std::cout << "ft::map<" << _PURPLE << "std::string" << _END << ", " << _PURPLE << "int" << _END << "> mymap;" << std::endl;
	std::cout << "std::map<" << _PURPLE << "std::string" << _END << ", " << _PURPLE << "int" << _END <<"> map;" << std::endl;

	std::cout << std::endl;
	std::cout << "mymap.max_size(): " << mymap.max_size() << std::endl;
	std::cout << "map.max_size(): " << map.max_size() << std::endl;
	std::cout << std::endl;

	compareMap("map.empty()", mymap, map);
	compareMap("map.size()", mymap, map);

	mymap.insert(ft::pair<std::string, int>("ft", 42));
	map.insert(std::pair<std::string, int>("ft", 42));
	compareMap("map.insert(\"ft\", 42)", mymap, map);

	mymap.insert(ft::pair<std::string, int>("one", 1));
	map.insert(std::pair<std::string, int>("one", 1));
	compareMap("map.insert(\"one\", 1)", mymap, map);


	std::cout << _WHITE << "# testing upper/lower_bound" << _END << std::endl;
	ft::map<std::string, int>::iterator mit;
	std::map<std::string, int>::iterator it;
	mit = mymap.lower_bound("aaa");
	it = map.lower_bound("aaa");
	std::cout << std::setw(40) << "mymap.lower_bound(\"aaa\"): " << mit->first << ":" << mit->second << std::endl;;
	std::cout << std::setw(40) << "map.lower_bound(\"aaa\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	mit = mymap.lower_bound("one");
	it = map.lower_bound("one");
	std::cout << std::setw(40) << "mymap.lower_bound(\"one\"): " << mit->first << ":" << mit->second << std::endl;;
	std::cout << std::setw(40) << "map.lower_bound(\"one\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	mit = mymap.lower_bound("oae");
	it = map.lower_bound("oae");
	std::cout << std::setw(40) << "mymap.lower_bound(\"oae\"): " << mit->first << ":" << mit->second << std::endl;;
	std::cout << std::setw(40) << "map.lower_bound(\"oae\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	mit = mymap.lower_bound("ft");
	it = map.lower_bound("ft");
	std::cout << std::setw(40) << "mymap.lower_bound(\"ft\"): " << mit->first << ":" << mit->second << std::endl;;
	std::cout << std::setw(40) << "map.lower_bound(\"ft\"): " << it->first << ":" << it->second << std::endl;
	std::cout << std::endl;
	mit = mymap.lower_bound("zzz");
	it = map.lower_bound("zzz");
	if (mit == mymap.end())
		std::cout << std::setw(40) << "mymap.lower_bound(\"zzz\"): mymap.end()" << std::endl;
	if (it == map.end())
		std::cout << std::setw(40) << "map.lower_bound(\"zzz\"): map.end()" << std::endl;
	std::cout << std::endl;
	mit = mymap.upper_bound("aaa");
	it = map.upper_bound("aaa");
	std::cout << std::setw(40) << "mymap.upper_bound(\"aaa\"): " << mit->first << ":" << mit->second << std::endl;;
	std::cout << std::setw(40) << "map.upper_bound(\"aaa\"): " << it->first << ":" << it->second << std::endl;;
	std::cout << std::endl;
	mit = mymap.upper_bound("oae");
	it = map.upper_bound("oae");
	std::cout << std::setw(40) << "mymap.upper_bound(\"oae\"): " << mit->first << ":" << mit->second << std::endl;;
	std::cout << std::setw(40) << "map.upper_bound(\"oae\"): " << it->first << ":" << it->second << std::endl;;
	std::cout << std::endl;
	mit = mymap.upper_bound("one");
	it = map.upper_bound("one");
	if (mit == mymap.end())
		std::cout << std::setw(40) << "mymap.upper_bound(\"one\"): mymap.end()" << std::endl;
	if (it == map.end())
		std::cout << std::setw(40) << "map.upper_bound(\"one\"): map.end()" << std::endl;
	std::cout << std::endl;
	mit = mymap.upper_bound("ft");
	it = map.upper_bound("ft");
	std::cout << std::setw(40) << "mymap.upper_bound(\"ft\"): " << mit->first << ":" << mit->second << std::endl;;
	std::cout << std::setw(40) << "map.upper_bound(\"ft\"): " << it->first << ":" << it->second << std::endl;;
	std::cout << std::endl;
	mit = mymap.upper_bound("zzz");
	it = map.upper_bound("zzz");
	if (mit == mymap.end())
		std::cout << std::setw(40) << "mymap.upper_bound(\"zzz\"): mymap.end()" << std::endl;
	if (it == map.end())
		std::cout << std::setw(40) << "map.upper_bound(\"zzz\"): map.end()" << std::endl;
	std::cout << std::endl;

	mymap.erase("undefined");
	map.erase("undefined");
	compareMap("map.erase(\"undefined\")", mymap, map);
	mymap.erase("ft");
	map.erase("ft");
	compareMap("map.erase(\"ft\")", mymap, map);
	std::cout << _WHITE << "# double clear" << _END << std::endl;
	mymap.clear();
	map.clear();
	compareMap("map.clear()", mymap, map);
	mymap.clear();
	map.clear();
	compareMap("map.clear()", mymap, map);
	mymap["lol"];
	map["lol"];
	compareMap("map[\"lol\"", mymap, map);
	mymap.insert(ft::pair<std::string, int>("xD", 123));
	map.insert(std::pair<std::string, int>("xD", 123));
	compareMap("map.insert(\"xD\", 123)", mymap, map);
	mymap.insert(mymap.end(), ft::pair<std::string, int>("uch", 442));
	map.insert(map.end(), std::pair<std::string, int>("uch", 442));
	compareMap("map.insert(map.end(), \"uch\", 442)", mymap, map);
	mymap.insert(mymap.begin(), ft::pair<std::string, int>("uch", 22));
	map.insert(map.begin(), std::pair<std::string, int>("uch", 22));
	compareMap("map.insert(map.begin(), \"uch\", 22)", mymap, map);
	mymap.insert(mymap.end(), ft::pair<std::string, int>("uch", 23));
	map.insert(map.end(), std::pair<std::string, int>("uch", 23));
	compareMap("map.insert(map.end(), \"uch\", 23)", mymap, map);
	mymap.insert(ft::pair<std::string, int>("uch", 23));
	map.insert(std::pair<std::string, int>("uch", 23));
	compareMap("map.insert(\"uch\", 23)", mymap, map);
	mymap["lol"] = 8;
	map["lol"] = 8;
	compareMap("map[\"lol\"] = 8", mymap, map);


	ft::map<std::string, int> mymap2;
	std::map<std::string, int> map2;

	std::cout << "ft::map<" << _PURPLE << "std::string" << _END << ", " << _PURPLE << "int" << _END << "> mymap2;" << std::endl;
	std::cout << "std::map<" << _PURPLE << "std::string" << _END << ", " << _PURPLE << "int" << _END <<"> map2;" << std::endl;

	swap(mymap, mymap2);
	swap(map, map2);
	compareMap("swap(map, map2)", mymap, map);
	compareMap("map 2", mymap2, map2);

	mymap = mymap2;
	map = map2;
	compareMap("map = map2", mymap, map);

	std::cout << std::setw(40) << "mymap == mymap2: " << (mymap == mymap2) << std::endl;
	std::cout << std::setw(40) << "map == map2: " << (map == map2) << std::endl;
	std::cout << std::endl;

	mymap.clear();
	map.clear();
	compareMap("map.clear()", mymap, map);

	mymap["satan"] = 666;
	map["satan"] = 666;
	compareMap("map[\"satan\"] = 666", mymap, map);
	std::cout << std::setw(40) << "mymap == mymap2: " << (mymap == mymap2) << std::endl;
	std::cout << std::setw(40) << "map == map2: " << (map == map2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap <= mymap2: " << (mymap <= mymap2) << std::endl;
	std::cout << std::setw(40) << "map <= map2: " << (map <= map2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap >= mymap2: " << (mymap >= mymap2) << std::endl;
	std::cout << std::setw(40) << "map >= map2: " << (map >= map2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap > mymap2: " << (mymap > mymap2) << std::endl;
	std::cout << std::setw(40) << "map > map2: " << (map > map2) << std::endl;
	std::cout << std::endl;
	std::cout << std::setw(40) << "mymap < mymap2: " << (mymap > mymap2) << std::endl;
	std::cout << std::setw(40) << "map < map2: " << (map > map2) << std::endl;
	std::cout << std::endl;


	// TO SHOW AVL TREE ?
	ft::map<int, int> mymap3;
	mymap3.insert(ft::map<int, int>::value_type(1, 1));
	mymap3.insert(ft::map<int, int>::value_type(4, 1));
	mymap3.insert(ft::map<int, int>::value_type(3, 1));
	mymap3.insert(ft::map<int, int>::value_type(5, 1));
	mymap3.insert(ft::map<int, int>::value_type(9, 1));
	mymap3.insert(ft::map<int, int>::value_type(2, 1));
	mymap3.insert(ft::map<int, int>::value_type(8, 199));
	mymap3.insert(ft::map<int, int>::value_type(7, 1));
	mymap3.insert(ft::map<int, int>::value_type(6, 1));
	mymap3.insert(ft::map<int, int>::value_type(6, 1));
	mymap3.insert(ft::map<int, int>::value_type(0, 1));

	// mymap3.print(); wtf ?

	mymap3.erase(6);
	mymap3.erase(7);
	mymap3.erase(7);
	mymap3.erase(3);
	mymap3.erase(2);

	printf("\nerase 6 7 3 2\n");
	// mymap3.print();

	printf("\nerase 8\n");
	mymap3.erase(8);
	// mymap3.print();

	printf("\nerase 1\n");
	mymap3.erase(1);
	// mymap3.print();

	printf("\nerase 5\n");
	mymap3.erase(5);
	// mymap3.print();

	printf("\nclear\n");
	mymap3.clear();
	// mymap3.print();
}
