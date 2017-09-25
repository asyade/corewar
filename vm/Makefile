CC = clang

NAME = corewar

PATH_SRC = srcs/ srcs/parsing/

DIRS =	obj/core/ obj/env/ obj/source/ obj/inst

SRC = srcs/core/core.c \
		srcs/core/cpu.c \
		srcs/core/free.c \
		srcs/core/memory.c \
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
		srcs/env/shenv.c \
		srcs/source/defaultSourceProvider.c \
		srcs/logger.c \
		srcs/main.c \
		srcs/params.c \

OBJ = $(patsubst $(PATH_SRC)/%.c, obj/%.o, $(SRC))

FLAGS = -Wall -Wextra -Werror -g3 #-Ofast # -g -fsanitize=address

LIBS = -L./libft -lft -lncurses

HEADERS = -I libft/includes -I includes/

DEPTHS = Makefile includes/cpu.h includes/structs.h includes/def.h includes/libft.h includes/envNcurse.h includes/envSh.h includes/source.h includes/vm.h includes/inst.h includes/libft.h

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft/
	$(CC) $(OBJ) -o $(NAME) $(HEADERS) $(FLAGS) $(LIBS)
	echo "\033[33mCreating  \033[32m[✔] \033[0m$(NAME)"

obj/%.o : $(PATH_SRC)/%.c $(DEPTHS)
	mkdir -p $(DIRS)
	$(CC) -c $< -o $@ $(HEADERS) $(FLAGS)
	echo "\033[33mCompiling \033[32m[✔] \033[0m$<"

.PHONY : clean fclean

clean :
	make -C libft/ clean
	/bin/rm -rf obj/
	echo "\033[31mRemoving  \033[32m[✔] \033[0mObject files"

fclean : clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)
	echo "\033[31mRemoving  \033[32m[✔] \033[0m$(NAME)"

re : fclean all
