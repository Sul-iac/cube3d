/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:25:31 by vorace32          #+#    #+#             */
/*   Updated: 2025/05/16 22:19:06 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

void put_pixel(minilibx_struct* data, int x, int y, int color) {
	char *dst;
	int error;
	
	error = 0;
	if (x < 0 || x >= (int)data->win_w || y < 0 || y >= (int)data->win_h)
	{
		if (!error)
		{
			// erreur si les coos sont en dehors de la fenetre -> ca devrait pas arrriver ^^
			error = 1;
		}
		return;
	}
	dst = data->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_vertical_line(minilibx_struct *mlx_s, int x, int y_start, int y_end, int color)
{
	int y;
	int tmp;
	
	if (y_start > y_end)
	{
		tmp = y_start;
		y_start = y_end;
		y_end = tmp;
	}
	y = y_start;
	while (y < y_end)
	{
		put_pixel(mlx_s, x, y, color);
		y++;
	}
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

void draw_circle(minilibx_struct *img, int grid_x, int grid_y, int col)
{
	int		px;
	int		py;
	float	cx;
	float	cy;
	float	radius;
	float	dx;
	float	dy;
	float	dist;

    py = 0;
    while (py < TILE)
    {
        px = 0;
        while (px < TILE)
        {
            dx = px + 0.5f - TILE / 2.0f;
            dy = py + 0.5f - TILE / 2.0f;
            dist = dx * dx + dy * dy;
            if (dist <= radius * radius)
                put_pixel(img, grid_x * TILE + px, grid_y * TILE + py, col);
            px++;
        }
        py++;
    }
}