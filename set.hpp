/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:38:00 by bchelste          #+#    #+#             */
/*   Updated: 2022/02/19 17:01:30 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "set_utils.hpp"

# include <memory>

namespace ft
{
	template<typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T> >
	class set
	{
		public:
			
			typedef T													key_type;
			typedef	T													value_type;
			typedef Compare                                        		key_compare;
			typedef Compare												value_compare;
			typedef	Allocator											allocator_type;
			typedef typename allocator_type::reference					reference;
			typedef typename allocator_type::const_reference			const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef ft::rb_tree_set_const_iterator<value_type>			iterator;
			typedef ft::rb_tree_set_const_iterator<value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef std::ptrdiff_t										difference_type;
			typedef std::size_t											size_type;
		
		private:
			
			ft::rb_tree_set<value_type, value_compare, allocator_type>	rbTree;
			key_compare													cmp;
			allocator_type												alloc;

		public:

			// constructors and destructor:

			explicit set(const key_compare &n_comp = key_compare(), const allocator_type &n_alloc = allocator_type());

			template<typename InputIterator>
			set(InputIterator first, InputIterator last, const key_compare &n_comp = key_compare(), const allocator_type &n_alloc = allocator_type());

			set(const set &data);

			~set();

			// operator = :

			set &operator=(const set &data);

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

			// modifiers:

			ft::pair<iterator, bool>		insert(const value_type &val);
			iterator						insert(iterator position, const value_type &val);
			template <class InputIterator>
			void							insert(InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value>::type* = 0);

			void							erase(iterator position);
			size_type						erase(const value_type &val);
			void							erase(iterator first, iterator last);

			void							swap(set &x);

			void							clear();

			// observers:

			key_compare						key_comp() const;

			value_compare					value_comp() const;

			// operations:

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

	template<typename T, typename Compare, typename Allocator>
	set<T, Compare, Allocator>::set(const key_compare &n_comp, const allocator_type &n_alloc) : rbTree(n_comp, n_alloc), cmp(n_comp), alloc(n_alloc)
	{
		
	}

	template<typename T, typename Compare, typename Allocator>
	template<typename InputIterator>
	set<T, Compare, Allocator>::set(InputIterator first, InputIterator last, const key_compare &n_comp, const allocator_type &n_alloc) : rbTree(n_comp, n_alloc), cmp(n_comp), alloc(n_alloc)
	{
		this->rbTree.insert(first, last);
	}

	template<typename T, typename Compare, typename Allocator>
	set<T, Compare, Allocator>::set(const set &data) : rbTree(data.rbTree), cmp(data.cmp), alloc(data.alloc)
	{
		
	}

	template<typename T, typename Compare, typename Allocator>
	set<T, Compare, Allocator>::~set()
	{
		
	}

	template<typename T, typename Compare, typename Allocator>
	set<T, Compare, Allocator> &set<T, Compare, Allocator>::operator=(const set &data)
	{
		if (this == &data)
			return (*this);
		this->cmp = data.cmp;
		this->alloc = data.alloc;
		this->rbTree = data.rbTree;
		return (*this);
	}

	// iterators:

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::iterator set<T, Compare, Allocator>::begin()
	{
		return (this->rbTree.begin());
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::const_iterator set<T, Compare, Allocator>::begin() const
	{
		return (this->rbTree.begin());
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::iterator set<T, Compare, Allocator>::end()
	{
		return (this->rbTree.end());
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::const_iterator set<T, Compare, Allocator>::end() const
	{
		return (this->rbTree.end());
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::reverse_iterator set<T, Compare, Allocator>::rbegin()
	{
		return (this->rbTree.rbegin());
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::const_reverse_iterator set<T, Compare, Allocator>::rbegin() const
	{
		return (this->rbTree.rbegin());
	}
	
	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::reverse_iterator set<T, Compare, Allocator>::rend()
	{
		return (this->rbTree.rend());
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::const_reverse_iterator set<T, Compare, Allocator>::rend() const
	{
		return (this->rbTree.rend());
	}

	// capacity:

	template<typename T, typename Compare, typename Allocator>
	bool set<T, Compare, Allocator>::empty() const
	{
		return (this->rbTree.empty());
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::size_type set<T, Compare, Allocator>::size() const
	{
		return (this->rbTree.get_size());
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::size_type set<T, Compare, Allocator>::max_size() const
	{
		return (this->rbTree.max_size());
	}

	// modifiers:

	template<typename T, typename Compare, typename Allocator>
	ft::pair<typename set<T, Compare, Allocator>::iterator, bool>		set<T, Compare, Allocator>::insert(const value_type &val)
	{
		return (this->rbTree.insert(val));
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::iterator set<T, Compare, Allocator>::insert(iterator position, const value_type &val)
	{
		return (this->rbTree.insert(position, val));
	}

	template<typename T, typename Compare, typename Allocator>
	template <class InputIterator> 
	void set<T, Compare, Allocator>::insert(InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value>::type*)
	{
		this->rbTree.insert(first, last);
	}

	template<typename T, typename Compare, typename Allocator>
	void set<T, Compare, Allocator>::erase(iterator position)
	{
		this->rbTree.erase(position);
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::size_type set<T, Compare, Allocator>::erase(const value_type &val)
	{
		return (this->rbTree.erase(val));
	}

	template<typename T, typename Compare, typename Allocator>
	void set<T, Compare, Allocator>::erase(iterator first, iterator last)
	{
		return (this->rbTree.erase(first, last));
	}

	template<typename T, typename Compare, typename Allocator>
	void set<T, Compare, Allocator>::swap(set &x)
	{
		this->rbTree.swap(x.rbTree);
	}

	template<typename T, typename Compare, typename Allocator>
	void set<T, Compare, Allocator>::clear()
	{
		this->rbTree.clear();
	}

	// observers:
	
	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::key_compare	set<T, Compare, Allocator>::key_comp() const
	{
		return (this->cmp);
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::value_compare set<T, Compare, Allocator>::value_comp() const
	{
		return (this->cmp);
	}
	
	// operations:

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::iterator set<T, Compare, Allocator>::find(const key_type &k)
	{
		return (this->rbTree.find(k)); 
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::const_iterator set<T, Compare, Allocator>::find(const key_type &k) const
	{
		return (this->rbTree.find(k));
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::size_type set<T, Compare, Allocator>::count(const key_type &k) const
	{
		return (this->rbTree.count(k));
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::iterator set<T, Compare, Allocator>::lower_bound(const key_type &k)
	{
		return (this->rbTree.lower_bound(k)); 
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::const_iterator set<T, Compare, Allocator>::lower_bound(const key_type &k) const
	{
		return (this->rbTree.lower_bound(k));
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::iterator set<T, Compare, Allocator>::upper_bound(const key_type &k)
	{
		return (this->rbTree.upper_bound(k)); 
	}

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::const_iterator set<T, Compare, Allocator>::upper_bound(const key_type &k) const
	{
		return (this->rbTree.upper_bound(k));
	}

	template<typename T, typename Compare, typename Allocator>
	ft::pair<typename set<T, Compare, Allocator>::iterator, typename set<T, Compare, Allocator>::iterator> set<T, Compare, Allocator>::equal_range(const key_type &k)
	{
		return (this->rbTree.equal_range(k));
	}

	template<typename T, typename Compare, typename Allocator>
	ft::pair<typename set<T, Compare, Allocator>::const_iterator, typename set<T, Compare, Allocator>::const_iterator> set<T, Compare, Allocator>::equal_range(const key_type &k) const
	{
		return (this->rbTree.equal_range(k));
	}

	// allocator:

	template<typename T, typename Compare, typename Allocator>
	typename set<T, Compare, Allocator>::allocator_type set<T, Compare, Allocator>::get_allocator() const
	{
		return (this->alloc);
	}

	// non-member functions:

	template<typename T, typename Compare, typename Allocator>
	bool operator==(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
	{
		return ((lhs.size() == rhs.size()) && (ft::equal(lhs.begin(), lhs.end(), rhs.begin())));
	}

	template<typename T, typename Compare, typename Allocator>
	bool operator!=(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
	{
		return (!(lhs == rhs));
	}

	template<typename T, typename Compare, typename Allocator>
	bool operator<(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template<typename T, typename Compare, typename Allocator>
	bool operator>(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
	{
		return (rhs < lhs);
	}

	template<typename T, typename Compare, typename Allocator>
	bool operator<=(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
	{
		return (!(rhs < lhs));
	}

	template<typename T, typename Compare, typename Allocator>
	bool operator>=(const set<T, Compare, Allocator> &lhs, const set<T, Compare, Allocator> &rhs)
	{
		return (!(lhs < rhs));
	}	

	template<typename T, typename Compare, typename Allocator>
	void swap(set<T, Compare, Allocator> &x, set<T, Compare, Allocator> &y)
	{
		x.swap(y);
	}
	
}

#endif