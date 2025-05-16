/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:25:31 by vorace32          #+#    #+#             */
/*   Updated: 2025/05/16 17:11:41 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

void put_pixel(minilibx_struct* data, int x, int y, int color) {
	char *dst;

	dst = data->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_line(minilibx_struct *mlx_s, int x0, int y0, int x1, int y1, int color) {
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		put_pixel(mlx_s, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_rect(minilibx_struct *mlx_s, int x, int y, int width, int height, int color)
{
	draw_line(mlx_s, x, y, x + width, y, color);
	draw_line(mlx_s, x + width, y, x + width, y + height, color);
	draw_line(mlx_s, x + width, y + height, x, y + height, color);
	draw_line(mlx_s, x, y + height, x, y, color);
}

void draw_filled_rect(minilibx_struct *mlx_s, int x, int y, int width, int height, int color)
{
	for (int i = 0; i < height; i++)
	{
		draw_line(mlx_s, x, y + i, x + width, y + i, color);
	}
}

void draw_circle(minilibx_struct *img, int grid_x, int grid_y, int col)
{
    int px, py;
    float cx = grid_x * TILE + TILE / 2.0f;
    float cy = grid_y * TILE + TILE / 2.0f;
    float radius = TILE / 2.0f - 1.0f;
    float dx, dy, dist;

    for (py = 0; py < TILE; py++)
    {
        for (px = 0; px < TILE; px++)
        {
            dx = px + 0.5f - TILE / 2.0f;
            dy = py + 0.5f - TILE / 2.0f;
            dist = dx * dx + dy * dy;
            if (dist <= radius * radius)
                put_pixel(img, grid_x * TILE + px, grid_y * TILE + py, col);
        }
    }
}