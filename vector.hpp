/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 13:59:44 by bchelste          #+#    #+#             */
/*   Updated: 2022/02/09 21:43:58 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include <stdexcept>

# include "reimplement.hpp"
# include "iterators.hpp"

namespace	ft
{

template< typename T, typename Allocator = std::allocator<T> >
class vector
{
	public:
	
		// Member types:
		
		typedef T														value_type;
		typedef Allocator												allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef typename ft::vector_iterator<T>							iterator;
		typedef typename ft::vector_const_iterator<T>					const_iterator;
		typedef typename ft::reverse_iterator<iterator> 				reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef typename allocator_type::size_type						size_type;
		typedef typename allocator_type::difference_type				difference_type;

	private:

		pointer			v_begin;
		size_type		v_size;
		size_type		v_capacity;
		allocator_type	alloc;
		
	public:
	
		// Member functions:
		
		// Constr/destr:
		
		explicit vector(const allocator_type &n_alloc = allocator_type());
		explicit vector(size_type n, const value_type &val_tp = value_type(),
						const allocator_type &n_alloc = allocator_type());
		template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type &n_alloc = allocator_type(),
					typename enable_if<!ft::is_integral<InputIterator>::value>::type* = 0);
		explicit vector(const vector &data);
		
		~vector();

		vector &operator=(const vector &x);

		// Iterators:
		
		iterator				begin();
		iterator				end();
		
		const_iterator			begin() const;
		const_iterator			end() const;

		reverse_iterator 		rbegin();
		reverse_iterator 		rend();

		const_reverse_iterator	rbegin() const;
		const_reverse_iterator	rend() const;

		// Capacity:
		
		size_type				size() const;
		
		size_type				max_size() const;
		
		void					resize(size_type n, value_type val = value_type());
		
		size_type				capacity() const;
		
		bool					empty() const;
		
		void					reserve(size_type n);

		// Element access:
		
		reference				operator[](size_type n);
		const_reference			operator[](size_type n) const;
		
		reference				at(size_type n);
		const_reference			at(size_type n) const;

		reference				front();
		const_reference			front() const;

		reference				back();
		const_reference			back() const;

		// Modifiers:
		
		template <class InputIterator>
			void				assign(InputIterator first, InputIterator last,
									typename enable_if<!ft::is_integral<InputIterator>::value>::type* = 0);
		void					assign(size_type n, const value_type &val);
		
		void					push_back(const value_type &val);
		
		void					pop_back();
		
		iterator				insert(iterator position, const value_type &val);
		void					insert(iterator position, size_type n, const value_type &val);
		template <class InputIterator>
			void				insert(iterator position, InputIterator first, InputIterator last,
									typename enable_if<!ft::is_integral<InputIterator>::value>::type* = 0);

		iterator				erase(iterator first, iterator last);
		iterator				erase(iterator position);
		
		void					swap(vector &x);

		void					clear();
		
		// Allocator:
		
		allocator_type			get_allocator() const;


		// My methods:
		
	private:

		void 					vctr_constr(pointer start, size_type n, const value_type &v_type);
		
		template <class InputIterator>
		void					vctr_range_constr(InputIterator first, InputIterator last, pointer start);
		
		template <class InputIterator>
		void					vctr_range_alloc(InputIterator first, InputIterator last);

		template <class InputIterator>
		void					vctr_range_first_alloc(InputIterator first, InputIterator last);

		void					vctr_reserve_realloc(size_type n);
		
};

// Constr/destr:

template<typename T, typename Allocator>
vector<T, Allocator>::vector(const allocator_type &n_alloc)
	: v_begin(NULL), v_size(0), v_capacity(0), alloc(n_alloc) {}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(size_type n,
		const value_type &val_tp, const allocator_type &n_alloc) : alloc(n_alloc)
{
	this->v_size = n;
	this->v_capacity = n;
	this->v_begin = this->alloc.allocate(this->v_capacity);
	this->vctr_constr(v_begin, n, val_tp);
}

template<typename T, typename Allocator>
template <class InputIterator>
vector<T, Allocator>::vector(InputIterator first, InputIterator last, const allocator_type &n_alloc,
	typename enable_if<!ft::is_integral<InputIterator>::value>::type*) : alloc(n_alloc)
{
	this->vctr_range_first_alloc(first, last);
	this->vctr_range_constr(first, last, this->v_begin);		
}

template<typename T, typename Allocator>
vector<T, Allocator>::vector(const vector<T, Allocator> &data) : alloc(data.alloc)
{
	this->vctr_range_first_alloc(data.begin(), data.end());
	this->vctr_range_constr(data.begin(), data.end(), this->v_begin);
}

template<typename T, typename Allocator>
vector<T, Allocator>::~vector()
{
	this->clear();
	this->alloc.deallocate(this->v_begin, this->v_capacity);
}

template<typename T, typename Allocator>
vector<T, Allocator> &vector<T, Allocator>::operator=(const vector &data)
{
	if ((this != &data) && (this->capacity() < data.capacity()))
	{
		this->clear();
		this->alloc.deallocate(this->v_begin, this->v_capacity);
		this->vctr_range_first_alloc(data.begin(), data.end());
		this->vctr_range_constr(data.begin(), data.end(), this->v_begin);
	}
	else 
		this->assign(data.begin(), data.end());
	return (*this);
}

// Iterators:

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin()
{
	return (iterator(this->v_begin));
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end()
{
	return (iterator(this->v_begin + this->v_size));
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const
{
	return (const_iterator(this->v_begin));
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const
{
	return (const_iterator(this->v_begin + this->v_size));
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin()
{
	return (reverse_iterator(this->v_begin + this->v_size));
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend()
{
	return (reverse_iterator(this->v_begin));
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const
{
	return (reverse_const_iterator(this->v_begin + this->v_size));
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const
{
	return (reverse_const_iterator(this->v_begin));
}

// Capacity:

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type	vector<T, Allocator>::size() const
{
	return (this->v_size);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type	vector<T, Allocator>::max_size() const
{
	size_type n;

	n = this->alloc.max_size();
	return (n);
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::resize(size_type n, value_type val)
{
	pointer		old_v_begin = this->v_begin;
	size_type	old_v_capacity = this->v_capacity;
	iterator	tmp;
	
	if (n < this->v_size)
		this->erase(iterator(this->v_begin + n), iterator(this->v_begin + this->v_size));
	else
	{
		this->v_capacity = n;
		this->v_begin = this->alloc.allocate(this->v_capacity);
		this->vctr_range_constr(iterator(old_v_begin), iterator(old_v_begin + this->v_size), this->v_begin);
		tmp = iterator(old_v_begin);
		while (tmp != iterator(old_v_begin + this->v_size))
		{
			this->alloc.destroy(tmp.getptr());
			++tmp;
		}
		
		this->alloc.deallocate(old_v_begin, old_v_capacity);
		this->vctr_constr((this->v_begin + this->v_size), (n - this->v_size), val);
		this->v_size += (n - this->v_size);
	}
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type	vector<T, Allocator>::capacity() const
{
	return (this->v_capacity);
}

template<typename T, typename Allocator>
bool	vector<T, Allocator>::empty() const
{
	if (this->v_size == 0)
		return (true);
	return (false);
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::reserve(size_type n)
{
	if (n > this->max_size())
		throw std::length_error("reserve size requested is greater than max_size");
	if (n > this->v_capacity)
		this->vctr_reserve_realloc(n);
}

// Element access:

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::operator[](size_type n)
{
	return ((this->v_begin)[n]);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::operator[](size_type n) const
{
	return ((this->v_begin)[n]);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::at(size_type n)
{
	if ((n < 0) || (n >= this->v_size))
		throw std::out_of_range("position out of bounds");
	return ((this->v_begin)[n]);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::at(size_type n) const
{
	if ((n < 0) || (n >= this->v_size))
		throw std::out_of_range("position out of bounds");
	return ((this->v_begin)[n]);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::front()
{
	return ((this->v_begin)[0]);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::front() const
{
	return ((this->v_begin)[0]);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference vector<T, Allocator>::back()
{
	return ((this->v_begin)[this->v_size - 1]);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference vector<T, Allocator>::back() const
{
	return ((this->v_begin)[this->v_size - 1]);
}

// Modifiers:

template<typename T, typename Allocator>
template <class InputIterator>
void	vector<T, Allocator>::assign(InputIterator first, InputIterator last,
	typename enable_if<!ft::is_integral<InputIterator>::value>::type*)
{
	this->clear();
	size_type tmp = 0;
	InputIterator tmp_it = first;
	for (; tmp_it != last; ++tmp_it)
		++tmp;
	if (tmp > this->v_capacity)
		this->vctr_reserve_realloc(tmp);
	this->v_size = tmp;
	this->vctr_range_constr(first, last, this->v_begin);
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::assign(size_type n, const value_type &val)
{
	this->clear();
	this->alloc.deallocate(this->v_begin, this->v_capacity);
	this->v_size = n;
	this->v_capacity = n;
	this->v_begin = this->alloc.allocate(this->v_capacity);
	this->vctr_constr(this->v_begin, n, val);
}

template<typename T, typename Allocator>
void vector<T, Allocator>::push_back(const value_type &val)
{
	this->insert(this->end(), val);
}

template<typename T, typename Allocator>
void vector<T, Allocator>::pop_back()
{
	iterator it = this->end();
	--it;
	this->erase(it, this->end());
	
}
template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::insert(iterator position, const value_type &val)
{	
	difference_type tmp = position.getptr() - this->v_begin;
	iterator it(this->v_begin + tmp);
	this->insert(position, 1, val);
	return(it);
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::insert(iterator position, size_type n, const value_type &val)
{
	difference_type new_pos = position - this->begin();
	difference_type tmp = static_cast<difference_type>(n);
	if ((this->v_size + n) > this->v_capacity)
	{
		this->vctr_reserve_realloc(n);
		position = this->begin() + new_pos;
	}
	iterator it = this->end();
	--it;
	for (;it >= position; --it)
	{
		this->alloc.construct(&(*(it + tmp)), *it);
		this->alloc.destroy(&(*it));
	} 
	this->vctr_constr(position.getptr(), n, val);
	this->v_size += n;
}

template<typename T, typename Allocator>
template <class InputIterator>
void	vector<T, Allocator>::insert(iterator position, InputIterator first, InputIterator last,
	typename enable_if<!ft::is_integral<InputIterator>::value>::type*)
{
	size_type tmp = 0;
	InputIterator itcnt = first;
	difference_type new_pos = position - this->begin();
	for (; itcnt != last; ++itcnt)
		++tmp;
	difference_type dt = static_cast<difference_type>(tmp);
	if ((this->v_size + tmp) > this->v_capacity)
	{
		this->vctr_reserve_realloc(tmp);
		position = this->begin() + new_pos;
	}
	iterator it = this->end();
	--it;
	for (;it >= position; --it)
	{
		this->alloc.construct(&(*(it + dt)), *it);
		this->alloc.destroy(&(*it));
	}
	this->vctr_range_constr(first, last, position.getptr());
	this->v_size += tmp;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::erase(iterator first, iterator last)
{
	size_type	nbr;
	iterator	it;
	nbr = 0;
	if (first == last)
		return last;
	difference_type tmp = last - first;
	for (; first != last; ++first)
	{
		this->alloc.destroy(first.getptr());
		++nbr;
	}
	for (; last != this->end(); ++last)
	{
		it = last - tmp;
		this->alloc.construct(it.getptr(), *last);
		this->alloc.destroy(last.getptr());
	}
	this->v_size -= nbr;
	it = first - tmp; 
	return (it);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::erase(iterator position)
{
	iterator	it;
	difference_type tmp = 1;
	
	it = this->erase(position, (position + tmp));
	return (it);
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::swap(vector<T, Allocator> &x)
{
	pointer			p_tmp;
	size_type		s_tmp;
	size_type		c_tmp;
	allocator_type	a_tmp;

	p_tmp = this->v_begin;
	this->v_begin = x.v_begin;
	x.v_begin = p_tmp;

	s_tmp = this->v_size;
	this->v_size = x.v_size;
	x.v_size = s_tmp;

	c_tmp = this->v_capacity;
	this->v_capacity = x.v_capacity;
	x.v_capacity = c_tmp;

	a_tmp = this->alloc;
	this->alloc = x.alloc;
	x.alloc = a_tmp;
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::clear()
{
	this->erase(this->begin(), iterator(this->v_begin + this->v_size));
}

// Allocator:

template<typename T, typename Allocator>
typename vector<T, Allocator>::allocator_type	vector<T, Allocator>::get_allocator() const
{
	return (this->alloc);
}

// My methods:

template<typename T, typename Allocator>
void 	vector<T, Allocator>::vctr_constr(pointer start,
									size_type n, const value_type &v_type)
{
	for (size_type i = 0; i < n; ++i)
	{
		this->alloc.construct(start, v_type);
		++start;
	}
}

template<typename T, typename Allocator>
template <class InputIterator>	
void	vector<T, Allocator>::vctr_range_alloc(InputIterator first, InputIterator last)
{
	size_type	tmp = 0;
	
	for (; first != last; ++first)
		++tmp;
	this->v_size = tmp;
	this->v_capacity = tmp * 2;
	this->v_begin = this->alloc.allocate(this->v_capacity);
}

template<typename T, typename Allocator>
template <class InputIterator>	
void	vector<T, Allocator>::vctr_range_first_alloc(InputIterator first, InputIterator last)
{
	size_type	tmp = 0;
	
	for (; first != last; ++first)
		++tmp;
	this->v_size = tmp;
	this->v_capacity = tmp;
	this->v_begin = this->alloc.allocate(this->v_capacity);
}

template<typename T, typename Allocator>
template <class InputIterator>
void	vector<T, Allocator>::vctr_range_constr(InputIterator first, InputIterator last, pointer start)
{
	for (; first != last; ++first)
	{
		this->alloc.construct(start, *first);
		++start;
	}
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::vctr_reserve_realloc(size_type n)
{
	size_type	old_v_capacity = this->v_capacity;
	pointer		old_v_begin = this->v_begin;
	iterator	tmp;
	
	if (old_v_capacity == 0)
		this->v_capacity = n;
	else if ((this->v_size + n) > (old_v_capacity * 2))
		this->v_capacity = this->v_size + n;
	else
		this->v_capacity = old_v_capacity * 2;
	this->v_begin = this->alloc.allocate(this->v_capacity);
	this->vctr_range_constr(iterator(old_v_begin), iterator(old_v_begin + this->v_size), this->v_begin);
	tmp = iterator(old_v_begin);
	while (tmp != iterator(old_v_begin + this->v_size))
	{
		this->alloc.destroy(tmp.getptr());
		++tmp;
	}
	this->alloc.deallocate(old_v_begin, old_v_capacity);
}

// Non-member function overloads:

template<typename T, typename Allocator>
void swap(vector<T, Allocator> &x, vector<T, Allocator> &y)
{
	x.swap(y);
}

template<typename T, typename Allocator>
bool operator == (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
	return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template<typename T, typename Allocator>
bool operator != (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
	return (!(lhs == rhs));
}

template<typename T, typename Allocator>
bool operator < (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<typename T, typename Allocator>
bool operator > (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
	return (rhs < lhs);
}

template<typename T, typename Allocator>
bool operator <= (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
	return (!(rhs < lhs));
}

template<typename T, typename Allocator>
bool operator >= (const vector<T, Allocator> &lhs, const vector<T, Allocator> &rhs)
{
	return (!(lhs < rhs));
}

}

#endif