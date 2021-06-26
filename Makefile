# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: ksmorozo <ksmorozo@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/24 11:23:42 by ksmorozo      #+#    #+#                  #
#    Updated: 2021/06/26 15:32:21 by ksmorozo      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC_FILE = main.c event_handlers.c \
get_next_line/get_next_line.c \
handle_textures.c \
update_player.c cast_rays.c \
cast_rays_utils.c \

CHECKER_DIR = checker/
CHECKER_SRC_FILE = check_map.c check_resolution.c \
check_rgb.c check_cub_file.c \
check_arguments.c \
check_texture.c check_map_utils.c

INIT_DIR = initialiser/
INIT_SRC_FILE = init_sprite_struct.c init_config_struct.c \
init_wall_struct.c init_ray_struct.c \
init_player_struct.c

GRAPHICS_DIR = graphics/
GRAPHICS_SRC_FILE = draw_sprite.c \
draw_sprite_utils.c drawing_utils.c \
draw_minimap.c draw_floor_ceiling.c \
handle_image.c

PARSER_DIR = parser/
PARSER_SRC_FILE = parser.c parse_texture.c \
parse_ceiling_floor.c

MINILIBX_DIR = mlx/
MINILIBX = libmlx.dylib

LIBFT_DIR = libft/
LIBFT = libft.a

OBJ = $(SRC_FILE:.c=.o) \
$(addprefix $(CHECKER_DIR), $(CHECKER_SRC_FILE:.c=.o)) \
$(addprefix $(INIT_DIR), $(INIT_SRC_FILE:.c=.o)) \
$(addprefix $(GRAPHICS_DIR), $(GRAPHICS_SRC_FILE:.c=.o)) \
$(addprefix $(PARSER_DIR), $(PARSER_SRC_FILE:.c=.o))

HEADER = cub3d.h

CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C $(MINILIBX_DIR)
	make -C $(LIBFT_DIR)
	gcc $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	mv $(MINILIBX_DIR)$(MINILIBX) .

clean:
	rm -f $(OBJ) $(MINILIBX)
	make clean -C $(MINILIBX_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(MINILIBX_DIR)$(MINILIBX)
	rm -f $(LIBFT) $(LIBFT_DIR)$(LIBFT)

re: fclean all