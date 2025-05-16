/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:02:11 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/16 15:47:55 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mainInclude.h"

int render_raycast(t_game *game_st)
{
	t_raycast raycast;
	
	raycast.plan_x		= 0;
	raycast.plan_y		= 0.66;
	raycast.time		= 0;
	raycast.old_time	= 0;
	raycast.map_x		= (int)game_st->player.x;
	raycast.map_y		= (int)game_st->player.y;
	raycast.hit			= 0;

	int x;
	x = 0;
	while(x < game_st->mini_map.win_w)
	{
		raycast.camera_x = 2 * x / (double)game_st->mini_map.win_w - 1;
		raycast.ray_dir_x = game_st->player.dir_x + raycast.plan_x * raycast.camera_x;
		if(raycast.ray_dir_x == 0)
			raycast.delta_dist_x = 1e30;
		else
			raycast.delta_dist_x = fabs(1 / raycast.ray_dir_x);
		raycast.ray_dir_y = game_st->player.dir_y + raycast.plan_y * raycast.camera_x;
		if(raycast.ray_dir_y == 0)
			raycast.delta_dist_y = 1e30;
		else
			raycast.delta_dist_y = fabs(1 / raycast.ray_dir_y);
		if(raycast.delta_dist_x < 0)
		{
			raycast.step_x = -1;
			raycast.side_dist_x = (game_st->player.x - raycast.map_x) * raycast.delta_dist_x;
		}
		else
		{
			raycast.step_x = 1;
			raycast.side_dist_x = (raycast.map_x + 1.0 - game_st->player.x) * raycast.delta_dist_x;
		}
		if(raycast.delta_dist_y < 0)
		{
			raycast.step_y = -1;
			raycast.side_dist_y = (game_st->player.y - raycast.map_y) * raycast.delta_dist_y;
		}
		else
		{
			raycast.step_y = 1;
			raycast.side_dist_y = (raycast.map_y + 1.0 - game_st->player.y) * raycast.delta_dist_y;
		}
		while(raycast.hit == 0) 
		{
			if(raycast.side_dist_x < raycast.side_dist_y)
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
			if(game_st->map[raycast.map_x][raycast.map_y] > 0)
				raycast.hit = 1;
		}
		x++;
	}
}
