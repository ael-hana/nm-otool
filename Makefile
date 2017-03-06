NAME=ft_nm

CC=clang

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

SRC=nm.c

OBJ=$(SRC:.c=.o)

$(NAME):
	make -C libft/
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o ft_nm

all: $(NAME)

clean:
	make -C libft/ clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft/ fclean
	$(RM) $(NAME)

re: fclean all
