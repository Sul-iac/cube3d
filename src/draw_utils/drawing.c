/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:25:31 by vorace32          #+#    #+#             */
/*   Updated: 2025/05/16 19:26:31 by qbarron          ###   ########.fr       */
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