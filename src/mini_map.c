/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:56:28 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/17 00:39:22 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

static void	draw_tile(minilibx_struct *img, int grid_x, int grid_y, int col)
{
	int	px;
	int	py;

	py = 0;
	while (py < TILE)
	{
		px = 0;
		while (px < TILE)
		{
			put_pixel(img, grid_x * TILE + px, grid_y * TILE + py, col);
			px++;
		}
		py++;
	}
}

void	render_minimap(char **map, int w, int h, minilibx_struct *mm,
		float player_x, float player_y)
{
	int		px;
	int		py;
	int		center_x;
	int		center_y;
	float	map_x;
	float	map_y;
	int		tile_x;
	int		tile_y;
	int		color;
	int		dx;
	int		dy;
	int		dist2;
	int		radius;
	int		screen_x;
	int		screen_y;

	screen_x = 80;
	screen_y = 80;
	radius = 60;
	center_x = 0;
	center_y = 0;

	py = -radius;
	while (py <= radius)
	{
		px = -radius;
		while (px <= radius)
		{
			dx = px;
			dy = py;
			if (dx * dx + dy * dy > radius * radius)
			{
				px++;
				continue;
			}
			map_x = player_x + px / 15.0f;
			map_y = player_y + py / 15.0f;
			tile_x = (int)map_x;
			tile_y = (int)map_y;
			if (tile_x < 0 || tile_y < 0 || tile_x >= w || tile_y >= h)
				color = COL_EMPTY;
			else if (map[tile_y][tile_x] == '1')
				color = COL_WALL;
			else if (map[tile_y][tile_x] == '0' || map[tile_y][tile_x] == 'N'
				|| map[tile_y][tile_x] == 'S' || map[tile_y][tile_x] == 'E'
				|| map[tile_y][tile_x] == 'W')
				color = COL_FLOOR;
			else
				color = COL_EMPTY;
			put_pixel(mm, screen_x + px, screen_y + py, color);
			px++;
		}
		py++;
	}
	
	py = -2;
	while (py <= 2)
	{
		px = -2;
		while (px <= 2)
		{
			if (px * px + py * py <= 4)
				put_pixel(mm, screen_x + px, screen_y + py, COL_PLAYER);
			px++;
		}
		py++;
	}
	
	py = -radius;
	while (py <= radius)
	{
		px = -radius;
		while (px <= radius)
		{
			dx = px;
			dy = py;
			dist2 = dx * dx + dy * dy;
			if (dist2 >= (radius - 1) * (radius - 1) && dist2 <= radius * radius)
				put_pixel(mm, screen_x + px, screen_y + py, 0x00FFFFFF);
			px++;
		}
		py++;
	}
}
