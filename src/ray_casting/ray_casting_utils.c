/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:25:17 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 13:42:52 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mainInclude.h"

// init the delta dist (dist between two points in a square)
void	init_delta_dist(t_raycast *raycast)
{
	if (raycast->ray_dir_x == 0)
		raycast->delta_dist_x = 1e30;
	else
		raycast->delta_dist_x = fabs(1.0 / raycast->ray_dir_x);
	if (raycast->ray_dir_y == 0)
		raycast->delta_dist_y = 1e30;
	else
		raycast->delta_dist_y = fabs(1.0 / raycast->ray_dir_y);
}

void	draw_pixel_wall(t_raycast *raycast, t_game *game_st, t_texture *tex,
		int x)
{
	while (tex->y < raycast->draw_end)
	{
		tex->d = tex->y * 256 - game_st->mlx_struct.win_h * 128
			+ raycast->line_h * 128;
		tex->tex_y = ((tex->d * tex->height) / raycast->line_h) / 256;
		if (raycast->line_h == 0)
			return ;
		if (tex->tex_x < 0 || tex->tex_x >= tex->width || tex->tex_y < 0
			|| tex->tex_y >= tex->height)
		{
			tex->y++;
			continue ;
		}
		tex->color = *(int *)(tex->addr + (tex->tex_y * tex->line_len
					+ tex->tex_x * (tex->bpp / 8)));
		if (raycast->side == 1)
			tex->color = (tex->color >> 1) & 0x7F7F7F;
		put_pixel(&game_st->mlx_struct, x, tex->y, tex->color);
		tex->y++;
	}
}

void	init_texture_direction(t_raycast *raycast, t_game *game_st,
			t_texture *tex, int x)
{
	if (raycast->side == 0 && raycast->ray_dir_x < 0)
		tex = &game_st->we;
	else if (raycast->side == 0 && raycast->ray_dir_x >= 0)
		tex = &game_st->ea;
	else if (raycast->side == 1 && raycast->ray_dir_y < 0)
		tex = &game_st->no;
	else
		tex = &game_st->so;
	if (raycast->side == 0)
		tex->wall_x = game_st->player.y + raycast->wall_dist
			* raycast->ray_dir_y;
	else
		tex->wall_x = game_st->player.x + raycast->wall_dist
			* raycast->ray_dir_x;
	tex->wall_x -= floor(tex->wall_x);
	tex->tex_x = (int)(tex->wall_x * (double)tex->width);
	if ((raycast->side == 0 && raycast->ray_dir_x > 0) || (raycast->side == 1
			&& raycast->ray_dir_y < 0))
		tex->tex_x = tex->width - tex->tex_x - 1;
	tex->y = raycast->draw_start;
	if (!tex || !tex->addr)
		return ;
	draw_pixel_wall(raycast, game_st, tex, x);
}

void	draw_wall_texture(t_game *game_st, int x, t_raycast *raycast)
{
	t_texture	*tex;

	init_texture_direction(raycast, game_st, tex, x);
}
