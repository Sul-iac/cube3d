/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:56:28 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/16 17:27:32 by vorace32         ###   ########.fr       */
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

	center_x = 60;
	center_y = 60;
	py = 0;
	while (py < 120)
	{
		px = 0;
		while (px < 120)
		{
			put_pixel(mm, px, py, COL_EMPTY);
			px++;
		}
		py++;
	}
	py = 0;
	while (py < 120)
	{
		px = 0;
		while (px < 120)
		{
			dx = px - center_x;
			dy = py - center_y;
			if (dx * dx + dy * dy > 60 * 60)
			{
				px++;
				continue ;
			}
			map_x = player_x + dx / 25.0f;
			map_y = player_y + dy / 25.0f;
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
			put_pixel(mm, px, py, color);
			px++;
		}
		py++;
	}
	py = center_y - 2;
	while (py <= center_y + 2)
	{
		px = center_x - 2;
		while (px <= center_x + 2)
		{
			if ((px - center_x) * (px - center_x) + (py - center_y) * (py
					- center_y) <= 4)
				put_pixel(mm, px, py, COL_PLAYER);
			px++;
		}
		py++;
	}
	py = 0;
	while (py < 120)
	{
		px = 0;
		while (px < 120)
		{
			dx = px - center_x;
			dy = py - center_y;
			dist2 = dx * dx + dy * dy;
			if (dist2 >= (60 - 1) * (60 - 1)
				&& dist2 <= 60 * 60)
				put_pixel(mm, px, py, 0x00FFFFFF);
			px++;
		}
		py++;
	}
}
