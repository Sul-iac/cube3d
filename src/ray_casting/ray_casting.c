/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:02:11 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/17 15:35:01 by qbarron          ###   ########.fr       */
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

void	draw_wall_texture(t_game *game_st, int x, t_raycast *raycast)
{
	t_texture	*tex;
	double		wall_x;
	int			tex_x; 
	int			tex_y;
	int			color;
	int			y;
	int			d;


	if (raycast->side == 0 && raycast->ray_dir_x < 0)
		tex = &game_st->we;
	else if (raycast->side == 0 && raycast->ray_dir_x >= 0)
		tex = &game_st->ea;
	else if (raycast->side == 1 && raycast->ray_dir_y < 0)
		tex = &game_st->no;
	else
		tex = &game_st->so;
	if (raycast->side == 0)
		wall_x = game_st->player.y + raycast->wall_dist * raycast->ray_dir_y;
	else
		wall_x = game_st->player.x + raycast->wall_dist * raycast->ray_dir_x;
	wall_x -= floor(wall_x);

	tex_x = (int)(wall_x * (double)tex->width);
	if ((raycast->side == 0 && raycast->ray_dir_x > 0)
		|| (raycast->side == 1 && raycast->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;

	y = raycast->draw_start;
	while (y < raycast->draw_end)
	{
		d = y * 256 - game_st->mlx_struct.win_h * 128 + raycast->line_h * 128;
		tex_y = ((d * tex->height) / raycast->line_h) / 256;
		color = *(int *)(tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8)));
		if (raycast->side == 1)
			color = (color >> 1) & 0x7F7F7F; // ombre sur mur NS
		put_pixel(&game_st->mlx_struct, x, y, color);
		y++;
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
				raycast.draw_start = -raycast.line_h / 2 + game_st->mlx_struct.win_h / 2;
				if (raycast.draw_start < 0)
					raycast.draw_start = 0;
				raycast.draw_end = raycast.line_h / 2 + game_st->mlx_struct.win_h / 2;
				if (raycast.draw_end >= game_st->mlx_struct.win_h)
					raycast.draw_end = game_st->mlx_struct.win_h - 1;
				draw_wall_texture(game_st, x, &raycast);
			}
		}
		x++;
	}
	return (0);
}
