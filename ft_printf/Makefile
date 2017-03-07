# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-hana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/20 00:58:44 by ael-hana          #+#    #+#              #
#    Updated: 2016/01/12 20:40:52 by ael-hana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC = ft_bit_wise.c \
		ft_print_num_d.c \
		ft_printf.c \
		ft_printf_op_c_unicode.c \
		ft_printf_op_s.c \
		ft_printf_p.c \
		ft_printf_op_s_unicode.c \
		ft_conv_base.c \
		ft_modif_list.c ft_len_func.c \
		ft_foret_de_if.c \
		ft_foret_de_if_2.c

SRCLIBFT =    ft_atoi.c \
    ft_bzero.c \
    ft_isalnum.c \
    ft_isalpha.c \
    ft_isascii.c \
    ft_isdigit.c \
    ft_isprint.c \
    ft_itoa.c \
    ft_lstadd.c \
    ft_lstdel.c \
    ft_lstdelone.c \
    ft_lstiter.c \
    ft_lstmap.c \
    ft_lstnew.c \
    ft_memalloc.c \
    ft_memccpy.c \
    ft_memchr.c \
    ft_memcmp.c \
    ft_memcpy.c \
    ft_memdel.c \
    ft_memmove.c \
    ft_memset.c \
    ft_putchar.c \
    ft_putchar_fd.c \
    ft_putendl.c \
    ft_putendl_fd.c \
    ft_putnbr.c \
    ft_putnbr_fd.c \
    ft_putstr.c \
    ft_putstr_fd.c \
    ft_strcat.c \
    ft_strchr.c \
    ft_strclr.c \
    ft_strcmp.c \
    ft_strcpy.c \
    ft_strdel.c \
    ft_strdup.c \
    ft_strequ.c \
    ft_striter.c \
    ft_striteri.c \
    ft_strjoin.c \
    ft_strlcat.c \
    ft_strlen.c \
    ft_strmap.c \
    ft_strmapi.c \
    ft_strncat.c \
    ft_strncmp.c \
    ft_strncpy.c \
    ft_strnequ.c \
    ft_strnew.c \
    ft_strnstr.c \
    ft_strrchr.c \
    ft_strsplit.c \
    ft_strstr.c \
    ft_strsub.c \
    ft_strtrim.c \
    ft_tolower.c \
    ft_toupper.c

OBJ = $(SRC:.c=.o)


OBJLIBFT = $(SRCLIBFT:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(FLAGS) -c $(addprefix  libft/,$(SRCLIBFT))
		@ar rc $(NAME) $(OBJ) $(OBJLIBFT)
		@ranlib $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $< $(FLAGS) -I libft/

clean:
	@rm -f $(OBJ)
	@rm -f $(OBJLIBFT)

fclean: clean
	@rm -f $(NAME)

re: fclean all
