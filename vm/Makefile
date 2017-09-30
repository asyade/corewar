CC = gcc

NAME = corewar

PATH_SRC = srcs/ srcs/parsing/

DIRS =	obj/core/ obj/env/ obj/inst

SRC = srcs/core/core.c \
		srcs/core/cpu.c \
		srcs/core/free.c \
		srcs/core/memory.c \
		srcs/core/memory_read_n.c \
		srcs/core/params.c \
		srcs/core/params_get.c \
		srcs/core/params_check.c \
		srcs/core/play.c \
		srcs/core/process.c \
		srcs/core/vm_sound.c \
		srcs/core/vm.c \
		srcs/inst/inst_utils.c \
		srcs/inst/inst_fork.c \
		srcs/inst/inst_load.c \
		srcs/inst/inst_operator.c \
		srcs/inst/inst_set.c \
		srcs/inst/inst.c \
		srcs/core/dump.c \
		srcs/env/ncenv.c \
		srcs/env/ncenv_windaube.c \
		srcs/env/ncenv_dump.c \
		srcs/env/ncenv_stats.c \
		srcs/env/ncenv_colors.c \
		srcs/env/shenv_unused.c \
		srcs/env/shenv_verbose.c \
		srcs/env/shenv_verbose2.c \
		srcs/env/shenv.c \
		srcs/source_provider.c \
		srcs/logger_utils.c \
		srcs/champ_sort.c \
		srcs/main.c \
		srcs/usage.c \
		srcs/params.c

OBJ= $(SRC:.c=.o)
FLAGS= -Wall -Wextra -Werror -g3#-g3 -fsanitize=address
LIBS= -L./libft -lft -lncurses -L./ft_printf -lftprintf
HEADERS= -I./libft/includes -I./includes/ -I./ft_printf/includes
DEPTHS= Makefile includes/cpu.h includes/structs.h includes/def.h includes/libft.h includes/env_ncurse.h includes/env_sh.h  includes/vm.h includes/inst.h includes/libft.h

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	make -C ft_printf/
	$(CC) $(OBJ) $(HEADERS) $(FLAGS) $(LIBS) -o $(NAME)
	echo "\033[33mCreating  \033[32m[✔] \033[0m$(NAME)"

%.o: %.c
	$(CC) $< -c $(HEADERS) $(FLAGS) -o $@

.PHONY: clean fclean

clean :
	make -C libft/ clean
	make -C ft_printf/ clean
	/bin/rm -f $(OBJ)
	echo "\033[31mRemoving  \033[32m[✔] \033[0mObject files"

fclean : clean
	make -C libft/ fclean
	make -C ft_printf/ fclean
	/bin/rm -f $(NAME)
	echo "\033[31mRemoving  \033[32m[✔] \033[0m$(NAME)"

re : fclean all
