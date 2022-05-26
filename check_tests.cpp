/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:46:30 by bchelste          #+#    #+#             */
/*   Updated: 2022/02/19 20:39:48 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iterator>
#include <list>
#include <map>
#include <stack>
#include <set>
#include <iostream>
#include <fstream>
#include <exception>
#include <ctime>
#include <utility>
#include <iomanip>

#include "iterators.hpp"
#include "reimplement.hpp"
#include "rb_tree.hpp"
#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "set.hpp"

#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define DFLT "\033[0m"

// utils for output:

template<typename T_VCTR>
void print_vector(std::ostream &stream, T_VCTR const &vctr)
{
	stream << "size = " << vctr.size() << std::endl;
	stream << "capacity = " << vctr.capacity() << std::endl;
	typename T_VCTR::const_iterator it = vctr.begin();
	stream << "vector: ";
	while (it != vctr.end())
	{
		stream << *it << " ";
		++it;
	}
	stream << std::endl;
	stream << "-----\n" << std::endl;
}

template <typename T_MAP>
void	ft_print_map(T_MAP const &mp, std::ostream &stream)
{
	stream << "size: " << mp.size() << std::endl;
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		stream << std::endl << "Content is:" << std::endl;
		while (it != ite)
		{
			stream << "- " << "key: " << it->first << " | value: " << it->second << std::endl;
			++it;
		}
	stream << "-----------------------------------------" << std::endl;
}

template <typename T_SET>
void	ft_print_set(T_SET const &set, std::ostream &stream)
{
	stream << "size: " << set.size() << std::endl;
		typename T_SET::const_iterator it = set.begin(), ite = set.end();
		stream << std::endl << "Content is:" << std::endl;
		while (it != ite)
		{
			stream << "- " << "key: " << *it << " |" << std::endl;
			++it;
		}
	stream << "-----------------------------------------" << std::endl;
}

// tests:

void ft_vctr_out(std::ostream &stream)
{
	//create vector output:

	ft::vector<int> 	tmp_1;
	ft::vector<int>		tmp_2(4, 8);
	ft::vector<int>		tmp_3(tmp_2);
	ft::vector<int>		tmp_4(tmp_2.begin(), tmp_2.end());
	ft::vector<int>		tmp_5(9, 1);
	ft::vector<int>		tmp_6(2, 88);
	
	stream << "----------vector_tests----------" << std::endl;
	
	stream << "--------------" << std::endl;
	stream << "CONSTRUCTORS: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_1(empty): " << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_2(4, 8): " << std::endl;;
	print_vector(stream, tmp_2);
	stream << "tmp_3(tmp_2): " << std::endl;;
	print_vector(stream, tmp_3);
	stream << "tmp_4(tmp_2.begin(), tmp_2.end()): " << std::endl;;
	print_vector(stream, tmp_4);
	
	stream << "--------------" << std::endl;
	stream << "OPERATOR = " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_5(9, 1):" << std::endl;
	print_vector(stream, tmp_5);
	stream << "tmp_6(2, 88):" << std::endl;
	print_vector(stream, tmp_6);
	tmp_6 = tmp_5;
	stream << "tmp_6 = tmp_5;" << std::endl;
	stream << "tmp_6: " << std::endl;
	print_vector(stream, tmp_6);
	tmp_5 = tmp_4;
	stream << "tmp_5 = tmp_4;" << std::endl;
	stream << "tmp_5: " << std::endl;
	print_vector(stream, tmp_5);
	
	stream << "--------------" << std::endl;
	stream << "POP_BACK AND PUSH_BACK: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_2: " << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.push_back(15);
	stream << "tmp_2.push_back(15)" << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.push_back(16);
	tmp_2.push_back(23);
	tmp_2.push_back(42);
	tmp_2.push_back(69);
	tmp_2.push_back(-70);
	tmp_2.push_back(-45);
	stream << "tmp_2.push_back 16 23 42 69 -70 -45" << std::endl;
	print_vector(stream, tmp_2);
	stream << "--\n" << std::endl;
	stream << "tmp_6: " << std::endl;
	print_vector(stream, tmp_6);
	tmp_6.pop_back();
	tmp_6.pop_back();
	stream << "tmp_6.pop_back 2 times:" << std::endl;
	print_vector(stream, tmp_6);
	
	stream << "--------------" << std::endl;
	stream << "CAPACITY: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_4: " << std::endl;
	print_vector(stream, tmp_4);
	tmp_4.resize(10,44);
	stream << "tmp_4 [after tmp_4.resize(10, 44)] : " << std::endl;
	print_vector(stream, tmp_4);
	stream << "tmp_2: " << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.resize(1);
	stream << "tmp_2 [after tmp_2.resize(1)] : " << std::endl;
	print_vector(stream, tmp_2);
	stream << "tmp_1.empty()= " << tmp_1.empty() << std::endl;
	stream << "tmp_2.empty()= " << tmp_2.empty() << std::endl;
	stream << "tmp_6.empty()= " << tmp_6.empty() << std::endl;
	stream << std::endl;
	stream << "tmp_1: " << std::endl;
	print_vector(stream, tmp_1);
	tmp_1.reserve(10);
	stream << "tmp_1.reserve(10) " << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_5: " << std::endl;
	print_vector(stream, tmp_5);
	tmp_5.reserve(1);
	stream << "tmp_5.reserve(1) " << std::endl;
	print_vector(stream, tmp_5);
	
	stream << "--------------" << std::endl;
	stream << "ITERATORS: " << std::endl;
	stream << "--------------\n" << std::endl;
	tmp_4.push_back(9);
	stream << "tmp_4: " << std::endl;
	print_vector(stream, tmp_4);
	stream << "tmp_4.begin(): " << (*(tmp_4.begin())) << std::endl;
	std::vector<int>::difference_type nbr = 1;
	stream << "tmp_4.end() - 1: " << (*(tmp_4.end() - nbr)) << std::endl;
	stream << "tmp_4.rbegin(): " << (*(tmp_4.rbegin())) << std::endl;
	stream << "tmp_4.rend() - 1: " << (*(tmp_4.rend() - nbr)) << std::endl;
	
	stream << "--------------" << std::endl;
	stream << "ELEMENT ACCESS: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_4: " << std::endl;
	stream << "tmp_4[5]: " << (tmp_4[5]) << std::endl;
	stream << "tmp_4.at(3): " << tmp_4.at(3) << std::endl;
	stream << "tmp_4.front(): " << tmp_4.front() << std::endl;
	stream << "tmp_4.back(): " << tmp_4.back() << std::endl;
	
	stream << "--------------" << std::endl;
	stream << "MODIFIERS: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_1: " << std::endl;
	print_vector(stream, tmp_1);
	tmp_1.assign(17, 5);
	stream << "tmp_1.assign(17, 5) " << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_2: " << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.assign(tmp_4.begin(), tmp_4.end());
	stream << "tmp_2.assign(tmp_4.begin(), tmp_4.end()) " << std::endl;
	print_vector(stream, tmp_2);
	stream << "tmp_2.clear()" << std::endl;
	tmp_2.clear();
	print_vector(stream, tmp_2);
	stream << "tmp_2.insert(tmp_2.begin(), 2)" << std::endl;
	tmp_2.insert(tmp_2.begin(), 2);
	print_vector(stream, tmp_2);
	stream << "tmp_2.insert((tmp_2.begin() + nbr), 5, 7)" << std::endl;
	tmp_2.insert((tmp_2.begin() + nbr), 5, 7);
	print_vector(stream, tmp_2);
	tmp_1.push_back(99);
	stream << "tmp_2.insert((tmp_2.begin() + (nbr*2)), tmp_1.begin(), tmp_1.end())" << std::endl;
	tmp_2.insert((tmp_2.begin() + nbr + nbr), tmp_1.begin(), tmp_1.end());
	print_vector(stream, tmp_2);
	stream << "tmp_2.erase(tmp_2.begin() + 6 , (tmp_2.begin() + nbr(12))))" << std::endl;
	nbr += 5;
	tmp_2.erase((tmp_2.begin() + nbr), (tmp_2.begin() + nbr + nbr));
	print_vector(stream, tmp_2);
	stream << "tmp_2.erase(tmp_2.end() - 1)" << std::endl;
	nbr = 1;
	tmp_2.erase(tmp_2.end() - nbr);
	print_vector(stream, tmp_2);
	stream << "tmp_2.erase(tmp_2.begin()) two times" << std::endl;
	tmp_2.erase(tmp_2.begin());
	tmp_2.erase(tmp_2.begin());
	print_vector(stream, tmp_2);
	
	stream << "\ncheck swap: \n" << std::endl;
	stream << "tmp_4:" << std::endl;
	print_vector(stream, tmp_4);
	stream << "tmp_2:" << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.swap(tmp_4);
	stream << "after swap: \n" << std::endl;
	stream << "tmp_4:" << std::endl;
	print_vector(stream, tmp_4);
	stream << "tmp_2:" << std::endl;
	print_vector(stream, tmp_2);
	
	stream << "\ncheck swap non-member: \n" << std::endl;
	stream << "tmp_1:" << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_2:" << std::endl;
	print_vector(stream, tmp_2);
	stream << "after swap: \n" << std::endl;
	swap(tmp_1, tmp_2);
	stream << "tmp_1:" << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_2:" << std::endl;
	print_vector(stream, tmp_2);
	
	tmp_1.clear();
	tmp_1.assign(5, 22);
	tmp_1.push_back(1);
	tmp_2.assign(5, 22);
	tmp_3.assign(5, 22);
	
	stream << "compare: " << std::endl;
	stream << (tmp_1 < tmp_2) << std::endl;
	stream << (tmp_1 > tmp_2) << std::endl;
	stream << (tmp_1 >= tmp_2) << std::endl;
	stream << (tmp_3 >= tmp_2) << std::endl;
	stream << (tmp_3 == tmp_2) << std::endl;
	stream << (tmp_1 == tmp_2) << std::endl;
	stream << (tmp_3 != tmp_2) << std::endl;
	stream << "************" << std::endl;
	return;
}
	
void std_vctr_out(std::ostream &stream)
{
	//create vector output:
		
	std::vector<int> 		tmp_1;
	std::vector<int>		tmp_2(4, 8);
	std::vector<int>		tmp_3(tmp_2);
	std::vector<int>		tmp_4(tmp_2.begin(), tmp_2.end());
	std::vector<int>		tmp_5(9, 1);
	std::vector<int>		tmp_6(2, 88);
	
	stream << "----------vector_tests----------" << std::endl;
	
	stream << "--------------" << std::endl;
	stream << "CONSTRUCTORS: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_1(empty): " << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_2(4, 8): " << std::endl;;
	print_vector(stream, tmp_2);
	stream << "tmp_3(tmp_2): " << std::endl;;
	print_vector(stream, tmp_3);
	stream << "tmp_4(tmp_2.begin(), tmp_2.end()): " << std::endl;;
	print_vector(stream, tmp_4);
	
	stream << "--------------" << std::endl;
	stream << "OPERATOR = " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_5(9, 1):" << std::endl;
	print_vector(stream, tmp_5);
	stream << "tmp_6(2, 88):" << std::endl;
	print_vector(stream, tmp_6);
	tmp_6 = tmp_5;
	stream << "tmp_6 = tmp_5;" << std::endl;
	stream << "tmp_6: " << std::endl;
	print_vector(stream, tmp_6);
	tmp_5 = tmp_4;
	stream << "tmp_5 = tmp_4;" << std::endl;
	stream << "tmp_5: " << std::endl;
	print_vector(stream, tmp_5);
	
	stream << "--------------" << std::endl;
	stream << "POP_BACK AND PUSH_BACK: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_2: " << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.push_back(15);
	stream << "tmp_2.push_back(15)" << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.push_back(16);
	tmp_2.push_back(23);
	tmp_2.push_back(42);
	tmp_2.push_back(69);
	tmp_2.push_back(-70);
	tmp_2.push_back(-45);
	stream << "tmp_2.push_back 16 23 42 69 -70 -45" << std::endl;
	print_vector(stream, tmp_2);
	stream << "--\n" << std::endl;
	stream << "tmp_6: " << std::endl;
	print_vector(stream, tmp_6);
	tmp_6.pop_back();
	tmp_6.pop_back();
	stream << "tmp_6.pop_back 2 times:" << std::endl;
	print_vector(stream, tmp_6);
	
	stream << "--------------" << std::endl;
	stream << "CAPACITY: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_4: " << std::endl;
	print_vector(stream, tmp_4);
	tmp_4.resize(10,44);
	stream << "tmp_4 [after tmp_4.resize(10, 44)] : " << std::endl;
	print_vector(stream, tmp_4);
	stream << "tmp_2: " << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.resize(1);
	stream << "tmp_2 [after tmp_2.resize(1)] : " << std::endl;
	print_vector(stream, tmp_2);
	stream << "tmp_1.empty()= " << tmp_1.empty() << std::endl;
	stream << "tmp_2.empty()= " << tmp_2.empty() << std::endl;
	stream << "tmp_6.empty()= " << tmp_6.empty() << std::endl;
	stream << std::endl;
	stream << "tmp_1: " << std::endl;
	print_vector(stream, tmp_1);
	tmp_1.reserve(10);
	stream << "tmp_1.reserve(10) " << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_5: " << std::endl;
	print_vector(stream, tmp_5);
	tmp_5.reserve(1);
	stream << "tmp_5.reserve(1) " << std::endl;
	print_vector(stream, tmp_5);
	
	stream << "--------------" << std::endl;
	stream << "ITERATORS: " << std::endl;
	stream << "--------------\n" << std::endl;
	tmp_4.push_back(9);
	stream << "tmp_4: " << std::endl;
	print_vector(stream, tmp_4);
	stream << "tmp_4.begin(): " << (*(tmp_4.begin())) << std::endl;
	std::vector<int>::difference_type nbr = 1;
	stream << "tmp_4.end() - 1: " << (*(tmp_4.end() - nbr)) << std::endl;
	stream << "tmp_4.rbegin(): " << (*(tmp_4.rbegin())) << std::endl;
	stream << "tmp_4.rend() - 1: " << (*(tmp_4.rend() - nbr)) << std::endl;
	
	stream << "--------------" << std::endl;
	stream << "ELEMENT ACCESS: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_4: " << std::endl;
	stream << "tmp_4[5]: " << (tmp_4[5]) << std::endl;
	stream << "tmp_4.at(3): " << tmp_4.at(3) << std::endl;
	stream << "tmp_4.front(): " << tmp_4.front() << std::endl;
	stream << "tmp_4.back(): " << tmp_4.back() << std::endl;
	
	stream << "--------------" << std::endl;
	stream << "MODIFIERS: " << std::endl;
	stream << "--------------\n" << std::endl;
	stream << "tmp_1: " << std::endl;
	print_vector(stream, tmp_1);
	tmp_1.assign(17, 5);
	stream << "tmp_1.assign(17, 5) " << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_2: " << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.assign(tmp_4.begin(), tmp_4.end());
	stream << "tmp_2.assign(tmp_4.begin(), tmp_4.end()) " << std::endl;
	print_vector(stream, tmp_2);
	stream << "tmp_2.clear()" << std::endl;
	tmp_2.clear();
	print_vector(stream, tmp_2);
	stream << "tmp_2.insert(tmp_2.begin(), 2)" << std::endl;
	tmp_2.insert(tmp_2.begin(), 2);
	print_vector(stream, tmp_2);
	stream << "tmp_2.insert((tmp_2.begin() + nbr), 5, 7)" << std::endl;
	tmp_2.insert((tmp_2.begin() + nbr), 5, 7);
	print_vector(stream, tmp_2);
	tmp_1.push_back(99);
	stream << "tmp_2.insert((tmp_2.begin() + (nbr*2)), tmp_1.begin(), tmp_1.end())" << std::endl;
	tmp_2.insert((tmp_2.begin() + nbr + nbr), tmp_1.begin(), tmp_1.end());
	print_vector(stream, tmp_2);
	stream << "tmp_2.erase(tmp_2.begin() + 6 , (tmp_2.begin() + nbr(12))))" << std::endl;
	nbr += 5;
	tmp_2.erase((tmp_2.begin() + nbr), (tmp_2.begin() + nbr + nbr));
	print_vector(stream, tmp_2);
	stream << "tmp_2.erase(tmp_2.end() - 1)" << std::endl;
	nbr = 1;
	tmp_2.erase(tmp_2.end() - nbr);
	print_vector(stream, tmp_2);
	stream << "tmp_2.erase(tmp_2.begin()) two times" << std::endl;
	tmp_2.erase(tmp_2.begin());
	tmp_2.erase(tmp_2.begin());
	print_vector(stream, tmp_2);
	
	stream << "\ncheck swap: \n" << std::endl;
	stream << "tmp_4:" << std::endl;
	print_vector(stream, tmp_4);
	stream << "tmp_2:" << std::endl;
	print_vector(stream, tmp_2);
	tmp_2.swap(tmp_4);
	stream << "after swap: \n" << std::endl;
	stream << "tmp_4:" << std::endl;
	print_vector(stream, tmp_4);
	stream << "tmp_2:" << std::endl;
	print_vector(stream, tmp_2);
	
	stream << "\ncheck swap non-member: \n" << std::endl;
	stream << "tmp_1:" << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_2:" << std::endl;
	print_vector(stream, tmp_2);
	stream << "after swap: \n" << std::endl;
	swap(tmp_1, tmp_2);
	stream << "tmp_1:" << std::endl;
	print_vector(stream, tmp_1);
	stream << "tmp_2:" << std::endl;
	print_vector(stream, tmp_2);
	
	tmp_1.clear();
	tmp_1.assign(5, 22);
	tmp_1.push_back(1);
	tmp_2.assign(5, 22);
	tmp_3.assign(5, 22);
	
	stream << "compare: " << std::endl;
	stream << (tmp_1 < tmp_2) << std::endl;
	stream << (tmp_1 > tmp_2) << std::endl;
	stream << (tmp_1 >= tmp_2) << std::endl;
	stream << (tmp_3 >= tmp_2) << std::endl;
	stream << (tmp_3 == tmp_2) << std::endl;
	stream << (tmp_1 == tmp_2) << std::endl;
	stream << (tmp_3 != tmp_2) << std::endl;
	stream << "************" << std::endl;
	return;
}

void ft_stck_out(std::ostream &stream)
{
	stream << "----------stack_tests----------" << std::endl;
	stream << "constructors: " << std::endl;
	ft::vector<int> test_vctr(5, 88);
	ft::stack<char> tmp_1;
	ft::stack<int, ft::vector<int> >tmp_2(test_vctr);
	stream << "stack #1: tmp_1 (empty) size = " << tmp_1.size() << std::endl;
	stream << "stack #2: tmp_2 (5, 88) size = " << tmp_2.size() << std::endl;
	stream <<  "----------------------------\n"  << std::endl;

	stream  << "member functions: " << std::endl;
	
	stream <<  "empty: " <<  std::endl;
	stream << "tmp_1 empty: " << tmp_1.empty() << std::endl;
	stream << "tmp_2 empty: " << tmp_1.empty() << std::endl;
	stream  << "----------------------------\n" << std::endl;

	stream << "push: " <<  std::endl;
	stream << "tmp_1: size before push = " << tmp_1.size() << std::endl;
	tmp_1.push('l');
	tmp_1.push('o');
	tmp_1.push('l');
	stream << "tmp_1: size after push ('l', 'o' and 'l' were added)= " << tmp_1.size() << std::endl;
	tmp_2.push(77);
	stream << "tmp_2: size after push (77 was added)= " << tmp_2.size() << std::endl;
	stream <<  "----------------------------\n" << std::endl;

	stream << "top and pop: " << std::endl;
	stream << "tmp_1 top element: " << tmp_1.top() << std::endl;
	stream << "tmp_2 top element: " << tmp_2.top() << std::endl;
	tmp_1.pop();
	tmp_2.pop();
	stream << "tmp_1 top element after tmp_1.pop(): " << tmp_1.top() << " and size = " << tmp_1.size() << std::endl;
	stream << "tmp_2 top element after tmp_2.pop(): " << tmp_2.top() << " and size = " << tmp_1.size() << std::endl;
	stream << "----------------------------\n" << std::endl;
	return ;
}

void std_stck_out(std::ostream &stream)
{
	stream << "----------stack_tests----------" << std::endl;
	stream << "constructors: " << std::endl;
	std::vector<int> test_vctr(5, 88);
	std::stack<char> tmp_1;
	std::stack<int, std::vector<int> >tmp_2(test_vctr);
	stream << "stack #1: tmp_1 (empty) size = " << tmp_1.size() << std::endl;
	stream << "stack #2: tmp_2 (5, 88) size = " << tmp_2.size() << std::endl;
	stream <<  "----------------------------\n"  << std::endl;

	stream  << "member functions: " << std::endl;
	
	stream <<  "empty: " <<  std::endl;
	stream << "tmp_1 empty: " << tmp_1.empty() << std::endl;
	stream << "tmp_2 empty: " << tmp_1.empty() << std::endl;
	stream  << "----------------------------\n" << std::endl;

	stream << "push: " <<  std::endl;
	stream << "tmp_1: size before push = " << tmp_1.size() << std::endl;
	tmp_1.push('l');
	tmp_1.push('o');
	tmp_1.push('l');
	stream << "tmp_1: size after push ('l', 'o' and 'l' were added)= " << tmp_1.size() << std::endl;
	tmp_2.push(77);
	stream << "tmp_2: size after push (77 was added)= " << tmp_2.size() << std::endl;
	stream <<  "----------------------------\n" << std::endl;

	stream << "top and pop: " << std::endl;
	stream << "tmp_1 top element: " << tmp_1.top() << std::endl;
	stream << "tmp_2 top element: " << tmp_2.top() << std::endl;
	tmp_1.pop();
	tmp_2.pop();
	stream << "tmp_1 top element after tmp_1.pop(): " << tmp_1.top() << " and size = " << tmp_1.size() << std::endl;
	stream << "tmp_2 top element after tmp_2.pop(): " << tmp_2.top() << " and size = " << tmp_1.size() << std::endl;
	stream << "----------------------------\n" << std::endl;
	return ;
}

void ft_map_out(std::ostream &stream)
{
	std::list<ft::pair<int, std::string > > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(ft::make_pair(i, std::string((lst_size - i), i + 65)));

	stream << "----------map_tests----------" << std::endl;

	ft::map<int, std::string > map1;

	ft::map<int, std::string > map2(lst.begin(), lst.end());
	
	ft::map<int, std::string >::value_type tmp(42, "lol");
	ft::map<int, std::string >::value_type tmp2(21, "lplplplplplp");
	ft::map<int, std::string >::iterator it;
	ft::map<int, std::string >::iterator it2;
	ft::map<int, std::string >::reverse_iterator itr;

	
	stream << "is empty map1: " << map1.empty() << std::endl;
	stream << "is empty map2: " << map2.empty() << std::endl;
	
	map1 = map2;
	stream << "map1 after map1 = map2: " << std::endl;
	
	ft_print_map(map1, stream);
	stream << "map2: " << map1.empty() << std::endl;
	ft_print_map(map2, stream);

	stream << "map1 after insert key 42 and then 21: " << std::endl;
	map1.insert(tmp);
	map1.insert(tmp2);
	ft_print_map(map1, stream);
	
	stream << "map2 after erase key 8 and then key 0: " << std::endl;
	map2.erase(8);
	map2.erase(0);
	ft_print_map(map2, stream);
	
	stream << "map1 after erase from begin to ++ ++ begin " << std::endl;
	map1.erase(map1.begin(), (++(++map1.begin())));
	ft_print_map(map1, stream);
	
	stream << "map1 after erase another erase with iterators:" << std::endl;
	map1.erase((++(++map1.begin())), --map1.end());
	ft_print_map(map1, stream);
	
	map1[10] = "privet 10";
	map1[9] = "poka";
	map1[333] = "tr tr tr";
	map1[42] = "yyyyyyy";
	stream << "map1 after [10], [9], [333], [42] :" << std::endl;
	ft_print_map(map1, stream);
	
	it = map1.end(); --it;
	stream << "map1 begin() key:" << map1.begin()->first << std::endl;
	stream << "map1 --end() key:" << it->first << std::endl;
	
	stream << "map1 rbegin() key:" << map1.rbegin()->first << std::endl;
	itr = map1.rend(); --itr;
	stream << "map1 rend() key:" << itr->first << std::endl;

	stream << "map1 lower_bound(10)->second: ";
	stream << map1.lower_bound(10)->second << std::endl;
	stream << "map1 lower_bound(8)->second: ";
	stream << map1.lower_bound(8)->second << std::endl;

	stream << "map1 upper_bound(42)->second: ";
	stream << map1.upper_bound(42)->second << std::endl;
	stream << "map1 upper_bound(43)->second: ";
	stream << map1.upper_bound(43)->second << std::endl;

	stream << "check equal_range in map1: " << std::endl;
	ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> eq_it = map1.equal_range(7);
	stream << "map1.equal_range(7)" << std::endl;
	 if (eq_it.first != map1.end())
            stream << "Key: " << eq_it.first->first << " | Value: " << eq_it.first->second << std::endl;
        else
            stream << "Hasn't find lower_bound 7" << std::endl;
        if (eq_it.second != map1.end())
            stream << "Key: " << eq_it.second->first << " | Value: " << eq_it.second->second << std::endl;
        else
           stream << "Hasn't find upper_bound 7" << std::endl;
	eq_it = map1.equal_range(335);
	stream << "map1.equal_range(335)" << std::endl;
	 if (eq_it.first != map1.end())
            stream << "Key: " << eq_it.first->first << " | Value: " << eq_it.first->second << std::endl;
        else
            stream << "Hasn't find lower_bound 335" << std::endl;
        if (eq_it.second != map1.end())
            stream << "Key: " << eq_it.second->first << " | Value: " << eq_it.second->second << std::endl;
        else
           stream << "Hasn't find upper_bound 335" << std::endl;
	stream << std::endl;
	stream << "map1:" << std::endl; ft_print_map(map1, stream);
	stream << "map2:" << std::endl; ft_print_map(map2, stream);
	map1.swap(map2);
	stream << "swap map1 and map2:\n ";
	stream << "map1:" << std::endl; ft_print_map(map1, stream);
	stream << "map2:" << std::endl; ft_print_map(map2, stream);

	it = map1.find(7);
	stream << "map1.find(7) second elem->: " << it->second << std::endl;
	
	stream << std::endl;
	stream << "\nmap1.count(9):        " << map1.count(9) << std::endl;
	stream << "and map1.count(9999): " << map1.count(9999) << std::endl;
	stream << std::endl;
	
	it = map1.begin(); ++it;
	it2 = map1.end(); -- it2; --it2;
	bool res1 = map1.key_comp()(map1.begin()->first, it->first);
	bool res2 = map1.value_comp()(*it2, *it);
	stream << std::endl;
	stream << "key_comp: " << res1 << std::endl;
	stream << "value_comp: " << res2 << std::endl;

	map1.clear();
	map2.clear();
	stream << "\n\nmaps after clear: \n";
	ft_print_map(map1, stream);
	ft_print_map(map2, stream);

	return ;

}

void std_map_out(std::ostream &stream)
{
	std::list<std::pair<int, std::string > > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::make_pair(i, std::string((lst_size - i), i + 65)));

		
	stream << "----------map_tests----------" << std::endl;

	std::map<int, std::string > map1;
	std::map<int, std::string > map2(lst.begin(), lst.end());
	std::map<int, std::string >::value_type tmp(42, "lol");
	std::map<int, std::string >::value_type tmp2(21, "lplplplplplp");
	std::map<int, std::string >::iterator it;
	std::map<int, std::string >::iterator it2;
	std::map<int, std::string >::reverse_iterator itr;

	
	stream << "is empty map1: " << map1.empty() << std::endl;
	stream << "is empty map2: " << map2.empty() << std::endl;
	map1 = map2;
	stream << "map1 after map1 = map2: " << std::endl;
	ft_print_map(map1, stream);
	stream << "map2: " << map1.empty() << std::endl;
	ft_print_map(map2, stream);
	stream << "map1 after insert key 42 and then 21: " << std::endl;
	map1.insert(tmp);
	map1.insert(tmp2);
	ft_print_map(map1, stream);
	stream << "map2 after erase key 8 and then key 0: " << std::endl;
	map2.erase(8);
	map2.erase(0);
	ft_print_map(map2, stream);
	stream << "map1 after erase from begin to ++ ++ begin " << std::endl;
	map1.erase(map1.begin(), (++(++map1.begin())));
	ft_print_map(map1, stream);
	stream << "map1 after erase another erase with iterators:" << std::endl;
	map1.erase((++(++map1.begin())), --map1.end());
	ft_print_map(map1, stream);
	map1[10] = "privet 10";
	map1[9] = "poka";
	map1[333] = "tr tr tr";
	map1[42] = "yyyyyyy";
	stream << "map1 after [10], [9], [333], [42] :" << std::endl;
	ft_print_map(map1, stream);
	
	it = map1.end(); --it;
	stream << "map1 begin() key:" << map1.begin()->first << std::endl;
	stream << "map1 --end() key:" << it->first << std::endl;
	
	stream << "map1 rbegin() key:" << map1.rbegin()->first << std::endl;
	itr = map1.rend(); --itr;
	stream << "map1 rend() key:" << itr->first << std::endl;

	stream << "map1 lower_bound(10)->second: ";
	stream << map1.lower_bound(10)->second << std::endl;
	stream << "map1 lower_bound(8)->second: ";
	stream << map1.lower_bound(8)->second << std::endl;

	stream << "map1 upper_bound(42)->second: ";
	stream << map1.upper_bound(42)->second << std::endl;
	stream << "map1 upper_bound(43)->second: ";
	stream << map1.upper_bound(43)->second << std::endl;

	stream << "check equal_range in map1: " << std::endl;
	std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> eq_it = map1.equal_range(7);
	stream << "map1.equal_range(7)" << std::endl;
	 if (eq_it.first != map1.end())
            stream << "Key: " << eq_it.first->first << " | Value: " << eq_it.first->second << std::endl;
        else
            stream << "Hasn't find lower_bound 7" << std::endl;
        if (eq_it.second != map1.end())
            stream << "Key: " << eq_it.second->first << " | Value: " << eq_it.second->second << std::endl;
        else
           stream << "Hasn't find upper_bound 7" << std::endl;
	eq_it = map1.equal_range(335);
	stream << "map1.equal_range(335)" << std::endl;
	 if (eq_it.first != map1.end())
            stream << "Key: " << eq_it.first->first << " | Value: " << eq_it.first->second << std::endl;
        else
            stream << "Hasn't find lower_bound 335" << std::endl;
        if (eq_it.second != map1.end())
            stream << "Key: " << eq_it.second->first << " | Value: " << eq_it.second->second << std::endl;
        else
           stream << "Hasn't find upper_bound 335" << std::endl;
	stream << std::endl;

	stream << "map1:" << std::endl; ft_print_map(map1, stream);
	stream << "map2:" << std::endl; ft_print_map(map2, stream);
	map1.swap(map2);
	stream << "swap map1 and map2:\n ";
	stream << "map1:" << std::endl; ft_print_map(map1, stream);
	stream << "map2:" << std::endl; ft_print_map(map2, stream);

	it = map1.find(7);
	stream << "map1.find(7) second elem->: " << it->second << std::endl;
	
	stream << std::endl;
	stream << "\nmap1.count(9):        " << map1.count(9) << std::endl;
	stream << "and map1.count(9999): " << map1.count(9999) << std::endl;
	stream << std::endl;
	
	it = map1.begin(); ++it;
	it2 = map1.end(); -- it2; --it2;
	bool res1 = map1.key_comp()(map1.begin()->first, it->first);
	bool res2 = map1.value_comp()(*it2, *it);
	stream << std::endl;
	stream << "key_comp: " << res1 << std::endl;
	stream << "value_comp: " << res2 << std::endl;

	map1.clear();
	map2.clear();
	stream << "\n\nmaps after clear: \n";
	ft_print_map(map1, stream);
	ft_print_map(map2, stream);
	return ;
	
}

void ft_set_out(std::ostream &stream)
{
	stream << "----------set_tests----------" << std::endl;

	std::list<int> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(i + 4);

	ft::set<int> set1;

	ft::set<int> set2(lst.begin(), lst.end());
	
	ft::set<int>::value_type tmp(42);
	ft::set<int>::value_type tmp2(21);
	ft::set<int>::iterator it;
	ft::set<int>::iterator it2;
	ft::set<int>::reverse_iterator itr;

	
	stream << "is empty set1: " << set1.empty() << std::endl;
	stream << "is empty set2: " << set2.empty() << std::endl;
	
	set1 = set2;
	stream << "set1 after set1 = set2: " << std::endl;
	
	ft_print_set(set1, stream);
	stream << "set2: " << set1.empty() << std::endl;
	ft_print_set(set2, stream);

	stream << "set1 after insert key 42 and then 21: " << std::endl;
	set1.insert(tmp);
	set1.insert(tmp2);
	ft_print_set(set1, stream);
	
	stream << "set2 after erase key 8 and then key 0: " << std::endl;
	set2.erase(8);
	set2.erase(0);
	ft_print_set(set2, stream);
	
	stream << "set1 after erase from begin to ++ ++ begin " << std::endl;
	set1.erase(set1.begin(), (++(++set1.begin())));
	ft_print_set(set1, stream);
	
	stream << "set1 after erase another erase with iterators:" << std::endl;
	set1.erase((++(++set1.begin())), --set1.end());
	ft_print_set(set1, stream);
	
	it = set1.end(); --it;
	stream << "set1 begin() key:" << *(set1.begin()) << std::endl;
	stream << "set1 --end() key:" << *it << std::endl;
	
	stream << "set1 rbegin() key:" << *(set1.rbegin()) << std::endl;
	itr = set1.rend(); --itr;
	stream << "set1 rend() key:" << *itr << std::endl;

	set1.insert(1);
	set1.insert(99);
	set1.insert(2);
	set1.insert(4);
	set1.insert(8);
	set1.insert(9);

	stream << "set1 lower_bound(10): ";
	stream << *(set1.lower_bound(10)) << std::endl;
	stream << "set1 lower_bound(8): ";
	stream << *(set1.lower_bound(8)) << std::endl;

	stream << "set1 upper_bound(11): ";
	it = set1.upper_bound(11);
	if (it != set1.end())
		stream << *(it) << std::endl;
	stream << "set1 upper_bound(100): ";
	it = set1.upper_bound(100);
	if (it != set1.end())
		stream << *(it) << std::endl;
	stream << std::endl;

	stream << "\ncheck equal_range in set1: " << std::endl;
	ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> eq_it = set1.equal_range(7);
        stream << "set1.equal_range(7)" << std::endl;
		if (eq_it.first != set1.end())
            stream << "Key: " << *(eq_it.first) << std::endl;
        else
            stream << "Hasn't find lower_bound 7" << std::endl;
        if (eq_it.second != set1.end())
            stream << "Key: " << *(eq_it.second) << std::endl;
        else
            stream << "Hasn't find upper_bound 7" << std::endl;
        eq_it = set1.equal_range(999);
		stream << "set1.equal_range(999)" << std::endl;
        if (eq_it.first != set1.end())
            stream << "Key: " << *(eq_it.first) << std::endl;
        else
            stream << "Hasn't find lower_bound 999" << std::endl;
        if (eq_it.second != set1.end())
            stream << "Key: " << *(eq_it.second) << std::endl;
        else
            stream << "Hasn't find upper_bound 999" << std::endl;
	stream << std::endl;
	stream << "set1:" << std::endl; ft_print_set(set1, stream);
	stream << "set2:" << std::endl; ft_print_set(set2, stream);
	set1.swap(set2);
	stream << "swap set1 and set2:\n ";
	stream << "set1:" << std::endl; ft_print_set(set1, stream);
	stream << "set2:" << std::endl; ft_print_set(set2, stream);

	it = set1.find(7);
	stream << "set1.find(7) second elem->: " << *it << std::endl;
	
	stream << std::endl;
	stream << "\nset1.count(9):        " << set1.count(9) << std::endl;
	stream << "and set1.count(9999): " << set1.count(9999) << std::endl;
	stream << std::endl;
	
	it = set1.begin(); ++it;
	it2 = set1.end(); -- it2; --it2;
	bool res1 = set1.key_comp()(*(set1.begin()), *it);
	bool res2 = set1.value_comp()(*it2, *it);
	stream << std::endl;
	stream << "key_comp: " << res1 << std::endl;
	stream << "value_comp: " << res2 << std::endl;

	set1.clear();
	set2.clear();
	stream << "\n\nsets after clear: \n";
	ft_print_set(set1, stream);
	ft_print_set(set2, stream);

	return ;
}

void std_set_out(std::ostream &stream)
{
	stream << "----------set_tests----------" << std::endl;

	std::list<int> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(i + 4);

	std::set<int> set1;

	std::set<int> set2(lst.begin(), lst.end());
	
	std::set<int>::value_type tmp(42);
	std::set<int>::value_type tmp2(21);
	std::set<int>::iterator it;
	std::set<int>::iterator it2;
	std::set<int>::reverse_iterator itr;

	
	stream << "is empty set1: " << set1.empty() << std::endl;
	stream << "is empty set2: " << set2.empty() << std::endl;
	
	set1 = set2;
	stream << "set1 after set1 = set2: " << std::endl;
	
	ft_print_set(set1, stream);
	stream << "set2: " << set1.empty() << std::endl;
	ft_print_set(set2, stream);

	stream << "set1 after insert key 42 and then 21: " << std::endl;
	set1.insert(tmp);
	set1.insert(tmp2);
	ft_print_set(set1, stream);
	
	stream << "set2 after erase key 8 and then key 0: " << std::endl;
	set2.erase(8);
	set2.erase(0);
	ft_print_set(set2, stream);
	
	stream << "set1 after erase from begin to ++ ++ begin " << std::endl;
	set1.erase(set1.begin(), (++(++set1.begin())));
	ft_print_set(set1, stream);
	
	stream << "set1 after erase another erase with iterators:" << std::endl;
	set1.erase((++(++set1.begin())), --set1.end());
	ft_print_set(set1, stream);
	
	it = set1.end(); --it;
	stream << "set1 begin() key:" << *(set1.begin()) << std::endl;
	stream << "set1 --end() key:" << *it << std::endl;
	
	stream << "set1 rbegin() key:" << *(set1.rbegin()) << std::endl;
	itr = set1.rend(); --itr;
	stream << "set1 rend() key:" << *itr << std::endl;

	set1.insert(1);
	set1.insert(99);
	set1.insert(2);
	set1.insert(4);
	set1.insert(8);
	set1.insert(9);

	stream << "set1 lower_bound(10): ";
	stream << *(set1.lower_bound(10)) << std::endl;
	stream << "set1 lower_bound(8): ";
	stream << *(set1.lower_bound(8)) << std::endl;

	stream << "set1 upper_bound(11): ";
	it = set1.upper_bound(11);
	if (it != set1.end())
		stream << *(it) << std::endl;
	stream << "set1 upper_bound(100): ";
	it = set1.upper_bound(100);
	if (it != set1.end())
		stream << *(it) << std::endl;
	stream << std::endl;

	stream << "\ncheck equal_range in set1: " << std::endl;
	std::pair<std::set<int>::iterator, std::set<int>::iterator> eq_it = set1.equal_range(7);
		stream << "set1.equal_range(7)" << std::endl;
        if (eq_it.first != set1.end())
            stream << "Key: " << *(eq_it.first) << std::endl;
        else
            stream << "Hasn't find lower_bound 7" << std::endl;
        if (eq_it.second != set1.end())
            stream << "Key: " << *(eq_it.second) << std::endl;
        else
            stream << "Hasn't find upper_bound 7" << std::endl;
        eq_it = set1.equal_range(999);
		stream << "set1.equal_range(999)" << std::endl;
        if (eq_it.first != set1.end())
            stream << "Key: " << *(eq_it.first) << std::endl;
        else
            stream << "Hasn't find lower_bound 999" << std::endl;
        if (eq_it.second != set1.end())
            stream << "Key: " << *(eq_it.second) << std::endl;
        else
            stream << "Hasn't find upper_bound 999" << std::endl;
	stream << std::endl;
	stream << "set1:" << std::endl; ft_print_set(set1, stream);
	stream << "set2:" << std::endl; ft_print_set(set2, stream);
	set1.swap(set2);
	stream << "swap set1 and set2:\n ";
	stream << "set1:" << std::endl; ft_print_set(set1, stream);
	stream << "set2:" << std::endl; ft_print_set(set2, stream);

	it = set1.find(7);
	stream << "set1.find(7) second elem->: " << *it << std::endl;
	
	stream << std::endl;
	stream << "\nset1.count(9):        " << set1.count(9) << std::endl;
	stream << "and set1.count(9999): " << set1.count(9999) << std::endl;
	stream << std::endl;
	
	it = set1.begin(); ++it;
	it2 = set1.end(); -- it2; --it2;
	bool res1 = set1.key_comp()(*(set1.begin()), *it);
	bool res2 = set1.value_comp()(*it2, *it);
	stream << std::endl;
	stream << "key_comp: " << res1 << std::endl;
	stream << "value_comp: " << res2 << std::endl;

	set1.clear();
	set2.clear();
	stream << "\n\nsets after clear: \n";
	ft_print_set(set1, stream);
	ft_print_set(set2, stream);

	return ;
}

void ft_check_cntnr(std::ostream &stream, int flag, std::string nm_spc)
{
	if (flag == 1)
	{
		if (nm_spc == "ft")
			ft_vctr_out(stream);
		else if (nm_spc == "std")
			std_vctr_out(stream);
		else
		{
			throw std::exception();
			return ;
		}
	}
	else if (flag == 2)
	{
		if (nm_spc == "ft")
			ft_stck_out(stream);
		else if (nm_spc == "std")
			std_stck_out(stream);
		else
		{
			throw std::exception();
			return ;
		}
	}
	else if (flag == 3)
	{
		if (nm_spc == "ft")
			ft_map_out(stream);
		else if (nm_spc == "std")
			std_map_out(stream);
		else
		{
			throw std::exception();
			return ;
		}
	}
	else if (flag == 4)
	{
		if (nm_spc == "ft")
			ft_set_out(stream);
		else if (nm_spc == "std")
			std_set_out(stream);
		else
		{
			throw std::exception();
			return ;
		}
	}
	else
		throw std::exception();
		
}

void ft_container(std::string ft_name, std::string stl_name, int flag)
{
	std::string ft_filename = ft_name + ".txt";
	unsigned int 	start_time_ft = clock();
	std::ofstream outPutFile_ft;
	outPutFile_ft.open(ft_filename);
	if (!outPutFile_ft.is_open())
		throw std::exception();
	ft_check_cntnr(outPutFile_ft, flag, "ft");
	outPutFile_ft.close();
	unsigned int 	finish_time_ft = clock();
	std::cout << YELLOW << " " << ft_name << " time = " << finish_time_ft - start_time_ft << std::setprecision(7) << " msec" << DFLT << std::endl;
		

	std::string std_filename = stl_name + ".txt";	
	unsigned int 	start_time_std = clock();
	std::ofstream outPutFile_std;
	outPutFile_std.open(std_filename);
	if (!outPutFile_std.is_open())
		throw std::exception();
	ft_check_cntnr(outPutFile_std, flag, "std");
	outPutFile_std.close();
	unsigned int 	finish_time_std = clock();
	std::cout << YELLOW << stl_name << " time = " << finish_time_std - start_time_std << std::setprecision(7) << " msec" << DFLT << std::endl;
	
	std::cout << BLUE << "* " << ft_name << " and " << stl_name << " check files have been created *" << DFLT << std::endl << std::endl;
	return ;
}