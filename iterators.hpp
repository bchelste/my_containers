/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:45:41 by bchelste          #+#    #+#             */
/*   Updated: 2022/02/18 20:18:13 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
# define ITERATORS_HPP

namespace ft
{

	// utils for iterators:
	
	template<typename Iterator>
	struct iterator_traits
	{
		public:
    		typedef typename Iterator::difference_type		difference_type;
    		typedef typename Iterator::value_type			value_type;
    		typedef typename Iterator::pointer				pointer;
    		typedef typename Iterator::reference			reference;
    		typedef typename Iterator::iterator_category	iterator_category;	
	};

	// iterator_traits:

	template<typename T>
	struct iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t 							difference_type;
    		typedef T 										value_type;
    		typedef T* 										pointer;
    		typedef T& 										reference;
    		typedef std::random_access_iterator_tag 		iterator_category;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t 							difference_type;
    		typedef const T 								value_type;
			typedef const T* 								pointer;
    		typedef const T& 								reference;
    		typedef std::random_access_iterator_tag 		iterator_category;
	};
	
// iterator base class:

template<typename Category, typename T, typename Distance = std::ptrdiff_t, 
		typename Pointer = T*, typename Reference = T&>
struct iterator
{
		
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

// vector_iterator:

template<typename T>
class vector_iterator : public iterator<std::random_access_iterator_tag, T>
{	
	public:
		
		typedef T												value_type;
		typedef typename std::ptrdiff_t							difference_type;
		typedef T*												pointer;
		typedef T&												reference;
		//typedef typename std::random_access_iterator_tag		iterator_category;
		
	private:
		
		pointer													ptr;
		
	public:

		vector_iterator();
		
		vector_iterator(const vector_iterator<T> &data);
		
		vector_iterator(pointer n_ptr);
		
		~vector_iterator();

		vector_iterator &operator=(const vector_iterator<T> &data);

		reference		operator*() const;
		pointer			operator->() const;
		reference		operator[](std::ptrdiff_t n) const;
		
		pointer			getptr() const;
		
		bool	operator==(const vector_iterator<T> &other) const;
		bool	operator!=(const vector_iterator<T> &other) const;
		bool	operator>(const vector_iterator<T> &other) const;
		bool	operator<(const vector_iterator<T> &other) const;
		bool	operator>=(const vector_iterator<T> &other) const;
		bool	operator<=(const vector_iterator<T> &other) const;

		vector_iterator	operator++(int);	// iterator++
		vector_iterator	&operator++();		// ++iterator

		vector_iterator	operator--(int);	// iterator--
		vector_iterator	&operator--();		// --iterator

		vector_iterator &operator+=(difference_type nbr);
		vector_iterator operator+(difference_type nbr) const;

		vector_iterator &operator-=(difference_type nbr);
		vector_iterator operator-(difference_type nbr) const;
	
};

template<typename T>
vector_iterator<T>::vector_iterator() : ptr(NULL) {}

template<typename T>
vector_iterator<T>::vector_iterator(const vector_iterator<T> &data) : ptr(data.getptr()) {}

template<typename T>
vector_iterator<T>::vector_iterator(vector_iterator<T>::pointer n_ptr) : ptr(n_ptr) {}

template<typename T>
vector_iterator<T>::~vector_iterator() {}

template<typename T>
vector_iterator<T> &vector_iterator<T>::operator=(const vector_iterator<T> &data)
{
	this->ptr = data.ptr;
	return (*this);
}

template<typename T>
typename vector_iterator<T>::reference vector_iterator<T>::operator*() const
{
	return (*(this->ptr));
}

template<typename T>
typename vector_iterator<T>::pointer vector_iterator<T>::operator->() const
{
	return (ptr);
}

template<typename T>
typename vector_iterator<T>::reference vector_iterator<T>::operator[](typename vector_iterator<T>::difference_type n) const
{
	return (ptr[n]);
}

template<typename T>
typename vector_iterator<T>::pointer	vector_iterator<T>::getptr() const
{
	return (ptr);
}

template<typename T>
bool	vector_iterator<T>::operator==(const vector_iterator<T> &other) const
{
	return (this->ptr == other.ptr);
}

template<typename T>
bool	vector_iterator<T>::operator!=(const vector_iterator<T> &other) const
{
	return (this->ptr != other.ptr);
}

template<typename T>
bool	vector_iterator<T>::operator>(const vector_iterator<T> &other) const
{
	return (this->ptr > other.ptr);
}

template<typename T>
bool	vector_iterator<T>::operator<(const vector_iterator<T> &other) const
{
	return (this->ptr < other.ptr);
}

template<typename T>
bool	vector_iterator<T>::operator>=(const vector_iterator<T> &other) const
{
	return (this->ptr >= other.ptr);
}

template<typename T>
bool	vector_iterator<T>::operator<=(const vector_iterator<T> &other) const
{
	return (this->ptr <= other.ptr);
}

template<typename T>
vector_iterator<T> vector_iterator<T>::operator++(int)
{
	vector_iterator tmp(*this);
	
	this->ptr += 1;
	return (tmp);
}

template<typename T>
vector_iterator<T> &vector_iterator<T>::operator++()
{
	this->ptr += 1;
	return (*this);
}

template<typename T>
vector_iterator<T> vector_iterator<T>::operator--(int)
{
	vector_iterator tmp(*this);
	
	this->ptr -= 1;
	return (tmp);
}

template<typename T>
vector_iterator<T> &vector_iterator<T>::operator--()
{
	this->ptr -= 1;
	return (*this);
}

template<typename T>
vector_iterator<T> &vector_iterator<T>::operator+=(typename vector_iterator<T>::difference_type nbr)
{
	this->ptr += nbr;
	return (*this);
}

template<typename T>
vector_iterator<T>	vector_iterator<T>::operator+(typename vector_iterator<T>::difference_type nbr) const
{
	return (this->ptr + nbr);
}

template<typename T>
vector_iterator<T> &vector_iterator<T>::operator-=(typename vector_iterator<T>::difference_type nbr)
{
	this->ptr -= nbr;
	return (*this);
}

template<typename T>
vector_iterator<T>	vector_iterator<T>::operator-(typename vector_iterator<T>::difference_type nbr) const
{
	return (this->ptr - nbr);
}

template<typename T>
vector_iterator<T>	operator-(typename vector_iterator<T>::difference_type nbr, const vector_iterator<T> &first)
{
	return (first.getptr() - nbr);
}

template<typename T>
typename vector_iterator<T>::difference_type operator-(const vector_iterator<T> &first, const vector_iterator<T> &second)
{
	return (first.getptr() - second.getptr());
}

template<typename T>
vector_iterator<T> operator+(typename vector_iterator<T>::difference_type nbr, const vector_iterator<T> &first)
{
	return (first + nbr);
}

template<typename lT, typename rT>
bool	operator==(const vector_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() == rhs.getptr());
}

template<typename lT, typename rT>
bool	operator!=(const vector_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() != rhs.getptr());
}

template<typename lT, typename rT>
bool	operator<(const vector_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() < rhs.getptr());
}

template<typename lT, typename rT>
bool	operator<=(const vector_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() <= rhs.getptr());
}

template<typename lT, typename rT>
bool	operator>(const vector_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() > rhs.getptr());
}

template<typename lT, typename rT>
bool	operator>=(const vector_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() >= rhs.getptr());
}

// vector_const_iterator:

template<typename T>
class vector_const_iterator : public iterator<std::random_access_iterator_tag, T>
{
	public:
		
		typedef const T											value_type;
		typedef typename std::ptrdiff_t							difference_type;
		typedef const T*										pointer;
		typedef const T&										reference;
		typedef typename std::random_access_iterator_tag		iterator_category;

	private:

		pointer													ptr;
		
	public:

		vector_const_iterator();
		
		vector_const_iterator(const vector_const_iterator<T> &data);
		vector_const_iterator(const vector_iterator<T> &data);
		
		vector_const_iterator(pointer n_ptr);
		
		~vector_const_iterator();

		vector_const_iterator &operator=(const vector_const_iterator<T> &data);
		vector_const_iterator &operator=(const vector_iterator<T> &data);
		
		reference	operator*() const;
		pointer		operator->() const;
		reference	operator[](difference_type n) const;

		pointer		getptr() const;

		bool	operator==(const vector_const_iterator<T> &other) const;
		bool	operator!=(const vector_const_iterator<T> &other) const;
		bool	operator>(const vector_const_iterator<T> &other) const;
		bool	operator<(const vector_const_iterator<T> &other) const;
		bool	operator>=(const vector_const_iterator<T> &other) const;
		bool	operator<=(const vector_const_iterator<T> &other) const;

		vector_const_iterator	operator++(int);	// iterator++
		vector_const_iterator	&operator++();		// ++iterator

		vector_const_iterator	operator--(int);	// iterator--
		vector_const_iterator	&operator--();		// --iterator

		vector_const_iterator &operator+=(difference_type nbr);
		vector_const_iterator operator+(difference_type nbr) const;

		vector_const_iterator &operator-=(difference_type nbr);
		vector_const_iterator operator-(difference_type nbr) const;
		
};

template<typename T>
vector_const_iterator<T>::vector_const_iterator() : ptr(NULL) {}

template<typename T>
vector_const_iterator<T>::vector_const_iterator(const vector_const_iterator<T> &data) : ptr(data.getptr()) {}

template<typename T>
vector_const_iterator<T>::vector_const_iterator(const vector_iterator<T> &data) : ptr(data.getptr()) {}

template<typename T>
vector_const_iterator<T>::vector_const_iterator(const vector_const_iterator<T>::pointer n_ptr) : ptr(n_ptr) {}

template<typename T>
vector_const_iterator<T>::~vector_const_iterator() {}

template<typename T>
vector_const_iterator<T> &vector_const_iterator<T>::operator=(const vector_const_iterator<T> &data)
{
	this->ptr = data.getptr();
	return (*this);
}

template<typename T>
vector_const_iterator<T> &vector_const_iterator<T>::operator=(const vector_iterator<T> &data)
{
	this->ptr = data.getptr();
	return (*this);
}

template<typename T>
typename vector_const_iterator<T>::reference	vector_const_iterator<T>::operator*() const
{
	return (*(this->ptr));
}

template<typename T>
typename vector_const_iterator<T>::pointer	vector_const_iterator<T>::operator->() const
{
	return (ptr);
}

template<typename T>
typename vector_const_iterator<T>::reference	vector_const_iterator<T>::operator[](typename vector_const_iterator<T>::difference_type n) const
{
	return (ptr[n]);
}

template<typename T>
typename vector_const_iterator<T>::pointer	vector_const_iterator<T>::getptr() const
{
	return (ptr);
}

template<typename T>
bool	vector_const_iterator<T>::operator==(const vector_const_iterator<T> &other) const
{
	return (this->ptr == other.ptr);
}

template<typename T>
bool	vector_const_iterator<T>::operator!=(const vector_const_iterator<T> &other) const
{
	return (this->ptr != other.ptr);
}

template<typename T>
bool	vector_const_iterator<T>::operator>(const vector_const_iterator<T> &other) const
{
	return (this->ptr > other.ptr);
}

template<typename T>
bool	vector_const_iterator<T>::operator<(const vector_const_iterator<T> &other) const
{
	return (this->ptr < other.ptr);
}

template<typename T>
bool	vector_const_iterator<T>::operator>=(const vector_const_iterator<T> &other) const
{
	return (this->ptr >= other.ptr);
}

template<typename T>
bool	vector_const_iterator<T>::operator<=(const vector_const_iterator<T> &other) const
{
	return (this->ptr <= other.ptr);
}

template<typename T>
vector_const_iterator<T> vector_const_iterator<T>::operator++(int)
{
	vector_const_iterator<T> tmp(*this);
	
	this->ptr += 1;
	return (tmp);
}

template<typename T>
vector_const_iterator<T> &vector_const_iterator<T>::operator++()
{
	this->ptr += 1;
	return (*this);
}

template<typename T>
vector_const_iterator<T> vector_const_iterator<T>::operator--(int)
{
	vector_const_iterator<T> tmp(*this);
	
	this->ptr -= 1;
	return (tmp);
}

template<typename T>
vector_const_iterator<T> &vector_const_iterator<T>::operator--()
{
	this->ptr -= 1;
	return (*this);
}

template<typename T>
vector_const_iterator<T> &vector_const_iterator<T>::operator+=(typename vector_const_iterator<T>::difference_type nbr)
{
	this->ptr += nbr;
	return (*this);
}

template<typename T>
vector_const_iterator<T>	vector_const_iterator<T>::operator+(typename vector_const_iterator<T>::difference_type nbr) const
{
	return (this->ptr + nbr);
}

template<typename T>
vector_const_iterator<T> &vector_const_iterator<T>::operator-=(typename vector_const_iterator<T>::difference_type nbr)
{
	this->ptr -= nbr;
	return (*this);
}

template<typename T>
vector_const_iterator<T>	vector_const_iterator<T>::operator-(typename vector_const_iterator<T>::difference_type nbr) const
{
	return (this->ptr - nbr);
}

template<typename T>
typename vector_const_iterator<T>::difference_type operator-(const vector_const_iterator<T> &first, const vector_const_iterator<T> &second)
{
	return (first.getptr() - second.getptr());
}

template<typename T>
vector_const_iterator<T> operator+(typename vector_const_iterator<T>::difference_type nbr, const vector_const_iterator<T> &first)
{
	return (first + nbr);
}

template<typename lT, typename rT>
typename vector_const_iterator<lT>::difference_type operator-(const vector_const_iterator<lT> &first, const vector_iterator<rT> &second)
{
	return (first.getptr() - second.getptr());
}

template<typename lT, typename rT>
typename vector_const_iterator<lT>::difference_type operator-(const vector_iterator<lT> &first, const vector_const_iterator<rT> &second)
{
	return (first.getptr() - second.getptr());
}

template<typename lT, typename rT>
bool	operator==(const vector_iterator<lT> &lhs, const vector_const_iterator<rT> &rhs)
{
	return (lhs.getptr() == rhs.getptr());
}

template<typename lT, typename rT>
bool	operator!=(const vector_iterator<lT> &lhs, const vector_const_iterator<rT> &rhs)
{
	return (lhs.getptr() != rhs.getptr());
}

template<typename lT, typename rT>
bool	operator<(const vector_iterator<lT> &lhs, const vector_const_iterator<rT> &rhs)
{
	return (lhs.getptr() < rhs.getptr());
}

template<typename lT, typename rT>
bool	operator<=(const vector_iterator<lT> &lhs, const vector_const_iterator<rT> &rhs)
{
	return (lhs.getptr() <= rhs.getptr());
}

template<typename lT, typename rT>
bool	operator>(const vector_iterator<lT> &lhs, const vector_const_iterator<rT> &rhs)
{
	return (lhs.getptr() > rhs.getptr());
}

template<typename lT, typename rT>
bool	operator>=(const vector_iterator<lT> &lhs, const vector_const_iterator<rT> &rhs)
{
	return (lhs.getptr() >= rhs.getptr());
}

template<typename lT, typename rT>
bool	operator==(const vector_const_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() == rhs.getptr());
}

template<typename lT, typename rT>
bool	operator!=(const vector_const_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() != rhs.getptr());
}

template<typename lT, typename rT>
bool	operator<(const vector_const_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() < rhs.getptr());
}

template<typename lT, typename rT>
bool	operator<=(const vector_const_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() <= rhs.getptr());
}

template<typename lT, typename rT>
bool	operator>(const vector_const_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() > rhs.getptr());
}

template<typename lT, typename rT>
bool	operator>=(const vector_const_iterator<lT> &lhs, const vector_iterator<rT> &rhs)
{
	return (lhs.getptr() >= rhs.getptr());
}

// reverse iterator:

template <typename iter>
class reverse_iterator
{
	public:
		typedef iter													iterator_type;
		typedef typename iterator_traits<iter>::iterator_category		iterator_category;
		typedef typename iterator_traits<iter>::value_type 				value_type;
		typedef typename iterator_traits<iter>::difference_type 		difference_type;
		typedef typename iterator_traits<iter>::pointer 				pointer;
		typedef typename iterator_traits<iter>::reference 				reference;
		
	protected:

		iterator_type	r_it;

	public:
	
		reverse_iterator();

		reverse_iterator(iterator_type it);
		
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it);

		~reverse_iterator();

		template <class Iter>
		reverse_iterator		&operator=(const reverse_iterator<Iter> &data);

		iterator_type		base() const;
		
		reference			operator*() const;
		pointer				operator->() const;
		reference			operator[](difference_type n) const;

		reverse_iterator	operator+(difference_type n) const;

		reverse_iterator	&operator++();
		reverse_iterator	operator++(int);

		reverse_iterator	&operator+=(difference_type n);

		reverse_iterator	operator-(difference_type n) const;

		reverse_iterator	&operator--();
		reverse_iterator	operator--(int);

		reverse_iterator	&operator-=(difference_type n);

};

template<typename from_iterator>
reverse_iterator<from_iterator>::reverse_iterator() : r_it() {}

template<typename from_iterator>
reverse_iterator<from_iterator>::reverse_iterator(iterator_type it) : r_it(it) {}

template<typename from_iterator>
template<typename Iter>
reverse_iterator<from_iterator>::reverse_iterator(const reverse_iterator<Iter> &rev_it) : r_it(rev_it.base()) {}

template<typename from_iterator>
template<typename Iter>
reverse_iterator<from_iterator> &reverse_iterator<from_iterator>::operator=(const reverse_iterator<Iter> &data)
{
	this->r_it = data.base();
	return (*this);
}

template<typename from_iterator>
reverse_iterator<from_iterator>::~reverse_iterator() {}

template<typename from_iterator>
typename reverse_iterator<from_iterator>::iterator_type	reverse_iterator<from_iterator>::base() const
{
	return (this->r_it);
}

template<typename from_iterator>
typename reverse_iterator<from_iterator>::reference	reverse_iterator<from_iterator>::operator*() const
{
	iterator_type tmp = this->r_it;
	--tmp;
	return (*tmp);
}

template<typename from_iterator>
typename reverse_iterator<from_iterator>::pointer	reverse_iterator<from_iterator>::operator->() const
{
	return (&(this->operator*()));
}

template<typename from_iterator>
typename reverse_iterator<from_iterator>::reference	reverse_iterator<from_iterator>::operator[](reverse_iterator<from_iterator>::difference_type n) const
{
	return ((this->r_it)[- n - 1]);
}

template<typename from_iterator>
reverse_iterator<from_iterator>	reverse_iterator<from_iterator>::operator+(reverse_iterator<from_iterator>::difference_type n) const
{
	return (this->r_it - n);
}

template<typename from_iterator>
reverse_iterator<from_iterator>	&reverse_iterator<from_iterator>::operator++()
{
	--(this->r_it);
	return (*this);
}

template<typename from_iterator>
reverse_iterator<from_iterator>	reverse_iterator<from_iterator>::operator++(int)
{
	reverse_iterator tmp = *this;
	--(this->r_it);
	return(tmp);
}

template<typename from_iterator>
reverse_iterator<from_iterator>	&reverse_iterator<from_iterator>::operator+=(reverse_iterator<from_iterator>::difference_type n)
{
	this->r_it -= n;
	return (*this);
}

template<typename from_iterator>
reverse_iterator<from_iterator>	reverse_iterator<from_iterator>::operator-(reverse_iterator<from_iterator>::difference_type n) const
{
	return (this->r_it + n);
}

template<typename from_iterator>
reverse_iterator<from_iterator>	&reverse_iterator<from_iterator>::operator--()
{
	++(this->r_it);
	return (*this);
}

template<typename from_iterator>
reverse_iterator<from_iterator>	reverse_iterator<from_iterator>::operator--(int)
{
	reverse_iterator tmp = *this;
	++(this->r_it);
	return(tmp);
}

template<typename from_iterator>
reverse_iterator<from_iterator>	&reverse_iterator<from_iterator>::operator-=(reverse_iterator<from_iterator>::difference_type n)
{
	this->r_it += n;
	return (*this);
}

template<typename from_iterator>
bool operator == (const reverse_iterator<from_iterator> &lhs, const reverse_iterator<from_iterator> &rhs)
{
	return (lhs.base() == rhs.base());
}

template<typename from_iterator>
bool operator != (const reverse_iterator<from_iterator> &lhs, const reverse_iterator<from_iterator> &rhs)
{
	return (lhs.base() != rhs.base());
}

template<typename from_iterator>
bool operator < (const reverse_iterator<from_iterator> &lhs, const reverse_iterator<from_iterator> &rhs)
{
	return (lhs.base() > rhs.base());
}

template<typename from_iterator>
bool operator <= (const reverse_iterator<from_iterator> &lhs, const reverse_iterator<from_iterator> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template<typename from_iterator>
bool operator > (const reverse_iterator<from_iterator> &lhs, const reverse_iterator<from_iterator> &rhs)
{
	return (lhs.base() < rhs.base());
}

template<typename from_iterator>
bool operator >= (const reverse_iterator<from_iterator> &lhs, const reverse_iterator<from_iterator> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template<typename from_iterator> 
reverse_iterator<from_iterator> operator + (typename reverse_iterator<from_iterator>::difference_type n, const reverse_iterator<from_iterator> &it)
{
	return (it.base() - n);
}

template<typename from_iterator>
typename reverse_iterator<from_iterator>::difference_type operator - (const reverse_iterator<from_iterator> &lhs, const reverse_iterator<from_iterator> &rhs)
{
	return (rhs.base() - lhs.base());
}

template<typename lT, typename rT>
bool	operator==(const reverse_iterator<lT> &lhs, const reverse_iterator<rT> &rhs)
{
	return (lhs.base() == rhs.base());
}

template<typename lT, typename rT>
bool	operator!=(const reverse_iterator<lT> &lhs, const reverse_iterator<rT> &rhs)
{
	return (lhs.base() != rhs.base());
}

template<typename lT, typename rT>
bool	operator<(const reverse_iterator<lT> &lhs, const reverse_iterator<rT> &rhs)
{
	return (lhs.base() > rhs.base());
}

template<typename lT, typename rT>
bool	operator<=(const reverse_iterator<lT> &lhs, const reverse_iterator<rT> &rhs)
{
	return (lhs.base() >= rhs.base());
}

template<typename lT, typename rT>
bool	operator>(const reverse_iterator<lT> &lhs, const reverse_iterator<rT> &rhs)
{
	return (lhs.base() < rhs.base());
}

template<typename lT, typename rT>
bool	operator>=(const reverse_iterator<lT> &lhs, const reverse_iterator<rT> &rhs)
{
	return (lhs.base() <= rhs.base());
}

template<typename lT, typename rT>
typename reverse_iterator<lT>::difference_type operator-(const reverse_iterator<lT> &first, const reverse_iterator<rT> &second)
{
	return (second.base() - first.base());
}


// rb_tree_iterator:

template<typename T>
class Node;

template<typename T>
class rb_tree_iterator : public iterator<std::bidirectional_iterator_tag, T >
{
	public:
		
		typedef T												value_type;
		typedef typename std::ptrdiff_t							difference_type;
		typedef T*												pointer;
		typedef T&												reference;
		typedef typename ft::Node<T>							Node;

	private:
		
		Node													*ptr;

	public:

		rb_tree_iterator();
		
		rb_tree_iterator(Node *n_ptr);
		
		rb_tree_iterator(const rb_tree_iterator<T> &data);
		
		~rb_tree_iterator();

		rb_tree_iterator	&operator=(const rb_tree_iterator<T> &data);

		reference			operator*() const;
		pointer				operator->() const;

		rb_tree_iterator	&operator++(); // ++ptr
		rb_tree_iterator	&operator--(); // --ptr

		rb_tree_iterator	operator++(int); // ptr++
		rb_tree_iterator	operator--(int); // ptr--

		bool 				operator==(const rb_tree_iterator<T> &data) const;
		bool				operator!=(const rb_tree_iterator<T> &data) const;

		Node				*getptr() const;
	
};

template<typename T>
rb_tree_iterator<T>::rb_tree_iterator() : ptr(NULL)
{
	
}

template<typename T>
rb_tree_iterator<T>::rb_tree_iterator(Node *n_ptr) : ptr(n_ptr)
{
	
}

template<typename T>
rb_tree_iterator<T>::rb_tree_iterator(const rb_tree_iterator<T> &data) : ptr(data.getptr())
{
	
}

template<typename T>
rb_tree_iterator<T>::~rb_tree_iterator()
{
	
}

template<typename T>
rb_tree_iterator<T> &rb_tree_iterator<T>::operator=(const rb_tree_iterator<T> &data)
{
	if (this == &data)
		return (*this);
	this->ptr = data.ptr;
	return (*this);
}

template<typename T>
typename rb_tree_iterator<T>::reference rb_tree_iterator<T>::operator*() const
{
	return (*(this->ptr->value));
}

template<typename T>
typename rb_tree_iterator<T>::pointer rb_tree_iterator<T>::operator->() const
{
	return (this->ptr->value);
}

template<typename T>
rb_tree_iterator<T> &rb_tree_iterator<T>::operator++()
{
	Node			*tmp;
	Node			*prnt;

	tmp = this->getptr();
	if (tmp->right)
	{
		tmp = tmp->right;
		while (tmp->left != NULL)
			tmp = tmp->left;
		this->ptr = tmp;
	}
	else
	{
		prnt = tmp->parent;
		while ((prnt != NULL) && (tmp == prnt->right))
		{
			tmp = prnt;
			prnt = prnt->parent;
		}
		this->ptr = prnt;
	}
	return (*this);
}

template<typename T>
rb_tree_iterator<T> &rb_tree_iterator<T>::operator--()
{
	Node			*tmp;
	Node			*prnt;

	tmp = this->getptr();
	if (tmp->left)
	{
		tmp = tmp->left;
		while (tmp->right != NULL)
			tmp = tmp->right;
		this->ptr = tmp;
	}
	else
	{
		prnt = tmp->parent;
		while ((prnt != NULL) && (tmp == prnt->left))
		{
			tmp = prnt;
			prnt = prnt->parent;
		}
		this->ptr = prnt;
	}
	return (*this);
}

template<typename T>
rb_tree_iterator<T> rb_tree_iterator<T>::operator++(int)
{
	rb_tree_iterator tmp = *this;
	++(*this);
	return (tmp);
}

template<typename T>
rb_tree_iterator<T> rb_tree_iterator<T>::operator--(int)
{
	rb_tree_iterator tmp = *this;
	--(*this);
	return (tmp);
}

template<typename T>
bool	rb_tree_iterator<T>::operator==(const rb_tree_iterator<T> &data) const
{
	return (this->ptr == data.ptr);
}

template<typename T>
bool	rb_tree_iterator<T>::operator!=(const rb_tree_iterator<T> &data) const
{
	return (this->ptr != data.ptr);
}

template<typename T>
typename rb_tree_iterator<T>::Node *rb_tree_iterator<T>::getptr() const
{
	return (this->ptr);
}

// rb_tree_const_iterator:

template<typename T>
class rb_tree_const_iterator : public iterator<std::bidirectional_iterator_tag, T>
{
	public:
		
		typedef const T											value_type;
		typedef typename std::ptrdiff_t							difference_type;
		typedef const T*										pointer;
		typedef const T&										reference;
		typedef typename ft::Node<T>							Node;

	private:
		
		const Node												*ptr;

	public:
		
		rb_tree_const_iterator();

		rb_tree_const_iterator(Node *n_ptr);

		rb_tree_const_iterator(const rb_tree_const_iterator<T> &data);
		rb_tree_const_iterator(const rb_tree_iterator<T> &data);

		~rb_tree_const_iterator();

		rb_tree_const_iterator		&operator=(const rb_tree_const_iterator<T> &data);
		rb_tree_const_iterator		&operator=(const rb_tree_iterator<T> &data);

		reference					operator*() const;
		pointer						operator->() const;

		rb_tree_const_iterator		&operator++(); // ++ptr
		rb_tree_const_iterator		&operator--(); // --ptr

		rb_tree_const_iterator		operator++(int); // ptr++
		rb_tree_const_iterator		operator--(int); // ptr--

		bool 						operator==(const rb_tree_const_iterator<T> &data) const;
		bool						operator!=(const rb_tree_const_iterator<T> &data) const;

		const Node					*getptr() const;
		
};

template<typename T>
rb_tree_const_iterator<T>::rb_tree_const_iterator() : ptr(NULL)
{
	
}

template<typename T>
rb_tree_const_iterator<T>::rb_tree_const_iterator(Node *n_ptr) : ptr(n_ptr)
{
	
}

template<typename T>
rb_tree_const_iterator<T>::rb_tree_const_iterator(const rb_tree_const_iterator<T> &data) : ptr(data.getptr())
{
	
}

template<typename T>
rb_tree_const_iterator<T>::rb_tree_const_iterator(const rb_tree_iterator<T> &data) : ptr(data.getptr())
{
	
}

template<typename T>
rb_tree_const_iterator<T>::~rb_tree_const_iterator()
{
	
}

template<typename T>
rb_tree_const_iterator<T> &rb_tree_const_iterator<T>::operator=(const rb_tree_const_iterator<T> &data)
{
	if (this == &data)
		return (*this);
	this->ptr = data.getptr();
	return (*this);
}

template<typename T>
rb_tree_const_iterator<T> &rb_tree_const_iterator<T>::operator=(const rb_tree_iterator<T> &data)
{
	if (this == &data)
		return (*this);
	this->ptr = data.getptr();
	return (*this);
}

template<typename T>
typename rb_tree_const_iterator<T>::reference rb_tree_const_iterator<T>::operator*() const
{
	return (*(this->ptr->value));
}

template<typename T>
typename rb_tree_const_iterator<T>::pointer rb_tree_const_iterator<T>::operator->() const
{
	return (this->ptr->value);
}

template<typename T>
rb_tree_const_iterator<T> &rb_tree_const_iterator<T>::operator++()
{
	const Node			*tmp;
	const Node			*prnt;

	tmp = this->getptr();
	if (tmp->right)
	{
		tmp = tmp->right;
		while (tmp->left != NULL)
			tmp = tmp->left;
		this->ptr = tmp;
	}
	else
	{
		prnt = tmp->parent;
		while ((prnt != NULL) && (tmp == prnt->right))
		{
			tmp = prnt;
			prnt = prnt->parent;
		}
		this->ptr = prnt;
	}
	return (*this);
}

template<typename T>
rb_tree_const_iterator<T> &rb_tree_const_iterator<T>::operator--()
{
	const Node			*tmp;
	const Node			*prnt;

	tmp = this->getptr();
	if (tmp->left)
	{
		tmp = tmp->left;
		while (tmp->right != NULL)
			tmp = tmp->right;
		this->ptr = tmp;
	}
	else
	{
		prnt = tmp->parent;
		while ((prnt != NULL) && (tmp == prnt->left))
		{
			tmp = prnt;
			prnt = prnt->parent;
		}
		this->ptr = prnt;
	}
	return (*this);
}

template<typename T>
rb_tree_const_iterator<T> rb_tree_const_iterator<T>::operator++(int)
{
	rb_tree_const_iterator tmp = *this;
	++(*this);
	return (tmp);
}

template<typename T>
rb_tree_const_iterator<T> rb_tree_const_iterator<T>::operator--(int)
{
	rb_tree_const_iterator tmp = *this;
	--(*this);
	return (tmp);
}

template<typename T>
bool	rb_tree_const_iterator<T>::operator==(const rb_tree_const_iterator<T> &data) const
{
	return (this->ptr == data.ptr);
}

template<typename T>
bool	rb_tree_const_iterator<T>::operator!=(const rb_tree_const_iterator<T> &data) const
{
	return (this->ptr != data.ptr);
}

template<typename T>
const typename rb_tree_const_iterator<T>::Node *rb_tree_const_iterator<T>::getptr() const
{
	return (this->ptr);
}

}

#endif