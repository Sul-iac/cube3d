/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:28:41 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/13 15:24:48 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

void put_pixel(minilibx_struct* data, int x, int y, int color) {
	char *dst;

	dst = data->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_line(minilibx_struct *mlx_struct, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx;
	int sy;
	int err = dx + dy;
	int e2;

	if(x0 < x1) {
		sx = 1;
	} else {
		sx = -1;
	}

	if(y0 < y1) {
		sy = 1;
	} else {
		sy = -1;
	}

	while(1) {
		put_pixel(mlx_struct, x0, y0, color);
		if(x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if(e2 >= dy) {
			err += dy;
			x0	+= sx;
		}
		if(e2 <= dx) {
			err += dx;
			y0	+= sy;
		}
	}
}
