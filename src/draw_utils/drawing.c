/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:25:31 by vorace32          #+#    #+#             */
/*   Updated: 2025/05/20 11:00:05 by qbarron          ###   ########.fr       */
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
			error = 1;
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

void	draw_floor_ceiling(t_game *game_st, int x)
{
	int	y;

	y = 0;
	while (y < game_st->mlx_struct.win_h / 2)
	{
		put_pixel(&game_st->mlx_struct, x, y, game_st->ceiling_color);
		y++;
	}
	y = game_st->mlx_struct.win_h / 2;
	while (y < game_st->mlx_struct.win_h)
	{
		put_pixel(&game_st->mlx_struct, x, y, game_st->floor_color);
		y++;
	}
}