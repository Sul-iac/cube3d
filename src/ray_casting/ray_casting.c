/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:02:11 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 10:59:44 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mainInclude.h"

void	init_raycast_struct(t_raycast *raycast, t_game *game_st, int x)
{
	raycast->hit = 0;
	raycast->map_x = (int)game_st->player.x;
	raycast->map_y = (int)game_st->player.y;
	raycast->camera_x = 2 * x / (double)game_st->mlx_struct.win_w - 1;
	raycast->ray_dir_x = game_st->player.dir_x + game_st->player.plane_x * raycast->camera_x;
	raycast->ray_dir_y = game_st->player.dir_y + game_st->player.plane_y * raycast->camera_x;

} 

// init the delta (dist between two points in square)
// and init the vectors movements
void	init_2d_vector(t_raycast *raycast, t_game *game_st)
{
	init_delta_dist(raycast);
	if (raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (game_st->player.x - raycast->map_x) * raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - game_st->player.x) * raycast->delta_dist_x;
	}
	if (raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (game_st->player.y - raycast->map_y) * raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - game_st->player.y) * raycast->delta_dist_y;
	}
}

// calculate the vectr mvmt and detect if there
// a wall has been hit
void	dda_algorythm(t_raycast *raycast, t_game *game_st)
{
	while (raycast->hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		
		if (raycast->map_x < 0 || raycast->map_x >= game_st->map_w
			|| raycast->map_y < 0 || raycast->map_y >= game_st->map_h)
		{
			raycast->hit = 1;
			break ;
		}
		if (game_st->map[raycast->map_y][raycast->map_x] == '1')
			raycast->hit = 1;
	}
}

// render the dist from the camera plane to the wall
void	render_wall_dist(t_raycast *raycast, t_game *game_st, int x)
{
	if (raycast->hit == 1)
	{
		if (raycast->side == 0)
			raycast->wall_dist = (raycast->side_dist_x - raycast->delta_dist_x);
		else
			raycast->wall_dist = (raycast->side_dist_y - raycast->delta_dist_y);
		if (raycast->wall_dist > 0)
		{
			raycast->line_h = (int)(game_st->mlx_struct.win_h / raycast->wall_dist);
			raycast->draw_start = -raycast->line_h / 2 + game_st->mlx_struct.win_h / 2;
			if (raycast->draw_start < 0)
				raycast->draw_start = 0;
			raycast->draw_end = raycast->line_h / 2 + game_st->mlx_struct.win_h / 2;
			if (raycast->draw_end >= game_st->mlx_struct.win_h)
				raycast->draw_end = game_st->mlx_struct.win_h - 1;
			draw_wall_texture(game_st, x, raycast);
		}
	}
}

int	render_raycast(t_game *game_st)
{
	t_raycast	raycast;
	int			x;
	int			color;

	raycast.time = 0;
	raycast.old_time = 0;
	x = 0;
	while (x < game_st->mlx_struct.win_w)
	{
		draw_floor_ceiling(game_st, x);
		init_raycast_struct(&raycast, game_st, x);
		init_2d_vector(&raycast, game_st);
		dda_algorythm(&raycast, game_st);
		render_wall_dist(&raycast, game_st, x);
		x++;
	}
	return (0);
}
