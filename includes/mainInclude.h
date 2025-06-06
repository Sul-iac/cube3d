/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainInclude.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:32 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 13:21:29 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAININCLUDE_H
# define MAININCLUDE_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "get_next_line.h"

# define TILE 20


# define COL_WALL   0x00333333   
# define COL_FLOOR  0x00909090   
# define COL_EMPTY  0x00000000 
# define COL_PLAYER 0x00FF0000

// MAC 
// # define KEY_W 13
// # define KEY_A 0
// # define KEY_S 1
// # define KEY_D 2
// # define KEY_ESC 53

// SULLLIIIACCCCC 
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_L 65363
# define KEY_R 65361 // je sais pas quel code tu utilises sur mac ducoup j'ai pas mis pour toi chapeau chapeau
# define KEY_ESC 65307

# define ROT_SPEED 0.03f

typedef struct
{
	void				*mlx_init;
	void				*mlx_img;
	void				*mlx_windows;
	char				*address;
	int					endian;
	int					line_length;
	int					bits_per_pixel;
	unsigned int		win_h;
	unsigned int		win_w;
	
}				minilibx_struct;

typedef struct s_player
{
	int		move_backward;
	int		move_right;
	int		move_left;
	int		move_forward;
	int		rotate_left;
	int		rotate_right;
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	float	move_speed;
}				t_player;

typedef struct s_raycast
{
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		line_h;
	int		draw_start;
	int		draw_end;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	time;
	double	old_time;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	wall_dist;
}				t_raycast;

typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
	int		tex_x; 
	int		tex_y;
	int		color;
	int		y;
	int		d;
	double	wall_x;
}				t_texture;

typedef struct	s_get_map
{
	int		fd;
	char	*get_line;
	tu_list *rows;
	tu_list *node_next_line;
	int 	len;
	int		in_map;	
}				t_get_map;

typedef struct 	s_game
{
	char			**map;
	int				map_w;
	int				map_h;
	int				px;
	int				py;
	char			pdir;
	void			*mlx_init;
	void			*mlx_windows;
	t_texture		ea;
	t_texture		no;
	t_texture		we;
	t_texture		so;
	t_player		player;
	minilibx_struct	mlx_struct;
	int				floor_color;
	int				ceiling_color;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
}				t_game;


//mlx
void put_pixel(minilibx_struct* data, int x, int y, int color);
int ft_minilibx_init(t_game *game_st);
int loop_hook(void *param);
void draw_vertical_line(minilibx_struct *mlx_s, int x, int y_start, int y_end, int color);
// void draw_line(minilibx_struct *mlx_struct, int x0, int y0, int x1, int y1, int color);


//init
void init_struct(t_game *game_st);
void init_texture_struct(t_game *game_st);

// parser
int		parse_map(char *path, t_game *game_st);
int		get_map(char *path, char ***map, int *height, int *width);
int		validate_map(t_game *game_st);
int		check_closed(t_game *game_st);
int		flood(char **map_copy, int x, int y, t_game *game_st);
int		check_borders(t_game *game_st);
int		check_character(t_game *game_st);
int		parse_textures(char *path, t_game *game_st);
int		is_map_line(char *s);
int		extract_rgb(char *line);
int		parse_colors(char *path, t_game *game_st);
int		is_wall(t_game *game_st, float x, float y);
void	split_rgb(int *r, int *g, int *b, char **split);
char	**create_2d_map(int width, int height, tu_list **rows);
void	malloc_and_send_map(tu_list *cur, char **map, int width);
void	init_path_texture(t_game *game_st, int fd);
int		get_line_to_list(t_get_map *get_map, int *width, int *height);
void	init_get_map_struct(t_get_map *get_map, char *path);
void	free_map(char **map, int h);
int		character_position(t_game *game_st, int *player_count, int y);
int		check_character(t_game *game_st);
int		check_character(t_game *game_st);






// mm
void render_minimap(char **map, int w, int h, minilibx_struct *mm, float player_x, float player_y);

//hook
int key_press(int keycode, t_game *game_st);
int key_release(int keycode, t_game *game_st);
void update_player_position(t_game *game_st);


// RC
int 	render_raycast(t_game *game_st);
void	init_delta_dist(t_raycast* raycast);
void	draw_wall_texture(t_game *game_st, int x, t_raycast *raycast);
void	init_texture_direction(t_raycast *raycast, t_game *game_st, t_texture *tex, int x);
void	draw_pixel_wall(t_raycast *raycast, t_game *game_st, t_texture *tex, int x);
void	draw_floor_ceiling(t_game *game_st, int x);


#endif