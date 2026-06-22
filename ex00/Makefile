# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/17 17:10:17 by edi-maio          #+#    #+#              #
#    Updated: 2026/06/21 21:50:47 by edi-maio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp \
		BitcoinExchange.cpp

OBJS = $(SRCS:.cpp=.o)

%.o: %.cpp
	c++ $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	c++ $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
