/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:02:11 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/17 09:26:35 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mainInclude.h"

static void	draw_floor_ceiling(t_game *game_st, int x)
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

int	render_raycast(t_game *game_st)
{
	t_raycast	raycast;
	int			x;
	int			draw_start;
	int			draw_end;
	int			color;

	raycast.time = 0;
	raycast.old_time = 0;
	x = 0;
	while (x < game_st->mlx_struct.win_w)
	{
		// on rentre 
		draw_floor_ceiling(game_st, x);
		raycast.hit = 0;
		raycast.map_x = (int)game_st->player.x;
		raycast.map_y = (int)game_st->player.y;
		raycast.camera_x = 2 * x / (double)game_st->mlx_struct.win_w - 1;
		raycast.ray_dir_x = game_st->player.dir_x + game_st->player.plane_x * raycast.camera_x;
		raycast.ray_dir_y = game_st->player.dir_y + game_st->player.plane_y * raycast.camera_x;

		if (raycast.ray_dir_x == 0)
			raycast.delta_dist_x = 1e30;
		else
			raycast.delta_dist_x = fabs(1.0 / raycast.ray_dir_x); // chepa si on a le droit a fabs?
		if (raycast.ray_dir_y == 0)
			raycast.delta_dist_y = 1e30;
		else
			raycast.delta_dist_y = fabs(1.0 / raycast.ray_dir_y);
		
		if (raycast.ray_dir_x < 0)
		{
			raycast.step_x = -1;
			raycast.side_dist_x = (game_st->player.x - raycast.map_x) * raycast.delta_dist_x;
		}
		else
		{
			raycast.step_x = 1;
			raycast.side_dist_x = (raycast.map_x + 1.0 - game_st->player.x) * raycast.delta_dist_x;
		}
		if (raycast.ray_dir_y < 0)
		{
			raycast.step_y = -1;
			raycast.side_dist_y = (game_st->player.y - raycast.map_y) * raycast.delta_dist_y;
		}
		else
		{
			raycast.step_y = 1;
			raycast.side_dist_y = (raycast.map_y + 1.0 - game_st->player.y) * raycast.delta_dist_y;
		}

		while (raycast.hit == 0)
		{
			if (raycast.side_dist_x < raycast.side_dist_y)
			{
				raycast.side_dist_x += raycast.delta_dist_x;
				raycast.map_x += raycast.step_x;
				raycast.side = 0;
			}
			else
			{
				raycast.side_dist_y += raycast.delta_dist_y;
				raycast.map_y += raycast.step_y;
				raycast.side = 1;
			}
			
			if (raycast.map_x < 0 || raycast.map_x >= game_st->map_w
				|| raycast.map_y < 0 || raycast.map_y >= game_st->map_h)
				break ;
			if (game_st->map[raycast.map_y][raycast.map_x] == '1')
				raycast.hit = 1;
		}

		if (raycast.hit == 1)
		{
			if (raycast.side == 0)
				raycast.wall_dist = (raycast.side_dist_x - raycast.delta_dist_x);
			else
				raycast.wall_dist = (raycast.side_dist_y - raycast.delta_dist_y);
			
			if (raycast.wall_dist > 0)
			{
				raycast.line_h = (int)(game_st->mlx_struct.win_h / raycast.wall_dist);
				draw_start = -raycast.line_h / 2 + game_st->mlx_struct.win_h / 2;
				if (draw_start < 0)
					draw_start = 0;
				draw_end = raycast.line_h / 2 + game_st->mlx_struct.win_h / 2;
				if (draw_end >= game_st->mlx_struct.win_h)
					draw_end = game_st->mlx_struct.win_h - 1;

				color = (raycast.side == 1) ? 0xAAAAAA : 0xFFFFFF;
				draw_vertical_line(&game_st->mlx_struct, x, draw_start, draw_end, color);
			}
		}
		x++;
	}
	return (0);
}
