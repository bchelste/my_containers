/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:16:05 by bchelste          #+#    #+#             */
/*   Updated: 2022/02/07 20:56:31 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	
	template<typename T, typename Container = ft::vector<T> >
	class stack
	{
		public:
			
			//Member types:
			
			typedef T										value_type;
			typedef Container								container_type;
			typedef size_t									size_type;
			
		protected:
		
			container_type									c;

		public:

			//Member functions:

			explicit stack(const container_type &cont = container_type());
			explicit stack(const stack &data);
			
			~stack();

			stack &operator=(const stack &data);

			bool				empty() const;
			
			size_type			size() const;

			value_type			&top();
			const value_type 	&top() const;

			void				push(const value_type &val);

			void				pop();

			template<typename TF, typename ContainerF>
			friend bool operator==(const stack<TF, ContainerF> &lhs, const stack<TF, ContainerF> &rhs);

			template<typename TF, typename ContainerF>
			friend bool operator<(const stack<TF, ContainerF> &lhs, const stack<TF, ContainerF> &rhs);

	};

template<typename T, typename Container>
stack<T, Container>::stack(const container_type &cont) : c(cont)
{
	
}

template<typename T, typename Container>
stack<T, Container>::stack(const stack &data) : c(data.c)
{
	
}

template<typename T, typename Container>
stack<T, Container>::~stack()
{
	
}

template<typename T, typename Container>
stack<T, Container> &stack<T, Container>::operator=(const stack &data)
{
	if (this != &data)
		c = data.c;
	return (*this);
}

template<typename T, typename Container>
bool stack<T, Container>::empty() const
{
	return (c.empty());
}

template<typename T, typename Container>
typename stack<T, Container>::size_type	stack<T, Container>::size() const
{
	return (c.size());
}

template<typename T, typename Container>
typename stack<T, Container>::value_type	&stack<T, Container>::top()
{
	return (c.back());
}

template<typename T, typename Container>
const typename stack<T, Container>::value_type	&stack<T, Container>::top() const
{
	return (c.back());
}

template<typename T, typename Container>
void	stack<T, Container>::push(const value_type &val)
{
	c.push_back(val);
}

template<typename T, typename Container>
void	stack<T, Container>::pop()
{
	c.pop_back();
}

	// Non-member function overloads:

template<typename TF, typename ContainerF>
bool operator==(const stack<TF, ContainerF> &lhs, const stack<TF, ContainerF> &rhs)
{
	return (lhs.c == rhs.c);
}

template<typename TF, typename ContainerF>
bool operator!=(const stack<TF, ContainerF> &lhs, const stack<TF, ContainerF> &rhs)
{
	return (!(lhs == rhs));
}

template<typename TF, typename ContainerF>
bool operator<(const stack<TF, ContainerF> &lhs, const stack<TF, ContainerF> &rhs)
{
	return (lhs.c < rhs.c);
}

template<typename TF, typename ContainerF>
bool operator>(const stack<TF, ContainerF> &lhs, const stack<TF, ContainerF> &rhs)
{
	return (rhs < lhs);
}

template<typename TF, typename ContainerF>
bool operator<=(const stack<TF, ContainerF> &lhs, const stack<TF, ContainerF> &rhs)
{
	return (!(rhs < lhs));
}

template<typename TF, typename ContainerF>
bool operator>=(const stack<TF, ContainerF> &lhs, const stack<TF, ContainerF> &rhs)
{
	return (!(lhs < rhs));
}
	
}

#endif