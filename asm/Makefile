NAME= asm
SRC= srcs/main.c \
	srcs/ft_put_asm_usage.c \
	srcs/ft_check_file_extansion.c \
	srcs/ft_parse.c \
	srcs/ft_get_instruction_count.c \
	srcs/ft_discard_comments.c \
	srcs/ft_get_instruction_param_type.c \
	srcs/ft_check_params_integrity.c \
	srcs/ft_get_label_lst.c \
	srcs/parsing_actions/ft_make_encoding_byte.c \
	srcs/tokenization/ft_split.c \
	srcs/tokenization/ft_tokenize.c \
	srcs/tokenization/ft_lexing.c \
	srcs/tokenization/ft_interpretations.c

HDRS= includes/asm.h
OBJ= $(SRC:.c=.o)
HDR_PATH= ./libft/includes/
CC= gcc
CC_FLAGS= -v -Ofast -Weverything -Wall -Werror -Wextra  -g3 -fsanitize=address -fsanitize-blacklist=my_ignores.txt
LIBFT_PATH=./libft
FLAGS= -L$(LIBFT_PATH) -lft -I$(HDR_PATH) -I./includes

all: submodule $(NAME)

submodule:
	@make -C libft/

$(NAME): $(OBJ)
	$(CC) $(CC_FLAGS) $^ $(FLAGS) -o $(NAME)
%.o : %.c $(HDRS)
	$(CC) $(CC_FLAGS) $< -c -I$(HDR_PATH) -I./includes -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_PATH) clean
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
