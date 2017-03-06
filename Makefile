NAME=ft_nm

CC=clang

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC=nm.c dis_handle.c display.c handle.c list_nm.c

SRC_OTOOL= otool.c

OBJ=$(SRC:.c=.o)

OBJ_OTOOL=$(SRC_OTOOL:.c=.o)

$(NAME):
	make -C libft/
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -c $(SRC_OTOOL)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o ft_nm
	$(CC) $(CFLAGS) $(OBJ_OTOOL) libft/libft.a -o ft_otool

all: $(NAME)

clean:
	make -C libft/ clean
	$(RM) $(OBJ)
	$(RM) $(OBJ_OTOOL)

fclean: clean
	make -C libft/ fclean
	$(RM) $(NAME)
	$(RM) ft_otool

re: fclean all
