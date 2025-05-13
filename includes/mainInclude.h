/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainInclude.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:32 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/13 14:58:19 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAININCLUDE_H
# define MAININCLUDE_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct
{
	void	*mlx_init;
	void	*mlx_windows;
	void	*mlx_img;
	char	*address;
	int		endian;
	int		line_length;
	int		bits_per_pixel;

}			minilibx_struct;

typedef struct
{
	double	x;
	double	y;
	double	dir;
	double	fov;
}			player_info;

/* Fonctions de dessin */
void		put_pixel(minilibx_struct *data, int x, int y, int color);
void		draw_line(minilibx_struct *mlx_struct, int x0, int y0, int x1,
				int y1, int color);
void		draw_rect(minilibx_struct *mlx_s, int x, int y, int width, int height, int color);
void		draw_filled_rect(minilibx_struct *mlx_s, int x, int y, int width, int height, int color);
void		draw_circle(minilibx_struct *mlx_s, int x, int y, int radius, int color);

/* Fonctions de parsing */
int			parse_map(char *path);
int			get_map(char *path, char ***map, int *height, int *width);
int			parse_inside_map(char **map, int h, int w);

#endif