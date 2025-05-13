/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainInclude.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:32 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/13 14:55:44 by qbarron          ###   ########.fr       */
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

typedef struct {
	void	*mlx_init;
	void	*mlx_windows;
	void	*mlx_img;
	char	*address;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
	
}				minilibx_struct;

void put_pixel(minilibx_struct* data, int x, int y, int color);
void ft_minilibx_init();
void draw_line(minilibx_struct *mlx_struct, int x0, int y0, int x1, int y1, int color);

int parse_map(char *path);
int get_map(char *path, char ***map, int *height, int *width);
int validate_map(char **map, int h, int w);
int check_closed(char **map, int width, int height, int px, int py);
int flood(char **map_copy, int x, int y, int w, int h);
int check_borders(char **map, int width, int height);
int check_character(char **map, int w, int h, int *px, int *py, int *pdir);
static int is_map_line(char *s);


#endif