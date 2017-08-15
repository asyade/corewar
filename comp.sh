gcc srcs/*.c srcs/core/*.c srcs/source/*.c srcs/env/*.c srcs/env/sdlenv/*.c -Wall -Wextra -Werror -g3 -fsanitize=address libft/libft.a  -I./includes `sdl2-config --cflags --libs` -lncurses
