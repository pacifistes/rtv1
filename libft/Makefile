# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 12:08:07 by bbrunell          #+#    #+#              #
#    Updated: 2016/02/09 12:01:16 by bbrunell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_strjoin.c ft_strlen.c ft_strnew.c ft_strsub.c ft_atoi.c \
		get_next_line.c ft_nbr_case.c ft_numchr.c ft_strsplit.c \
		ft_strcmp.c ft_strdel.c ft_check_end.c ft_get_number_of_words.c\
		ft_verifint.c ft_nbr_case.c ft_numchr.c ft_parsing.c ft_putstr.c \
		ft_verif_file.c ft_strncmp.c ft_memalloc.c ft_bzero.c \
		letter_maj.c

OBJECT = $(SRCS:.c=.o)

$(NAME): 
		gcc -g -Wall -Werror -Wextra -c $(SRCS) -I ./
		ar rc $(NAME) $(OBJECT)
		ranlib $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all
