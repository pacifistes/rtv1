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

NAME = rtv1

SRCS = main.c parse.c ft_error.c parse_checker.c atod_and_lstadd.c \
		amb_and_convcolor.c vector_functions1.c vector_functions2.c \
		color_functions.c mlx_image_put_pixel.c \
		intersect_sphere.c intersect_plan.c intersect_cone.c equa_sec.c \
		intersect_cylinder.c intersect_cylinder2.c lenray.c \
		display.c init_threads.c move.c key_hook.c menu.c \
		do_gnl_and_verif_name.c

OBJECT = $(SRCS:.c=.o)

$(NAME): 
		make -C libft/
		gcc -o $(NAME) -Wall -Werror -Wextra -lmlx -framework OpenGL \
		-framework Appkit $(SRCS) libft/libft.a

all: $(NAME)

clean:
	rm -f $(OBJECT)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all
	make -C libft/ re
	

