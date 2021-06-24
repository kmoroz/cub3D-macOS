# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ksmorozo <ksmorozo@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/24 11:23:42 by ksmorozo      #+#    #+#                  #
#    Updated: 2021/06/24 11:32:06 by ksmorozo      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC_FILE = main.c event_handlers.c \
parser.c get_next_line/get_next_line.c \
handle_image.c \
draw_floor_ceiling.c handle_textures.c \
draw_sprite.c \
draw_sprite_utils.c drawing_utils.c \
update_player.c cast_rays.c \
cast_rays_utils.c \
draw_minimap.c \

CHECKER_DIR = checker/
CHECKER_SRC_FILE = check_map.c check_resolution.c \
check_rgb.c check_cub_file.c \
check_arguments.c \
check_texture.c check_map_utils.c

INIT_DIR = initialiser/
INIT_SRC_FILE = init_sprite_struct.c init_config_struct.c \
init_wall_struct.c init_ray_struct.c \
init_player_struct.c

MINILIBX_DIR = mlx/
MINILIBX = libmlx.dylib

LIBFT_DIR = libft/
LIBFT = libft.a

OBJ = $(SRC_FILE:.c=.o) \
$(addprefix $(CHECKER_DIR), $(CHECKER_SRC_FILE:.c=.o)) \
$(addprefix $(INIT_DIR), $(INIT_SRC_FILE:.c=.o))

HEADER = cub3d.h

CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C $(MINILIBX_DIR)
	make -C $(LIBFT_DIR)
	gcc $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	mv $(MINILIBX_DIR)$(MINILIBX) .

clean:
	rm -f $(OBJ)
	make clean -C $(MINILIBX_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(MINILIBX_DIR)$(MINILIBX)
	rm -f $(LIBFT) $(LIBFT_DIR)$(LIBFT)

re: fclean all