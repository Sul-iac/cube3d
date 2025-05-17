/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:25:31 by vorace32          #+#    #+#             */
/*   Updated: 2025/05/17 09:57:51 by qbarron          ###   ########.fr       */
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
			// (fils de pute avec des chapeau chapeau de grosse merde la, pointeur de merde) 
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