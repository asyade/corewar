NAME= asm
SRC= srcs/main.c \
	srcs/ft_put_asm_usage.c \
	srcs/ft_check_file_extansion.c \
	srcs/ft_parse.c \
	srcs/parsing_actions/ft_parse_flags.c \
	srcs/parsing_actions/ft_get_flags.c \
	srcs/ft_get_instruction_count.c \
	srcs/ft_discard_comments.c \
	srcs/ft_get_instruction_param_type.c \
	srcs/ft_check_params_integrity.c \
	srcs/ft_get_label_lst.c \
	srcs/parsing_actions/ft_make_encoding_byte.c \
	srcs/tokenization/ft_split.c \
	srcs/tokenization/ft_tokenize.c \
	srcs/tokenization/ft_lexing.c \
	srcs/tokenization/ft_lexing_2.c \
	srcs/tokenization/ft_assign_tokens_type.c \
	srcs/tokenization/ft_interpretations.c \
	srcs/tokenization/ft_interpretations_2.c \
	srcs/ft_parse_semantic_unit.c \
	srcs/ft_create_bin_buffer.c \
	srcs/ft_fill_header_name.c \
	srcs/ft_fill_header_comment.c \
	srcs/ft_get_params_value.c \
	srcs/ft_fill_bin_with_instruction.c \
	srcs/ft_create_corewar_file.c \
	srcs/ft_get_bin_filename.c \
	srcs/ft_bswap.c \
	srcs/ft_seek_labels.c \
	srcs/ft_is_token_decimal.c \
	srcs/ft_check_bin_integrity.c \
	srcs/diagnostics/ft_diagnostic.c \
	srcs/diagnostics/ft_get_abort_on_dk.c \
	srcs/diagnostics/ft_get_dk_colors_to_kind.c \
	srcs/diagnostics/ft_put_dk_colors.c \
	srcs/diagnostics/ft_get_dk_conf_from_msg.c \
	srcs/diagnostics/ft_set_dk_location.c \
	srcs/diagnostics/ft_init_dk_info.c \
	srcs/ft_check_label_integrity.c

HDRS= includes/asm.h
OBJ= $(SRC:.c=.o)
HDR_PATH= ./libft/includes/
CC= gcc
CC_FLAGS= -v -Ofast -Weverything -Wall -Werror -Wextra  -Wno-padded #-g3 -fsanitize=address -fsanitize-blacklist=my_ignores.txt
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
