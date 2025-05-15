/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:30:42 by vorace32          #+#    #+#             */
/*   Updated: 2025/05/15 15:14:59 by vorace32         ###   ########.fr       */
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
	return (0);
}

static int	is_wall(t_game *game_st, float x, float y)
{
	int	map_x;
	int	map_y;

    // juste on check si on est pas en dehors de la map ou si on est sur une case 1 dans la nouvelle pos
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

	// jsuis oblige de faire un hook pour voir si une touche est enfoncee ou non
	// jai ajoute le check de wall, ca marche sur la mini map mais il faudra voir si ca marche sur la vrai map

	if (game_st->player.move_forward)
	{
		new_x = game_st->player.x + game_st->player.dir_x * game_st->player.move_speed;
		new_y = game_st->player.y + game_st->player.dir_y * game_st->player.move_speed;
		// on calcul la nouvelle position du joueur avant de deplacer pour le check wall 
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
	if (game_st->player.move_right)
	{
		new_x = game_st->player.x + game_st->player.dir_y * game_st->player.move_speed;
		new_y = game_st->player.y - game_st->player.dir_x * game_st->player.move_speed;
		if (!is_wall(game_st, new_x, game_st->player.y))
			game_st->player.x = new_x;
		if (!is_wall(game_st, game_st->player.x, new_y))
			game_st->player.y = new_y;
	}
	if (game_st->player.move_left)
	{
		new_x = game_st->player.x - game_st->player.dir_y * game_st->player.move_speed;
		new_y = game_st->player.y + game_st->player.dir_x * game_st->player.move_speed;
		if (!is_wall(game_st, new_x, game_st->player.y))
			game_st->player.x = new_x;
		if (!is_wall(game_st, game_st->player.x, new_y))
			game_st->player.y = new_y;
	}
	// on update la position du joueur 
	game_st->px = (int)game_st->player.x;
	game_st->py = (int)game_st->player.y;
} 
