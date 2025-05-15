/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainInclude.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:32 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/15 19:34:27 by qbarron          ###   ########.fr       */
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

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

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
	double	plan_x; // le rayon 2d pour le plan cam
	double	plan_y;
	double	time;
	double	old_time;
	double	camera_x; // coord x sur le plan
	double	ray_dir_x;
	double	ray_dir_y;
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
void render_minimap(char **map, int w, int h, minilibx_struct *mm, int px, int py);

//hook
int key_press(int keycode, t_game *game_st);
int key_release(int keycode, t_game *game_st);
void update_player_position(t_game *game_st);



// RC
int render_raycast(t_game *game_st, t_raycast raycast);


#endif