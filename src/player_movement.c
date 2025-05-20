/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:30:42 by vorace32          #+#    #+#             */
/*   Updated: 2025/05/20 11:15:47 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int	key_press(int keycode, t_game *game_st)
{
	if (keycode == KEY_W)
		game_st->player.move_forward = 1;
	else if (keycode == KEY_S)
		game_st->player.move_backward = 1;
	else if (keycode == KEY_A)
		game_st->player.move_left = 1;
	else if (keycode == KEY_D)
		game_st->player.move_right = 1;
	else if(keycode == KEY_L)
		game_st->player.rotate_left = 1;
	else if(keycode == KEY_R)
		game_st->player.rotate_right = 1;
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	key_release(int keycode, t_game *game_st)
{
	if (keycode == KEY_W)
		game_st->player.move_forward = 0;
	else if (keycode == KEY_S)
		game_st->player.move_backward = 0;
	else if (keycode == KEY_A)
		game_st->player.move_left = 0;
	else if (keycode == KEY_D)
		game_st->player.move_right = 0;
	else if(keycode == KEY_L)
		game_st->player.rotate_left = 0;
	else if(keycode == KEY_R)
		game_st->player.rotate_right = 0;
	return (0);
}

int	is_wall(t_game *game_st, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_x >= game_st->map_w 
		|| map_y >= game_st->map_h)
		return (1);
	return (game_st->map[map_y][map_x] == '1');
}

void	update_player_position(t_game *game_st)
{
	float	new_x;
	float	new_y;
	float	old_dir_x;
	float	old_plane_x;

	if (game_st->player.move_forward)
	{
		new_x = game_st->player.x + game_st->player.dir_x * game_st->player.move_speed;
		new_y = game_st->player.y + game_st->player.dir_y * game_st->player.move_speed;
		if (!is_wall(game_st, new_x, game_st->player.y))
			game_st->player.x = new_x;
		if (!is_wall(game_st, game_st->player.x, new_y))
			game_st->player.y = new_y;
	}
	if (game_st->player.move_backward)
	{
		new_x = game_st->player.x - game_st->player.dir_x * game_st->player.move_speed;
		new_y = game_st->player.y - game_st->player.dir_y * game_st->player.move_speed;
		if (!is_wall(game_st, new_x, game_st->player.y))
			game_st->player.x = new_x;
		if (!is_wall(game_st, game_st->player.x, new_y))
			game_st->player.y = new_y;
	}
	if (game_st->player.move_left)
	{
		new_x = game_st->player.x - game_st->player.plane_x * game_st->player.move_speed;
		new_y = game_st->player.y - game_st->player.plane_y * game_st->player.move_speed;
		if (!is_wall(game_st, new_x, game_st->player.y))
			game_st->player.x = new_x;
		if (!is_wall(game_st, game_st->player.x, new_y))
			game_st->player.y = new_y;
	}
	if (game_st->player.move_right)
	{
		new_x = game_st->player.x + game_st->player.plane_x * game_st->player.move_speed;
		new_y = game_st->player.y + game_st->player.plane_y * game_st->player.move_speed;
		if (!is_wall(game_st, new_x, game_st->player.y))
			game_st->player.x = new_x;
		if (!is_wall(game_st, game_st->player.x, new_y))
			game_st->player.y = new_y;
	}
	if(game_st->player.rotate_left)
	{
		old_dir_x = game_st->player.dir_x;
		game_st->player.dir_x = game_st->player.dir_x * cos(ROT_SPEED) - game_st->player.dir_y * sin(ROT_SPEED);
		game_st->player.dir_y = old_dir_x * sin(ROT_SPEED) + game_st->player.dir_y * cos(ROT_SPEED);
		
		old_plane_x = game_st->player.plane_x;
		game_st->player.plane_x = game_st->player.plane_x * cos(ROT_SPEED) - game_st->player.plane_y * sin(ROT_SPEED);
		game_st->player.plane_y = old_plane_x * sin(ROT_SPEED) + game_st->player.plane_y * cos(ROT_SPEED);
	}
	if(game_st->player.rotate_right)
	{
		old_dir_x = game_st->player.dir_x;
		game_st->player.dir_x = game_st->player.dir_x * cos(-ROT_SPEED) - game_st->player.dir_y * sin(-ROT_SPEED);
		game_st->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game_st->player.dir_y * cos(-ROT_SPEED);

		old_plane_x = game_st->player.plane_x;
		game_st->player.plane_x = game_st->player.plane_x * cos(-ROT_SPEED) - game_st->player.plane_y * sin(-ROT_SPEED);
		game_st->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game_st->player.plane_y * cos(-ROT_SPEED);
	}
	game_st->px = (int)game_st->player.x;
	game_st->py = (int)game_st->player.y;
}
