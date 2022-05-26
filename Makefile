# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchelste <bchelste@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/30 22:04:41 by bchelste          #+#    #+#              #
#    Updated: 2022/02/19 20:41:15 by bchelste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_containers

CFLAGS			= -Wall -Werror -Wextra -std=c++98

CC				= clang++

SRCS			= main.cpp check_tests.cpp
				
HPPFLS			= reimplement.hpp iterators.hpp rb_tree.hpp vector.hpp stack.hpp map.hpp set.hpp set_utils.hpp

OBJS			= $(SRCS:.cpp=.o)

RM				= rm -f

%.o: %.cpp $(HPPFLS)
			$(CC) $(CFLAGS) $(OPTFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)
			$(RM) ft_vector.txt std_vector.txt
			$(RM) ft_stack.txt std_stack.txt
			$(RM) ft_map.txt std_map.txt
			$(RM) ft_set.txt std_set.txt
			$(RM) dif_vector.txt dif_stack.txt dif_map.txt dif_set.txt

re:			fclean all

check:		re
			./$(NAME)
			@diff ft_vector.txt std_vector.txt > dif_vector.txt || true
			@diff ft_stack.txt std_stack.txt > dif_stack.txt || true
			@diff ft_map.txt std_map.txt > dif_map.txt|| true
			@diff ft_set.txt std_set.txt > dif_set.txt|| true
			@echo "\033[1;32m *Diff files were created*\033[0m"
			

.PHONY:		all clean fclean re check