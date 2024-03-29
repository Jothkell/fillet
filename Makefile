#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkellehe <jkellehe@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/18 15:10:56 by jkellehe          #+#    #+#              #
#    Updated: 2018/07/06 16:35:38 by jkellehe         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = fillet

SRC = ft_bzero.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putnbr.c \
ft_putstr.c ft_strclr.c ft_strdel.c ft_striter.c ft_striteri.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_putendl.c ft_atoi.c \
ft_memcmp.c ft_strcmp.c ft_strequ.c ft_strlen.c ft_strncmp.c ft_strnequ.c \
ft_toupper.c ft_tolower.c ft_isdigit.c ft_isalpha.c ft_isalnum.c ft_isascii.c \
ft_isprint.c ft_itoa.c ft_strcat.c ft_strchr.c ft_strcpy.c ft_strdup.c \
ft_strjoin.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncpy.c ft_strnew.c \
ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c \
ft_strlcat.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c \
ft_lstnew.c 

HEADER = libft.h

all: $(NAME)

$(NAME):
	gcc -o fillet.c -c -Wall -Wextra -Werror $(SRC) -I$(HEADER)

fclean:
	rm fillet.c



re: fclean all
