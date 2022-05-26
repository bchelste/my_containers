/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 21:23:20 by bchelste          #+#    #+#             */
/*   Updated: 2022/02/19 17:08:26 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_UTILS_HPP
# define SET_UTILS_HPP

# define RED_NODE 0
# define BLACK_NODE 1

# include <memory>
# include <iostream>

# include "iterators.hpp"
# include "reimplement.hpp"
# include "rb_tree.hpp"

namespace ft
{
	template<typename T>
	class rb_tree_set_iterator;
	
	template<typename T>
	class rb_tree_set_const_iterator;

	// rb_tree_set for set:

	template<typename T, typename Compare, typename Allocator = std::allocator<T> >
	class rb_tree_set
	{
		
		public:
			
			typedef	T																value_type;
			typedef Compare															value_compare;
			typedef Allocator														alloc_type;
			typedef typename alloc_type::template rebind<Node<value_type> >::other	alloc_node;
			typedef typename alloc_node::pointer									pointer;
			typedef typename alloc_node::const_pointer								const_pointer;
			typedef typename alloc_node::reference									reference;
			typedef typename alloc_node::const_reference							const_reference;
			typedef ft::rb_tree_set_iterator<value_type>							iterator;
			typedef ft::rb_tree_set_const_iterator<value_type>						const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							reverse_const_iterator;
			typedef typename alloc_type::size_type									size_type;
			typedef typename alloc_type::difference_type							difference_type;

		private:

			size_type												size;
			value_compare											compare;
			pointer													finish;
			pointer													root;
			pointer													start;
			alloc_node												al_node;

		public:

			// constructors and destructor:
			
			rb_tree_set(const value_compare &n_compare, const alloc_type &n_alloc);
			rb_tree_set(const rb_tree_set &data);
			~rb_tree_set();
			
			rb_tree_set &operator=(const rb_tree_set &data);

			// iterators methods:

			iterator				begin();
			const_iterator			begin() const;

			iterator				end();
			const_iterator			end() const;

			reverse_iterator		rbegin();
			reverse_const_iterator	rbegin() const;

			reverse_iterator		rend();
			reverse_const_iterator	rend() const;

			// capacity methods:

			bool					empty() const;

			size_type				max_size() const;

			size_type				get_size() const;

			// modifiers

			ft::pair<iterator, bool>	insert(const value_type &val);
			iterator					insert(iterator position, const value_type &val);
			template <class InputIterator>
			void						insert(InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value>::type* = 0);

			void						erase(iterator position);
			size_type					erase(const value_type &key);
			void						erase(iterator first, iterator last);

			void						swap(rb_tree_set &data);

			void						clear();

			// operations:

			iterator					find(const value_type &k);
			const_iterator				find(const value_type &k) const;

			size_type					count(const value_type &k) const;

			iterator					lower_bound(const value_type &k);
			const_iterator				lower_bound(const value_type &k) const;

			iterator					upper_bound(const value_type &k);
			const_iterator				upper_bound(const value_type &k) const;

			ft::pair<iterator, iterator>				equal_range(const value_type &k);
			ft::pair<const_iterator, const_iterator>	equal_range(const value_type &k) const;

		private:

			pointer				nil_node();
			
			void				dealloc_node(pointer x);

			pointer				clone(pointer x);

			pointer				search_min(pointer x);

			pointer				search_max(pointer x);

			void				set_start();

			void				set_finish();

			pointer				search_key(const value_type &k) const;

			pointer				search_key_from(const value_type &k, pointer from) const;

			void				replacement(pointer r_parent, pointer old_child, pointer new_child);
			
			pointer				del_node(pointer x);
			
			void				erase_node(const value_type &k);
								
			void				left_rotate(pointer	x);
			
			void				right_rotate(pointer x);
			
			void				balance_insert(pointer x);

			pointer				get_brother(pointer x);

			void				balance_erase(pointer x);
	
	};

	template<typename T, typename Compare, typename Allocator>
	rb_tree_set<T, Compare, Allocator>::rb_tree_set(const value_compare &n_compare, const alloc_type &n_alloc) : size(0), compare(n_compare), finish(nil_node()), root(this->finish), start(nil_node()), al_node(n_alloc)
	{
		
	}

	template<typename T, typename Compare, typename Allocator>
	rb_tree_set<T, Compare, Allocator>::rb_tree_set(const rb_tree_set &data) : compare(data.compare), finish(nil_node()), start(nil_node()), al_node(data.al_node)
	{
		*this = data;
	}

	template<typename T, typename Compare, typename Allocator>
	rb_tree_set<T, Compare, Allocator>::~rb_tree_set()
	{
		if (this->root != this->finish)
		{
			this->dealloc_node(this->root);
			this->finish = NULL;
			this->start = NULL;
		}
	
		if (this->finish)
		{
			this->al_node.destroy(this->finish);
			this->al_node.deallocate(this->finish, 1);
			this->finish = NULL;
		}
		if (this->start)
		{
			this->al_node.destroy(this->start);
			this->al_node.deallocate(this->start, 1);
			this->start = NULL;
		}
	
	}

	template<typename T, typename Compare, typename Allocator>
	rb_tree_set<T, Compare, Allocator> &rb_tree_set<T, Compare, Allocator>::operator=(const rb_tree_set &data)
	{


		if (this == &data)
			return (*this);
		this->al_node = data.al_node;
		this->compare = data.compare;
		this->size = data.size;
		if (data.empty())
		{
			this->root = this->finish;
			this->start = this->finish;
		}
		else
		{
			pointer tmp_start;
			pointer tmp_finish;
		
			if (data.finish->parent != NULL)
			{	
				tmp_finish = data.finish->parent->right;
				data.finish->parent->right = NULL;
			}
		
			if (data.start->parent != NULL)
			{
				tmp_start = data.start->parent->left;
				data.start->parent->left = NULL;
			}
			this->root = clone(data.root);
		
			if (data.finish->parent != NULL)
				data.finish->parent->right = tmp_finish;
			
			if (data.start->parent != NULL)
				data.start->parent->left = tmp_start;	

			this->set_finish();
			this->set_start();
		}
		return (*this);	
		
	}

	// iterators:

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::iterator rb_tree_set<T, Compare, Allocator>::begin()
	{
		if (this->empty())
			return (iterator(this->finish));
		return (iterator(this->start->parent));	
		
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::const_iterator rb_tree_set<T, Compare, Allocator>::begin() const
	{
		if (this->empty())
			return (iterator(this->finish));
		return (iterator(this->start->parent));	
		
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::iterator rb_tree_set<T, Compare, Allocator>::end()
	{
		return (iterator(this->finish));
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::const_iterator rb_tree_set<T, Compare, Allocator>::end() const
	{
		return (const_iterator(this->finish));
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::reverse_iterator rb_tree_set<T, Compare, Allocator>::rbegin()
	{
		return (reverse_iterator(this->end()));
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::reverse_const_iterator rb_tree_set<T, Compare, Allocator>::rbegin() const
	{
		return (reverse_const_iterator(this->end()));
	}
	
	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::reverse_iterator rb_tree_set<T, Compare, Allocator>::rend()
	{
		return (reverse_iterator(this->begin()));
	}
	
	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::reverse_const_iterator rb_tree_set<T, Compare, Allocator>::rend() const
	{
		return (reverse_const_iterator(this->begin()));
	}

	// capacity methods:
	
	template<typename T, typename Compare, typename Allocator>
	bool rb_tree_set<T, Compare, Allocator>::empty() const
	{
		if (this->size == 0)
			return (true);
		return (false);
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::size_type rb_tree_set<T, Compare, Allocator>::max_size() const
	{
		return (this->al_node.max_size());
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::size_type rb_tree_set<T, Compare, Allocator>::get_size() const
	{
		return (this->size);
	}

	// modefiers:
	
	template<typename T, typename Compare, typename Allocator>
	ft::pair<typename rb_tree_set<T, Compare, Allocator>::iterator, bool> rb_tree_set<T, Compare, Allocator>::insert(const value_type &val)
	{
		if (finish->parent != NULL)
			this->finish->parent->right = NULL;
			
		if (start->parent != NULL)
			this->start->parent->left = NULL;

		pointer	insert_node = this->al_node.allocate(1);
		this->al_node.construct(insert_node, Node<value_type>(val, RED_NODE));
		pointer	current = this->root;
		pointer	tmp_parent = NULL;

		while(current != NULL)
		{
			if ((!current->left) && (!current->right) && (!current->value))
				break;

			tmp_parent = current;

			if (this->compare(*(insert_node->value), *(current->value)))
			{
				current = current->left;
			}
			else if (this->compare(*(current->value), *(insert_node->value)))
			{			
				current = current->right;
			}
			else
			{	
				this->al_node.destroy(insert_node);
				this->al_node.deallocate(insert_node, 1);
				this->set_finish();
				this->set_start();
				return (ft::make_pair(iterator(current), false));
			}	
		}

		insert_node->parent = tmp_parent;
		if (tmp_parent == NULL)
		{
			this->root = insert_node;
		}
		else if (this->compare(*(insert_node->value), *(tmp_parent->value)))
		{
			tmp_parent->left = insert_node;
		}
		else
		{
			tmp_parent->right = insert_node;
		}

		this->balance_insert(insert_node);
		this->size += 1;

		this->set_finish();
		this->set_start();

		return (ft::make_pair(iterator(insert_node), true));
	
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::iterator rb_tree_set<T, Compare, Allocator>::insert(iterator position, const value_type &val)
	{
		iterator next_pos = position;
		++next_pos;
		
		if ((position != iterator(this->finish)) && (val < *next_pos) && (val > *position))
		{
			
			if (position.getptr()->right == NULL)
			{
				pointer	insert_node = this->al_node.allocate(1);
				this->al_node.construct(insert_node, Node<value_type>(val, RED_NODE));
				
				position.getptr()->right = insert_node;
				insert_node->parent = position.getptr();
				this->balance_insert(insert_node);
				this->size += 1;
				this->set_finish();
				this->set_start();
				return (iterator(insert_node));	
			}	
		}
		ft::pair<iterator, bool> tmp = this->insert(val);
		return (tmp.first);
	}

	template<typename T, typename Compare, typename Allocator>
	template <class InputIterator>
	void rb_tree_set<T, Compare, Allocator>::insert(InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value>::type*)
	{

		while (first != last)
		{
			
			this->insert(*first);
			++first;

		}
	}

	template<typename T, typename Compare, typename Allocator>
	void	rb_tree_set<T, Compare, Allocator>::erase(iterator position)
	{
		this->erase_node(*position);
		this->set_start();
		this->set_finish();
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::size_type rb_tree_set<T, Compare, Allocator>::erase(const value_type &key)
	{

		size_type tmp;
		
		tmp = this->size;
		
		this->erase_node(key);
		this->set_start();
		this->set_finish();

		if (tmp == this->size)
			return (0);
		return (1);
	}

	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::erase(iterator first, iterator last)
	{
		iterator old_first = first;
		if ((first == this->begin()) && (last == this->end()))
		{
			this->clear();
			return ;
		}

		int nbr = 0;
		while (first != last)
		{
			++first;
			++nbr;
		}

		int erase_pos = 0;
		for(iterator it = this->begin(); it != old_first; ++it)
			++erase_pos;
		
		iterator pos = this->begin();

		for (int j = 0; j < nbr; ++j)
		{
			for (int i = 0; i < erase_pos; ++i)
				++pos;
			this->erase(*pos);
			pos = this->begin();
		}
	}
	
	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::swap(rb_tree_set &data)
	{
		size_type 	tmp_size;
		pointer		tmp_ptr;

		tmp_size = this->size;
		this->size = data.size;
		data.size = tmp_size;

		tmp_ptr = this->root;
		this->root = data.root;
		data.root = tmp_ptr;

		tmp_ptr = this->finish;
		this->finish = data.finish;
		data.finish = tmp_ptr;

		tmp_ptr = this->start;
		this->start = data.start;
		data.start = tmp_ptr;
	}

	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::clear()
	{
		rb_tree_set<T,Compare, Allocator> empty_tree(this->compare, this->al_node);
		empty_tree.swap(*this);
	}

	// operators:

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::iterator rb_tree_set<T, Compare, Allocator>::find(const value_type &k)
	{
		pointer tmp;

		tmp = this->search_key(k);
		if (tmp == NULL)
			return (this->end());
		return (iterator(tmp));
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::const_iterator rb_tree_set<T, Compare, Allocator>::find(const value_type &k) const
	{
		pointer tmp;

		tmp = this->search_key(k);
		if (tmp == NULL)
			return (this->end());
		return (const_iterator(tmp));
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::size_type		rb_tree_set<T, Compare, Allocator>::count(const value_type &k) const
	{
		size_type res = 0;
		pointer tmp = this->search_key(k);
		if (tmp != NULL)
			res = 1;
		return (res);
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::iterator rb_tree_set<T, Compare, Allocator>::lower_bound(const value_type &k)
	{
		iterator it_begin = this->begin();
		iterator it_end = this->end();

		while (it_begin != it_end)
		{
			if (this->compare((*it_begin), k))
				++it_begin;
			else
				break ;
		}
		return (it_begin);
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::const_iterator rb_tree_set<T, Compare, Allocator>::lower_bound(const value_type &k) const
	{
		const_iterator it_begin = this->begin();
		const_iterator it_end = this->end();

		while (it_begin != it_end)
		{
			if (this->compare((*it_begin), k))
				++it_begin;
			else
				break ;
		}
		return (it_begin);
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::iterator rb_tree_set<T, Compare, Allocator>::upper_bound(const value_type &k)
	{
		iterator it_begin = this->begin();
		iterator it_end = this->end();

		while (it_begin != it_end)
		{
			if (this->compare(k, (*it_begin)))
				break ;
			++it_begin;
		}
		return (it_begin);
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::const_iterator rb_tree_set<T, Compare, Allocator>::upper_bound(const value_type &k) const
	{
		const_iterator it_begin = this->begin();
		const_iterator it_end = this->end();

		while (it_begin != it_end)
		{
			if (this->compare(k, (*it_begin)))
				break ;
			++it_begin;
		}
		return (it_begin);
	}

	template<typename T, typename Compare, typename Allocator>
	ft::pair<typename rb_tree_set<T, Compare, Allocator>::iterator, typename rb_tree_set<T, Compare, Allocator>::iterator> rb_tree_set<T, Compare, Allocator>::equal_range(const value_type &k)
	{
		return (ft::pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
	}
	
	template<typename T, typename Compare, typename Allocator>
	ft::pair<typename rb_tree_set<T, Compare, Allocator>::const_iterator, typename rb_tree_set<T, Compare, Allocator>::const_iterator> rb_tree_set<T, Compare, Allocator>::equal_range(const value_type &k) const
	{
		return (ft::pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k)));
	}

	//////--------//////
	
	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::pointer rb_tree_set<T, Compare, Allocator>::nil_node()
	{
		pointer	tmp = this->al_node.allocate(1);
		
		this->al_node.construct(tmp, Node<value_type>());
		return (tmp);
	}

	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::dealloc_node(pointer x)
	{
		if (x == NULL)
			return;
		this->dealloc_node(x->left);
		this->dealloc_node(x->right);
		this->al_node.destroy(x);
		this->al_node.deallocate(x, 1);
		--this->size;
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::pointer rb_tree_set<T, Compare, Allocator>::clone(pointer x)
	{
		
		if (x == NULL)
			return (NULL);
		if ((x->left == NULL) && (x->right == NULL) && (x->value == NULL))
			return (NULL);
			
		pointer tmp = this->al_node.allocate(1);
		this->al_node.construct(tmp, Node<value_type>(*x));
		
		tmp->left = clone(x->left);
		if (tmp->left != NULL)
			tmp->left->parent = tmp;
			
		tmp->right = clone(x->right);
		if (tmp->right != NULL)
			tmp->right->parent = tmp;

		return (tmp);
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::pointer rb_tree_set<T, Compare, Allocator>::search_min(pointer x)
	{
		if (x == NULL)
			return (NULL);
		while ((x->left != NULL) && (x->left->value != NULL))
			x = x->left;
		return (x);
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::pointer rb_tree_set<T, Compare, Allocator>::search_max(pointer x)
	{
		if (x == NULL)
			return (NULL);
		while ((x->right != NULL) && (x->right->value != NULL))
			x = x->right;
		return (x);
	}

	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::set_start()
	{
		if (this->empty())
		{
			return ;
		}
		pointer new_first = this->search_min(this->root);
		new_first->left = this->start;
		this->start->parent = new_first;
		
	}
	
	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::set_finish()
	{
		if (this->empty())
		{
			return ;
		}
		pointer new_last = this->search_max(this->root);
		new_last->right = this->finish;
		this->finish->parent = new_last;
		
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::pointer rb_tree_set<T, Compare, Allocator>::search_key(const value_type &k) const
	{
		return (this->search_key_from(k, this->root));
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::pointer rb_tree_set<T, Compare, Allocator>::search_key_from(const value_type &k, pointer from) const
	{
		if ((from == NULL) || (from->value == NULL))
			return (NULL);
		if (this->compare(k, (*(from->value))))
			return (this->search_key_from(k, from->left));
		if (this->compare((*(from->value)), k))
			return (this->search_key_from(k, from->right));
		return (from);
	}

	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::erase_node(const value_type &k)
	{

		if (finish->parent != NULL)
			this->finish->parent->right = NULL;
		
		if (start->parent != NULL)
			this->start->parent->left = NULL;
		
		
		pointer			victim;
		pointer			tmp;
		unsigned int	tmp_color;
		pointer			mn_rght;
		value_type		*val;

		victim = this->search_key(k);
				
		if (victim == NULL)
			return ;
		tmp = NULL;
		
		if ((victim->left == NULL) || (victim->right == NULL))
		{
			tmp = this->del_node(victim);
			tmp_color = victim->color;
			victim->alloc.destroy(victim->value);
			victim->alloc.deallocate(victim->value, 1);
			this->al_node.deallocate(victim, 1);
		}
		else
		{
			mn_rght = this->search_min(victim->right);
			val = mn_rght->value;
			tmp = del_node(mn_rght);
			tmp_color = mn_rght->color;
			victim->alloc.destroy(victim->value);
			victim->alloc.deallocate(victim->value, 1);
			victim->value = val;
			this->al_node.deallocate(mn_rght, 1);
		}
		
		if ((tmp_color == BLACK_NODE) && (this->root != this->finish))
		{
			
			this->balance_erase(tmp);			// remove nil node after erase
			if (tmp->value == NULL)
			{
				this->replacement(tmp->parent, tmp, NULL);
				this->al_node.deallocate(tmp, 1);
			}
		}
		
		this->size -= 1;

		this->set_finish();
		this->set_start();
	}
	
	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::left_rotate(pointer x)
	{
		pointer tmp_parent;
		pointer right_child;

		tmp_parent = x->parent;
		right_child = x->right;
		x->right = right_child->left;
		if (right_child->left != NULL)
			right_child->left->parent = x;
		right_child->left = x;
		x->parent = right_child;
		this->replacement(tmp_parent, x, right_child);
	}

	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::right_rotate(pointer x)
	{
		pointer tmp_parent;
		pointer left_child;

		tmp_parent = x->parent;
		left_child = x->left;
		x->left = left_child->right;
		if (left_child->right != NULL)
			left_child->right->parent = x;
		left_child->right = x;
		x->parent = left_child;
		this->replacement(tmp_parent, x, left_child);
	}

	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::replacement(pointer r_parent, pointer old_child, pointer new_child)
	{
		if (r_parent == NULL)
			this->root = new_child;
		else if (r_parent->left == old_child)
			r_parent->left = new_child;
		else if (r_parent->right == old_child)
			r_parent->right = new_child;
		
		if (new_child != NULL)
			new_child->parent = r_parent;
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::pointer rb_tree_set<T, Compare, Allocator>::del_node(pointer x)
	{
		if (x->left != NULL)
		{
			this->replacement(x->parent, x, x->left);
			return (x->left);
		}
		else if (x->right != NULL)
		{
			this->replacement(x->parent, x, x->right);
			return (x->right);
		}
		else
		{
			pointer new_child = NULL;
			if (x->color == BLACK_NODE)
				new_child = this->nil_node();
			this->replacement(x->parent, x, new_child);
			return (new_child);
		}
		return (NULL);
	}

	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::balance_insert(pointer x)
	{
		// Case 1: parent == NULL, it is root and the end of recursion
		pointer	father = x->parent;
		if (father == NULL)
		{
			x->color = BLACK_NODE;
			return ;
		}

		// Case 2: black roots
		if (father->color == BLACK_NODE)	// parent->color = black => do nothing
			{
			
			return ;
			}
		
		// Case 3:
		pointer grandpa = father->parent;
		pointer	uncle = NULL;

		if (grandpa->left == father)
			uncle = grandpa->right;
		else if (grandpa->right == father)
			uncle = grandpa->left;
		
		// uncle->color == red => father, uncle, grandpa become recolored
		if ((uncle != NULL) && (uncle->color == RED_NODE))
		{
			father->color = BLACK_NODE;
			uncle->color = BLACK_NODE;
			grandpa->color = RED_NODE;
			this->balance_insert(grandpa); // recursion for red grandpa ... (till the root)
		}
		else if (father == grandpa->left)  // father is left child
		{
			
		// Case 4.1: uncle->colour == black	and x == grandpa->left->right
			if (x == father->right)
			{
				this->left_rotate(father); // 
				father = x;
			}
		// Case 5.1: uncle->colour == black and x == grandpa->left->left
			this->right_rotate(grandpa);
			
		// recolour
			father->color = BLACK_NODE;
			grandpa->color = RED_NODE;
		}
		else								// father is right child
		{

		// Case 4.2: uncle->colour == black and x == grandpa->right->left
			if (x == father->left)
			{
				this->right_rotate(father);
				father = x;
			}
		// Case 5.2: uncle->colour == black and x == grandpa->right->right
			this->left_rotate(grandpa);
			
		// recolour
			father->color = BLACK_NODE;
			grandpa->color = RED_NODE;
		}
	}

	template<typename T, typename Compare, typename Allocator>
	typename rb_tree_set<T, Compare, Allocator>::pointer rb_tree_set<T, Compare, Allocator>::get_brother(pointer x)
	{
		pointer father = x->parent;
		
		if (x == father->left)
			return (father->right);
		else if (x == x->parent->right)
			return (father->left);
		return (NULL);
	}
	
	template<typename T, typename Compare, typename Allocator>
	void rb_tree_set<T, Compare, Allocator>::balance_erase(pointer x)
	{
		if (x == this->root)
		{
			x->color = BLACK_NODE;
			return ;
		}
		
		pointer brother = get_brother(x);
		// Case 2: red brother
		if (brother->color == RED_NODE)
		{
			// recolor
			brother->color = BLACK_NODE;
			x->parent->color = RED_NODE;
			// rotate
			if (x == x->parent->left)
				this->left_rotate(x->parent);
			else
				this->right_rotate(x->parent);
			
			brother = get_brother(x);
		}
		
		// Black brother with two black children
		if (((brother->left == NULL) || (brother->left->color == BLACK_NODE)) &&
			((brother->right == NULL) || (brother->right->color == BLACK_NODE)))
		{
			brother->color = RED_NODE;

		// Case 3: black brother with two black children and red father
			if (x->parent->color == RED_NODE)
				x->parent->color = BLACK_NODE;
		// Case 4: black brother with two black children and black father
			else
				this->balance_erase(x->parent);
		}
		else
		{	
		// Case 5: black brother with at least one red child and father->left black
			if ((x == x->parent->left) &&
				((brother->right == NULL) || (brother->right->color == BLACK_NODE)))
			{
				brother->left->color = BLACK_NODE;
				brother->color = RED_NODE;
				this->right_rotate(brother);
				brother = x->parent->right;
			}
			else if ((x != x->parent->left) &&
				((brother->left == NULL) || (brother->left->color == BLACK_NODE)))
			{
				brother->right->color = BLACK_NODE;
				brother->color = RED_NODE;
				this->left_rotate(brother);
				brother = x->parent->left;
			}

		// Case 6: black brother with at least one red child and father->left red
			brother->color = x->parent->color;
			x->parent->color = BLACK_NODE;
			if (x == x->parent->left)
			{
				brother->right->color = BLACK_NODE;
				this->left_rotate(x->parent);
			}
			else
			{
				brother->left->color = BLACK_NODE;
				this->right_rotate(x->parent);
			}
		}
	}

	// rb_tree_set_iterator for set:
	
	template<typename T>
	class rb_tree_set_iterator : public iterator<std::bidirectional_iterator_tag, T >
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

			rb_tree_set_iterator();
		
			rb_tree_set_iterator(Node *n_ptr);
		
			rb_tree_set_iterator(const rb_tree_set_iterator<T> &data);
		
			rb_tree_set_iterator(const rb_tree_set_const_iterator<T> &data);
		
			~rb_tree_set_iterator();

			rb_tree_set_iterator	&operator=(const rb_tree_set_iterator<T> &data);

			reference				operator*() const;
			pointer					operator->() const;

			rb_tree_set_iterator	&operator++(); // ++ptr
			rb_tree_set_iterator	&operator--(); // --ptr

			rb_tree_set_iterator	operator++(int); // ptr++
			rb_tree_set_iterator	operator--(int); // ptr--

			bool 					operator==(const rb_tree_set_iterator<T> &data) const;
			bool					operator!=(const rb_tree_set_iterator<T> &data) const;

			Node					*getptr() const;
	
	};

	template<typename T>
	rb_tree_set_iterator<T>::rb_tree_set_iterator() : ptr(NULL)
	{
		
	}

	template<typename T>
	rb_tree_set_iterator<T>::rb_tree_set_iterator(Node *n_ptr) : ptr(n_ptr)
	{
		
	}

	template<typename T>
	rb_tree_set_iterator<T>::rb_tree_set_iterator(const rb_tree_set_iterator<T> &data) : ptr(data.getptr())
	{
		
	}

	template<typename T>
	rb_tree_set_iterator<T>::rb_tree_set_iterator(const rb_tree_set_const_iterator<T> &data) : ptr(const_cast<Node *>(data.getptr()))
	{
		
	}

	template<typename T>
	rb_tree_set_iterator<T>::~rb_tree_set_iterator()
	{
		
	}

	template<typename T>
	rb_tree_set_iterator<T> &rb_tree_set_iterator<T>::operator=(const rb_tree_set_iterator<T> &data)
	{
		if (this == &data)
			return (*this);
		this->ptr = data.ptr;
		return (*this);
	}

	template<typename T>
	typename rb_tree_set_iterator<T>::reference rb_tree_set_iterator<T>::operator*() const
	{
		return (*(this->ptr->value));
	}

	template<typename T>
	typename rb_tree_set_iterator<T>::pointer rb_tree_set_iterator<T>::operator->() const
	{
		return (this->ptr->value);
	}

	template<typename T>
	rb_tree_set_iterator<T> &rb_tree_set_iterator<T>::operator++()
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
	rb_tree_set_iterator<T> &rb_tree_set_iterator<T>::operator--()
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
	rb_tree_set_iterator<T> rb_tree_set_iterator<T>::operator++(int)
	{
		rb_tree_set_iterator tmp = *this;
		++(*this);
		return (tmp);
	}

	template<typename T>
	rb_tree_set_iterator<T> rb_tree_set_iterator<T>::operator--(int)
	{
		rb_tree_set_iterator tmp = *this;
		--(*this);
		return (tmp);
	}

	template<typename T>
	bool	rb_tree_set_iterator<T>::operator==(const rb_tree_set_iterator<T> &data) const
	{
		return (this->ptr == data.ptr);
	}

	template<typename T>
	bool	rb_tree_set_iterator<T>::operator!=(const rb_tree_set_iterator<T> &data) const
	{
		return (this->ptr != data.ptr);
	}

	template<typename T>
	typename rb_tree_set_iterator<T>::Node *rb_tree_set_iterator<T>::getptr() const
	{
		return (this->ptr);
	}

	// rb_tree_set_const_iterator for set:

	template<typename T>
	class rb_tree_set_const_iterator : public iterator<std::bidirectional_iterator_tag, T>
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
		
			rb_tree_set_const_iterator();

			rb_tree_set_const_iterator(Node *n_ptr);

			rb_tree_set_const_iterator(const rb_tree_set_const_iterator<T> &data);
			rb_tree_set_const_iterator(const rb_tree_set_iterator<T> &data);

			~rb_tree_set_const_iterator();

			rb_tree_set_const_iterator		&operator=(const rb_tree_set_const_iterator<T> &data);
			rb_tree_set_const_iterator		&operator=(const rb_tree_set_iterator<T> &data);

			reference						operator*() const;
			pointer							operator->() const;

			rb_tree_set_const_iterator		&operator++(); // ++ptr
			rb_tree_set_const_iterator		&operator--(); // --ptr

			rb_tree_set_const_iterator		operator++(int); // ptr++
			rb_tree_set_const_iterator		operator--(int); // ptr--

			bool 							operator==(const rb_tree_set_const_iterator<T> &data) const;
			bool							operator!=(const rb_tree_set_const_iterator<T> &data) const;

			const Node						*getptr() const;
		
	};

	template<typename T>
	rb_tree_set_const_iterator<T>::rb_tree_set_const_iterator() : ptr(NULL)
	{
	
	}

	template<typename T>
	rb_tree_set_const_iterator<T>::rb_tree_set_const_iterator(Node *n_ptr) : ptr(n_ptr)
	{
	
	}

	template<typename T>
	rb_tree_set_const_iterator<T>::rb_tree_set_const_iterator(const rb_tree_set_const_iterator<T> &data) : ptr(data.getptr())
	{
	
	}

	template<typename T>
	rb_tree_set_const_iterator<T>::rb_tree_set_const_iterator(const rb_tree_set_iterator<T> &data) : ptr(data.getptr())
	{
	
	}

	template<typename T>
	rb_tree_set_const_iterator<T>::~rb_tree_set_const_iterator()
	{
	
	}

	template<typename T>
	rb_tree_set_const_iterator<T> &rb_tree_set_const_iterator<T>::operator=(const rb_tree_set_const_iterator<T> &data)
	{
		if (this == &data)
			return (*this);
		this->ptr = data.getptr();
		return (*this);
	}

	template<typename T>
	rb_tree_set_const_iterator<T> &rb_tree_set_const_iterator<T>::operator=(const rb_tree_set_iterator<T> &data)
	{
		if (this == &data)
			return (*this);
		this->ptr = data.getptr();
		return (*this);
	}

	template<typename T>
	typename rb_tree_set_const_iterator<T>::reference rb_tree_set_const_iterator<T>::operator*() const
	{
		return (*(this->ptr->value));
	}

	template<typename T>
	typename rb_tree_set_const_iterator<T>::pointer rb_tree_set_const_iterator<T>::operator->() const
	{
		return (this->ptr->value);
	}

	template<typename T>
	rb_tree_set_const_iterator<T> &rb_tree_set_const_iterator<T>::operator++()
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
	rb_tree_set_const_iterator<T> &rb_tree_set_const_iterator<T>::operator--()
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
	rb_tree_set_const_iterator<T> rb_tree_set_const_iterator<T>::operator++(int)
	{
		rb_tree_set_const_iterator tmp = *this;
		++(*this);
		return (tmp);
	}

	template<typename T>
	rb_tree_set_const_iterator<T> rb_tree_set_const_iterator<T>::operator--(int)
	{
		rb_tree_set_const_iterator tmp = *this;
		--(*this);
		return (tmp);
	}

	template<typename T>
	bool	rb_tree_set_const_iterator<T>::operator==(const rb_tree_set_const_iterator<T> &data) const
	{
		return (this->ptr == data.ptr);
	}

	template<typename T>
	bool	rb_tree_set_const_iterator<T>::operator!=(const rb_tree_set_const_iterator<T> &data) const
	{
		return (this->ptr != data.ptr);
	}

	template<typename T>
	const typename rb_tree_set_const_iterator<T>::Node *rb_tree_set_const_iterator<T>::getptr() const
	{
		return (this->ptr);
	}
		
}

#endif