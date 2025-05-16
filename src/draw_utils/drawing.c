/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:25:31 by vorace32          #+#    #+#             */
/*   Updated: 2025/05/16 17:59:01 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

void put_pixel(minilibx_struct* data, int x, int y, int color) {
	char *dst;

	if (x < 0 || x >= (int)data->win_w || y < 0 || y >= (int)data->win_h)
	{
		printf("OUT OF BOUNDS: x=%d y=%d (image=%d x %d)\n", x, y, data->win_w, data->win_h);		
		return;
	}
	dst = data->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_vertical_line(minilibx_struct *mlx_s, int x, int y_start, int y_end, int color)
{
	int y;
	int tmp;
	
	y = y_start;
	if (y_start > y_end)
	{
		tmp = y_start;
		y_start = y_end;
		y_end = tmp;
	}
	for(int y = y_start; y < y_end; y++)
		put_pixel(mlx_s, x, y_end, color);
}


// void draw_line(minilibx_struct *mlx_s, int x0, int y0, int x1, int y1, int color) {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	int sx = x0 < x1 ? 1 : -1;
// 	int sy = y0 < y1 ? 1 : -1;
// 	int err = (dx > dy ? dx : -dy) / 2;
// 	int e2;

// 	while (1)
// 	{
// 		put_pixel(mlx_s, x0, y0, color);
// 		if (x0 == x1 && y0 == y1)
// 			break;
// 		e2 = err;
// 		if (e2 > -dx)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 < dy)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

// void draw_rect(minilibx_struct *mlx_s, int x, int y, int width, int height, int color)
// {
// 	draw_line(mlx_s, x, y, x + width, y, color);
// 	draw_line(mlx_s, x + width, y, x + width, y + height, color);
// 	draw_line(mlx_s, x + width, y + height, x, y + height, color);
// 	draw_line(mlx_s, x, y + height, x, y, color);
// }

// void draw_filled_rect(minilibx_struct *mlx_s, int x, int y, int width, int height, int color)
// {
// 	for (int i = 0; i < height; i++)
// 	{
// 		draw_line(mlx_s, x, y + i, x + width, y + i, color);
// 	}
// }

// void draw_circle(minilibx_struct *mlx_s, int x, int y, int radius, int color)
// {
// 	for (int i = 0; i < 360; i++)
// 	{
// 		draw_line(mlx_s, x, y, x + radius * cos(i), y + radius * sin(i), color);
// 	}
// }