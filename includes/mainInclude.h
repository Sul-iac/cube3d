/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainInclude.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:32 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/01 19:01:31 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAININCLUDE_H
# define MAININCLUDE_H

# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "../minilibx-linux/mlx.h"

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

int parse_map(char *map);
int get_map(char *map);


#endif