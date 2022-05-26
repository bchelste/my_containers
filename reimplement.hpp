/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reimplement.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:51:31 by bchelste          #+#    #+#             */
/*   Updated: 2022/02/18 14:18:24 by bchelste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REIMPLEMENT_HPP
# define REIMPLEMENT_HPP

namespace ft
{
	// enable_if:
	
	template<bool B, typename T = void>
	struct enable_if
	{
		
	};
	
	template<typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	// is_integral_base:

	template<typename>
	struct is_intagral_base
	{
		static const bool value = false;
	};

	template<>
	struct is_intagral_base<char>
	{
		static const bool value = true;
	};

	template<>
	struct is_intagral_base<unsigned char>
	{
		static const bool value = true;
	};

	template<>
	struct is_intagral_base<bool>
	{
		static const bool value = true;
	};

	template<>
	struct is_intagral_base<short>
	{
		static const bool value = true;
	};
	
	template<>
	struct is_intagral_base<unsigned short>
	{
		static const bool value = true;
	};

	template<>
	struct is_intagral_base<int>
	{
		static const bool value = true;
	};

	template<>
	struct is_intagral_base<unsigned int>
	{
		static const bool value = true;
	};
	
	template<>
	struct is_intagral_base<long>
	{
		static const bool value = true;
	};
	
	template<>
	struct is_intagral_base<unsigned long>
	{
		static const bool value = true;
	};

	template<>
	struct is_intagral_base<long long>
	{
		static const bool value = true;
	};

	template<>
	struct is_intagral_base<unsigned long long>
	{
		static const bool value = true;
	};

	// remove_const:
	
	template<typename T>
	struct remove_const
	{
		typedef T type;
	};

	template<typename T>
	struct remove_const<const T>
	{
		typedef T type;
	};

	// is_integral:
	
	template<typename T>
	struct is_integral : public is_intagral_base<typename remove_const<T>::type>
	{
		
	};

	template<typename InputIterator_1, typename InputIterator_2>
	bool equal(InputIterator_1 first_1,
						InputIterator_1 last_1, InputIterator_2 first_2)
	{
		while (first_1 != last_1)
		{
			if (!(*first_1 == *first_2))
				return (false);
			++first_1;
			++first_2;
		}
		return (true);
	}

	template<typename InputIterator_1, typename InputIterator_2>
	bool lexicographical_compare(InputIterator_1 first_1, InputIterator_1 last_1,
								InputIterator_2 first_2, InputIterator_2 last_2)
	{
		while ((first_1 != last_1) && (first_2 != last_2))
		{
			if (*first_2 < *first_1)
				return (false);
			else if (*first_1 < *first_2)
				return (true);
			++first_1;
			++first_2;
		}
		return ((first_2 != last_2) && (first_1 == last_1));
	}
	
	// pair:

	template<typename T1, typename T2>
	class pair
	{
		public:

			typedef T1			first_type;
			typedef T2			second_type;

			first_type			first;
			second_type			second;

			pair();
			
			template<typename U, typename V>
			pair(const pair<U,V> &pr);

			pair(const first_type &a, const second_type &b);

			~pair();

			pair	&operator=(const pair &pr);
	};

	template<typename T1, typename T2>
	pair<T1, T2>::pair() : first(T1()), second(T2())
	{
		
	}

	template<typename T1, typename T2>
	template<typename U, typename V>
	pair<T1, T2>::pair(const pair<U,V> &pr) : first(pr.first), second(pr.second)
	{
	
	}

	template<typename T1, typename T2>
	pair<T1, T2>::pair(const first_type &a, const second_type &b) : first(a), second(b)
	{
		
	}
	
	template<typename T1, typename T2>
	pair<T1, T2>::~pair()
	{
		
	}

	template<typename T1, typename T2>
	pair<T1, T2>	&pair<T1, T2>::operator=(const pair &pr)
	{
		if (this == &pr)
			return (*this);
		first = pr.first;
		second = pr.second;
		return (*this);
	}

	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <class T1, class T2>
  	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
	}

	template <class T1, class T2>
  	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
  	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		  return ((lhs.first < rhs.first) || ((lhs.first == rhs.first) && (lhs.second < rhs.second)));
	}
	
	template <class T1, class T2>
  	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		  return (!(rhs < lhs));
	}
	
	template <class T1, class T2>
  	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}
	
	template <class T1, class T2>
  	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		  return (!(lhs < rhs));
	}
	
}

// tests for the check:

//void ft_check_my_stack();
//void ft_check_my_vector();
//void ft_check_my_map();

void ft_container(std::string ft_name, std::string stl_name, int flag);

#endif


