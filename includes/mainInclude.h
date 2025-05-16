/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainInclude.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:32 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/16 17:21:28 by vorace32         ###   ########.fr       */
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
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

// SULLLIIIACCCCC 
// # define KEY_W 119
// # define KEY_A 97
// # define KEY_S 115
// # define KEY_D 100
// # define KEY_ESC 65307

typedef struct
{
	void				*ptr;	
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
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
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
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	plan_x; // le rayon 2d pour le plan cam
	double	plan_y; // la FOV en gros
	double	time;
	double	old_time;
	double	camera_x; // coord x sur le plan
	double	ray_dir_x;
	double	ray_dir_y;
	double	wall_dist;
}				t_raycast;

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
	t_player		player;
	minilibx_struct	mini_map;
}				t_game;


//mlx
void put_pixel(minilibx_struct* data, int x, int y, int color);
int ft_minilibx_init(t_game *game_st);
int loop_hook(void *param);
void draw_line(minilibx_struct *mlx_struct, int x0, int y0, int x1, int y1, int color);
void draw_circle(minilibx_struct *img, int grid_x, int grid_y, int col);
//init
t_game init_struct(t_game *game_st);

// parser
int parse_map(char *path, t_game *game_st);
int get_map(char *path, char ***map, int *height, int *width);
int validate_map(t_game *game_st, char **map, int h, int w);
int check_closed(char **map, int width, int height, int px, int py);
int flood(char **map_copy, int x, int y, int w, int h);
int check_borders(char **map, int width, int height);
int check_character(char **map, int w, int h, int *px, int *py, char *pdir);
static int is_map_line(char *s);

// evident
void render_minimap(char **map, int w, int h, minilibx_struct *mm, float player_x, float player_y);

//hook
int key_press(int keycode, t_game *game_st);
int key_release(int keycode, t_game *game_st);
void update_player_position(t_game *game_st);



// RC
int render_raycast(t_game *game_st);


#endif