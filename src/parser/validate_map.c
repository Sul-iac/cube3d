/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:48:36 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 13:24:33 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int	check_character(t_game *game_st)
{
	int		x;
	int		y;
	char	c;
	int		player_count;

	y = 0;
	player_count = 0;
	while (y < game_st->map_h)
	{
		if (character_position(game_st, &player_count, y) == -1)
			return (-1);
		y++;
	}
	if (player_count != 1)
		return (printf("error: %d player spawn\n", player_count), -1);
	return (0);
}

int	check_borders(t_game *game_st)
{
	int	i;
	int	j;

	j = -1;
	i = -1;
	while (++i < game_st->map_w)
	{
		if (game_st->map[0][i] != '1' && game_st->map[0][i] != ' ')
			return (printf("error: wall is open at [0, %d]\n", i), -1);
		if (game_st->map[game_st->map_h - 1][i] != '1'
			&& game_st->map[game_st->map_h - 1][i] != ' ')
			return (printf("error: wall is open at [%d, %d]\n", game_st->map_h
					- 1, i), -1);
	}
	while (++j < game_st->map_h)
	{
		if (game_st->map[j][0] != '1' && game_st->map[j][0] != ' ')
			return (printf("error: wall is open at [0, %d]\n", j), -1);
		if (game_st->map[j][game_st->map_w - 1] != '1'
			&& game_st->map[j][game_st->map_w - 1] != ' ')
			return (printf("error: wall is open at [%d, %d]\n", game_st->map_w
					- 1, j), -1);
	}
}

int	flood(char **map_copy, int x, int y, t_game *game_st)
{
	if (x < 0 || y < 0 || x >= game_st->map_w || y >= game_st->map_h)
		return (-1);
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return (0);
	if (map_copy[y][x] == ' ')
		return (-1);
	map_copy[y][x] = 'F';
	if (flood(map_copy, x + 1, y, game_st) == -1)
		return (-1);
	if (flood(map_copy, x - 1, y, game_st) == -1)
		return (-1);
	if (flood(map_copy, x, y + 1, game_st) == -1)
		return (-1);
	if (flood(map_copy, x, y - 1, game_st) == -1)
		return (-1);
	return (0);
}

int	check_closed(t_game *game_st)
{
	int		y;
	char	**copy;

	copy = (char **)malloc(sizeof(char *) * game_st->map_h);
	if (!copy)
		return (printf("error: check_closed malloc\n"), -1);
	y = 0;
	while (y < game_st->map_h)
	{
		copy[y] = ft_strdup(game_st->map[y]);
		if (!copy[y])
			return (printf("error: check_closed: ft_strdup\n"), -1);
		y++;
	}
	copy[game_st->py][game_st->px] = '0';
	if (flood(copy, game_st->px, game_st->py, game_st) == -1)
	{
		free_map(copy, game_st->map_h);
		return (printf("error: map not closed\n"), -1);
	}
	free_map(copy, game_st->map_h);
	return (0);
}

int	validate_map(t_game *game_st)
{
	if (check_character(game_st) == -1)
		return (-1);
	if (check_borders(game_st) == -1)
		return (-1);
	if (check_closed(game_st) == -1)
		return (-1);
	return (0);
}
