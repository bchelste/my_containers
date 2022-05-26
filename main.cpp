/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:59:47 by bchelste          #+#    #+#             */
/*   Updated: 2022/02/19 19:22:57 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>


#include "reimplement.hpp"
#include "iterators.hpp"
#include "rb_tree.hpp"
#include "set_utils.hpp"

#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"



int main()
{
	try
	{
		ft_container("ft_vector", "std_vector", 1);
		ft_container("ft_stack", "std_stack", 2);
		ft_container("ft_map", "std_map", 3);
		ft_container("ft_set", "std_set", 4);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return(0);
}

