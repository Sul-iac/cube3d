/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:02:11 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/16 19:10:39 by qbarron          ###   ########.fr       */
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
	int x;
	int draw_start;
	int draw_end;
	int hit;

	x = 0;
	hit = 0;
	printf("dimensions de la map %d x %d\n", game_st->map_w, game_st->map_h);
	printf("position du joueur: %f %f (int: %d, %d)\n", game_st->player.x, game_st->player.y,
       (int)game_st->player.x, (int)game_st->player.y);
	   

	if (raycast.map_x < 0 || raycast.map_x >= game_st->map_w ||
		raycast.map_y < 0 || raycast.map_y >= game_st->map_h)
		{
			printf("PLAYER STARTS OUT OF MAP! (%d, %d)\n", raycast.map_x, raycast.map_y);
			exit(1);
		}
		
		while(x < game_st->mlx_struct.win_w)
		{
			raycast.camera_x = 2 * x / (double)game_st->mlx_struct.win_w - 1;
			raycast.ray_dir_x = game_st->player.dir_x + raycast.plan_x * raycast.camera_x;
			if(raycast.ray_dir_x == 0)
				raycast.delta_dist_x = 1e30;
			else
				raycast.delta_dist_x = fabs(1.0 / raycast.ray_dir_x);
			raycast.ray_dir_y = game_st->player.dir_y + raycast.plan_y * raycast.camera_x;
			if(raycast.ray_dir_y == 0)
				raycast.delta_dist_y = 1e30;
			else
				raycast.delta_dist_y = fabs(1.0 / raycast.ray_dir_y);
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
			if (raycast.map_x < 0 || raycast.map_x >= game_st->map_w ||
					raycast.map_y < 0 || raycast.map_y >= game_st->map_h)
				{
					printf("OUT OF BOUNDS: map_x = %d, map_y = %d\n", raycast.map_x, raycast.map_y);
			    	exit(1);	
				}
			if (raycast.map_y < 0 || raycast.map_y >= game_st->map_h ||
					    raycast.map_x < 0 || raycast.map_x >= game_st->map_w)
				{
				    printf("OUT OF BOUNDS: map_x = %d, map_y = %d (map_w = %d, map_h = %d)\n",
				        raycast.map_x, raycast.map_y, game_st->map_w, game_st->map_h);
				    exit(1);
				}
			
			while(hit == 0) 
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
			
				if (raycast.map_x < 0 || raycast.map_x >= game_st->map_w ||
					raycast.map_y < 0 || raycast.map_y >= game_st->map_h)
				{
					printf("OUT OF BOUNDS WHILE DDA: map_x = %d, map_y = %d (map_w = %d, map_h = %d)\n",
						raycast.map_x, raycast.map_y, game_st->map_w, game_st->map_h);
					exit(1);
				}
				if(game_st->map[raycast.map_y][raycast.map_x] == '1')
					hit = 1;
			}
			if(raycast.side == 0)
				raycast.wall_dist = (raycast.side_dist_x - raycast.delta_dist_x);
			else
				raycast.wall_dist = (raycast.side_dist_y - raycast.delta_dist_y);
			if (raycast.wall_dist <= 0)
			{
				x++;
				continue;
			}
			raycast.line_h = (int)(game_st->mlx_struct.win_h / raycast.wall_dist);
			draw_start = -raycast.line_h / 2 + game_st->mlx_struct.win_h / 2;
			if(draw_start < 0)
				draw_start = 0;
			draw_end = raycast.line_h / 2 + game_st->mlx_struct.win_h / 2;
			if(draw_end >= game_st->mlx_struct.win_h)
				draw_end = game_st->mlx_struct.win_h - 1;
			int color = (raycast.side == 1) ? 0xAAAAAA : 0xFFFFFF;
			draw_vertical_line(&game_st->mlx_struct, x, draw_start, draw_end, color);
			x++;
	}
}
