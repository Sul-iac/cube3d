/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:10:19 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 13:22:16 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mainInclude.h"

void	free_map(char **map, int h)
{
	int	i;

	i = 0;
	while (i < h)
		free(map[i++]);
	free(map);
}

int	character_position(t_game *game_st, int *player_count, int y)
{
	char	c;
	int		x;

	x = 0;
	while (++x < game_st->map_w)
	{
		c = game_st->map[y][x];
		if (c == '0' || c == '1' || c == ' ')
			;
		else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		{
			game_st->px = x;
			game_st->py = y;
			game_st->pdir = c;
			(*player_count)++;
		}
		else
			return (printf("error: invalid char %c at [%d, %d]\n", c, y, x),
				-1);
	}
}
