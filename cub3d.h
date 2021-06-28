/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ksmorozo <ksmorozo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 13:15:43 by ksmorozo      #+#    #+#                 */
/*   Updated: 2021/06/28 13:14:10 by ksmorozo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <math.h>
# include <stdint.h>

/*
** Keyboard
*/

# define KEY_A 0 //97
# define KEY_W 13 //119
# define KEY_S 1 //115
# define KEY_D 2 //100
# define KEY_ESC 53 //65307
# define KEY_LEFT 123 //65361
# define KEY_RIGHT 124 //65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define PI 3.14159265
# define TWO_PI 6.28318530
# define FOV_ANGLE 1.0471975500000001
# define WALL_STRIP_WIDTH 10
# define SCALE_FACTOR 0.3
# define TILE_SIZE 30
# define NUM_TEXTURES 6
# define NO_TEXTURE 0
# define SO_TEXTURE 1
# define WE_TEXTURE 2
# define EA_TEXTURE 3
# define SPRITE_TEXTURE 4
# define ANIMATION_TEX 5
# define ERROR -1
# define OK 1
# define EPSILON 0.2

typedef struct s_cub
{
	long int	x_res;
	long int	y_res;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*sp_texture;
	int			floor_colour[3];
	int			ceiling_colour[3];
	int			type_identifier_num;
	t_list		*map;
}				t_cub;

typedef struct s_window_settings
{
	void		*mlx;
	void		*img;
	void		*window;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			*colour_buffer;
}				t_window_settings;

typedef struct s_player
{
	float	xpos;
	float	ypos;
	float	angle;
	float	walk_speed;
	float	turn_speed;
	int		turn_direction;
	int		walk_direction;
	float	sidewalk;
}				t_player;

typedef struct s_wall
{
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		wall_strip_height;
	float	proj_plane_distance;
	float	wall_height;
}				t_wall;

typedef struct s_texture
{
	void	*img;
	int		*colour_buffer;
	int		img_width;
	int		img_height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_texture;

typedef struct s_sprite
{
	float		*x;
	float		*y;
	float		*distance;
	float		*angle;
	int			num;
	int			*visible;
	float		*top;
	float		*bottom;
	float		*screen_pos_x;
	float		*left_x;
	float		*right_x;
	float		height;
	float		width;
	int			animation_index;
}			t_sprite;

typedef struct s_game
{
	t_player	*player;
	t_wall		*wall;
	t_texture	texture[NUM_TEXTURES];
	t_sprite	*sprite;
}				t_game_state;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	horizontal_wall_hit_x;
	float	horizontal_wall_hit_y;
	float	horizontal_wall_hit;
	float	vertical_wall_hit;
	float	vertical_wall_hit_x;
	float	vertical_wall_hit_y;
	float	*distance;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content;
	int		num_rays;
	float	hor_x_step;
	float	hor_y_step;
	float	vert_x_step;
	float	vert_y_step;
	int		was_hit_vertical;
}				t_ray;

typedef struct s_settings
{
	t_window_settings	*window;
	t_game_state		*game;
	t_cub				*config;
	t_ray				*ray;
}				t_settings;

int		parse_file(char *file, t_cub *config);
int		key_press_handler(int keycode, t_settings *settings);
int		key_release_handler(int keycode, t_settings *settings);
int		refresh(t_settings *settings);
void	draw_map(t_settings *settings);
void	draw_ray(t_settings *settings,
			float final_x, float final_y);
void	cast_rays(t_settings *settings);
void	generate_wall_projection(t_settings *settings, int count);
void	draw_ceiling(t_settings *settings);
void	draw_floor(t_settings *settings);
void	load_textures(t_settings *settings);
int		choose_texture(t_settings *settings);
int		check_args(int argc, char **argv);
float	calculate_distance(float x, float y,
			float intersection_x, float intersection_y);
void	render_sprite(t_settings *settings);
float	normalise_angle(float angle);
void	my_mlx_pixel_put(t_window_settings *window, int x, int y, int color);
int		get_colour(t_texture texture, int x, int y);
void	verify_max_screen_size(t_window_settings window, t_cub *config);
int		check_max_rgb_value(t_cub config);
int		veirify_rgb_input(char c);
int		is_map_on_top(t_cub config);
void	count_type_identifiers(t_cub *config, char *line);
int		verify_num_of_type_identifiers(t_cub config);
int		is_texture_provided(t_cub config);
int		check_map(t_cub config);
int		check_player(t_cub config);
int		is_map_on_top(t_cub config);
int		is_map_closed(t_cub config);
int		is_zero_open(t_cub config, int x, int y);
int		check_blank_lines_in_map(t_cub config);
int		is_line_last(t_cub config);
void	swap_sprites(t_sprite *sprite, int i, int j);
void	sort_sprites(t_settings *settings);
float	calculate_angle_sprite_player(t_settings *settings,
			int count, float angle_sprite_player);
void	is_sprite_visible(t_settings *settings, t_sprite *sprite, int count);
void	update_player_position(t_settings *settings, t_player *player);
void	find_shortest_distance(t_player *player, t_ray *ray, int count);
void	find_ray_direction(t_settings *settings);
int		check_wall_collision(t_settings *settings, float next_x, float next_y);
void	reset_ray_struct(t_ray *ray);
void	draw_minimap_components(t_settings *settings);
void	draw_a_square(t_window_settings *window, float x, float y, int colour);
void	init_player(t_settings *settings);
void	init_sprite(t_settings *settings);
void	init_ray(t_settings *settings);
void	init_config(t_settings *settings, t_cub *config);
void	init_texture_path(t_cub *config);
int		x_button_hook(void);
void	init_wall(t_settings *settings);
int		check_config_file(t_cub config);
int		check_allowed_chars(t_cub config);
int		parse_floor_colour(t_cub *game_config, char *line);
int		parse_ceiling_colour(t_cub *game_config, char *line);
int		parse_sprite_texture(t_cub *game_config, char *line);
int		parse_wall_texture(t_cub *game_config, char *line);
void	draw_a_circle(t_window_settings *window, float x, float y, int colour);
int		is_rgb_present(t_cub config);
int		veirify_resolution_input(char c);

#endif
