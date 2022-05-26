/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:16:02 by bchelste          #+#    #+#             */
/*   Updated: 2022/02/15 20:18:17 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "iterators.hpp"
# include "reimplement.hpp"
# include "rb_tree.hpp"

# include <memory>
# include <iostream>

namespace ft
{
	template<typename Key, typename T, typename Compare = std::less<Key>, typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef ft::pair<const key_type, mapped_type>				value_type;
			typedef Compare												key_compare;
			typedef Allocator											allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef ft::rb_tree_iterator<value_type>					iterator;
			typedef ft::rb_tree_const_iterator<value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef std::ptrdiff_t										difference_type;
			typedef std::size_t											size_type;

		private:

			class value_compare
			{
				
				protected:
				
					Compare comp;
					
				public:
				
					value_compare (Compare c) : comp(c) {}
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type &x, const value_type &y) const { return comp(x.first, y.first); }
			};
			
			ft::rb_tree<value_type, value_compare, allocator_type>		rbTree;
			key_compare													cmp;
			allocator_type												alloc;

		public:

			// constructors and destructor:

			explicit map(const key_compare &n_comp = key_compare(), const allocator_type &n_alloc = allocator_type());
			
			template<typename InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &n_comp = key_compare(), const allocator_type &n_alloc = allocator_type());
			
			map(const map &data);

			~map();

			// operator= :

			map &operator=(const map &data);

			// iterators:

			iterator						begin();
			const_iterator					begin() const;
			
			iterator						end();
			const_iterator					end() const;

			reverse_iterator				rbegin();
			const_reverse_iterator			rbegin() const;

			reverse_iterator				rend();
			const_reverse_iterator			rend() const;

			// capacity:

			bool							empty() const;

			size_type						size() const;

			size_type						max_size() const;

			// element access:

			mapped_type 					&operator[](const key_type &k);

			// modifiers:

			ft::pair<iterator, bool>		insert(const value_type &val);
			iterator						insert(iterator position, const value_type &val);
			template <class InputIterator>
			void							insert(InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value>::type* = 0);
			
			void							erase(iterator position);
			size_type						erase(const Key &key);
			void							erase(iterator first, iterator last);

			void							swap(map &x);

			void							clear();

			// observers:

			key_compare						key_comp() const;

			value_compare					value_comp() const;

			//operations:

			iterator						find(const key_type &k);
			const_iterator					find(const key_type &k) const;

			size_type						count(const key_type &k) const;

			iterator						lower_bound(const key_type &k);
			const_iterator					lower_bound(const key_type &k) const;

			iterator						upper_bound(const key_type &k);
			const_iterator					upper_bound(const key_type &k) const;

			ft::pair<iterator, iterator>				equal_range(const key_type &k);
			ft::pair<const_iterator, const_iterator>	equal_range(const key_type &k) const;

			// allocator:

			allocator_type					get_allocator() const;

	};

	template<typename Key, typename T, typename Compare, typename Allocator>
	map<Key, T, Compare, Allocator>::map(const key_compare &n_comp, const allocator_type &n_alloc) : rbTree(n_comp, n_alloc), cmp(n_comp), alloc(n_alloc)
	{
		
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	template<typename InputIterator>
	map<Key, T, Compare, Allocator>::map(InputIterator first, InputIterator last, const key_compare &n_comp, const allocator_type &n_alloc) : rbTree(n_comp, n_alloc), cmp(n_comp), alloc(n_alloc)
	{
		this->rbTree.insert(first, last);
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	map<Key, T, Compare, Allocator>::map(const map &data) : rbTree(data.rbTree), cmp(data.cmp), alloc(data.alloc)
	{

	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	map<Key, T, Compare, Allocator>::~map()
	{
		
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	map<Key, T, Compare, Allocator> &map<Key, T, Compare, Allocator>::operator=(const map &data)
	{
		if (this == &data)
			return (*this);
		this->cmp = data.cmp;
		this->alloc = data.alloc;
		this->rbTree = data.rbTree;
		return (*this);
	}

	// iterators:

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::begin()
	{
		return (this->rbTree.begin());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::begin() const
	{
		return (this->rbTree.begin());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::end()
	{
		return (this->rbTree.end());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::end() const
	{
		return (this->rbTree.end());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::reverse_iterator map<Key, T, Compare, Allocator>::rbegin()
	{
		return (this->rbTree.rbegin());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::const_reverse_iterator map<Key, T, Compare, Allocator>::rbegin() const
	{
		return (this->rbTree.rbegin());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::reverse_iterator map<Key, T, Compare, Allocator>::rend()
	{
		return (this->rbTree.rend());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::const_reverse_iterator map<Key, T, Compare, Allocator>::rend() const
	{
		return (this->rbTree.rend());
	}

	// capacity:

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool map<Key, T, Compare, Allocator>::empty() const
	{
		return (this->rbTree.empty());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::size_type map<Key, T, Compare, Allocator>::size() const
	{
		return (this->rbTree.get_size());
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::size_type map<Key, T, Compare, Allocator>::max_size() const
	{
		return (this->rbTree.max_size());
	}

	// element access:

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::mapped_type &map<Key, T, Compare, Allocator>::operator[](const key_type &k)
	{
		return ((((this->insert(ft::make_pair(k, mapped_type()))).first))->second);
	}

	// modifiers:
	
	template<typename Key, typename T, typename Compare, typename Allocator>
	ft::pair<typename map<Key, T, Compare, Allocator>::iterator, bool>		map<Key, T, Compare, Allocator>::insert(const value_type &val)
	{
		return (this->rbTree.insert(val));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::insert(iterator position, const value_type &val)
	{
		return (this->rbTree.insert(position, val));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	template <class InputIterator> 
	void map<Key, T, Compare, Allocator>::insert(InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value>::type*)
	{
		this->rbTree.insert(first, last);
	}
	
	template<typename Key, typename T, typename Compare, typename Allocator>
	void map<Key, T, Compare, Allocator>::erase(iterator position)
	{
		this->rbTree.erase(position);
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::size_type map<Key, T, Compare, Allocator>::erase(const Key &key)
	{
		return (this->rbTree.erase(ft::make_pair(key, mapped_type())));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	void map<Key, T, Compare, Allocator>::erase(iterator first, iterator last)
	{
		return (this->rbTree.erase(first, last));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	void map<Key, T, Compare, Allocator>::swap(map &x)
	{
		this->rbTree.swap(x.rbTree);
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	void map<Key, T, Compare, Allocator>::clear()
	{
		this->rbTree.clear();
	}

	// observers:

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::key_compare	map<Key, T, Compare, Allocator>::key_comp() const
	{
		return (this->cmp);
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::value_compare map<Key, T, Compare, Allocator>::value_comp() const
	{
		return (value_compare(key_compare()));
	}

	// operations:

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::find(const key_type &k)
	{
		return (this->rbTree.find(ft::make_pair(k, mapped_type()))); 
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::find(const key_type &k) const
	{
		return (this->rbTree.find(ft::make_pair(k, mapped_type())));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::size_type map<Key, T, Compare, Allocator>::count(const key_type &k) const
	{
		return (this->rbTree.count(ft::make_pair(k, mapped_type())));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::lower_bound(const key_type &k)
	{
		return (this->rbTree.lower_bound(ft::make_pair(k, mapped_type()))); 
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::lower_bound(const key_type &k) const
	{
		return (this->rbTree.lower_bound(ft::make_pair(k, mapped_type())));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::iterator map<Key, T, Compare, Allocator>::upper_bound(const key_type &k)
	{
		return (this->rbTree.upper_bound(ft::make_pair(k, mapped_type()))); 
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::upper_bound(const key_type &k) const
	{
		return (this->rbTree.upper_bound(ft::make_pair(k, mapped_type())));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	ft::pair<typename map<Key, T, Compare, Allocator>::iterator, typename map<Key, T, Compare, Allocator>::iterator> map<Key, T, Compare, Allocator>::equal_range(const key_type &k)
	{
		return (this->rbTree.equal_range(ft::make_pair(k, mapped_type())));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	ft::pair<typename map<Key, T, Compare, Allocator>::const_iterator, typename map<Key, T, Compare, Allocator>::const_iterator> map<Key, T, Compare, Allocator>::equal_range(const key_type &k) const
	{
		return (this->rbTree.equal_range(ft::make_pair(k, mapped_type())));
	}
	
	// allocator:

	template<typename Key, typename T, typename Compare, typename Allocator>
	typename map<Key, T, Compare, Allocator>::allocator_type map<Key, T, Compare, Allocator>::get_allocator() const
	{
		return (this->alloc);
	}

	// non-member functions:

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator==(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return ((lhs.size() == rhs.size()) && (ft::equal(lhs.begin(), lhs.end(), rhs.begin())));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(lhs == rhs));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator<(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator>(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (rhs < lhs);
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(rhs < lhs));
	}

	template<typename Key, typename T, typename Compare, typename Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(lhs < rhs));
	}	

	template<typename Key, typename T, typename Compare, typename Allocator>
	void swap(map<Key, T, Compare, Allocator> &x, map<Key, T, Compare, Allocator> &y)
	{
		x.swap(y);
	}
	
}

#endif 