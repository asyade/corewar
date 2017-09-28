NAME= libftprintf.a
SRC= srcs/printf/ft_printf.c \
	srcs/printf/ft_get_arg.c \
	srcs/printf/ft_cast.c \
	srcs/printf/ft_get_conversion.c \
	srcs/printf/ft_convertor.c \
	srcs/printf/ft_convertor_str.c \
	srcs/printf/ft_convertor_hexa.c \
	srcs/printf/ft_convertor_decimal.c \
	srcs/sprintf/ft_sprintf.c \
	srcs/sprintf/ft_sconvertor.c \
	srcs/sprintf/ft_sconvertor_str.c \
	srcs/sprintf/ft_sconvertor_hexa.c \
	srcs/sprintf/ft_sconvertor_decimal.c


HDRS= includes/ft_printf.h
OBJ= $(SRC:.c=.o)
HDR_PATH= ./includes
CC= gcc
CC_FLAGS= -Ofast -v -Wno-padded -Weverything -Wall -Werror -Wextra -g3 -fsanitize=address -fsanitize-blacklist=my_ignores.txt
LIBFT_PATH=./libft
FLAGS= -L$(LIBFT_PATH) -lft -I$(HDR_PATH) -I./$(LIBFT_PATH)/includes

all: submodule $(NAME)

submodule:
	@make -C libft/

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
%.o : %.c $(HDRS)
	$(CC) $(CC_FLAGS) $< -I$(HDR_PATH) -I$(LIBFT_PATH)/includes -c -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_PATH) clean
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
