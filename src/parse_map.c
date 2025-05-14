/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:56:40 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/14 11:55:01 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int check_character(char **map, int w, int h, int *px, int *py, char *pdir)
{
	int		x;
	int		y;
	char	c;
	int		player_count;

	y = 0;
	player_count = 0;
	while(y < h)
	{
		x = 0;
		while(x < w)
		{
			c = map[y][x];
			if(c == '0' || c == '1' || c == ' ')
				;
			else if(c == 'N' || c == 'E' || c == 'S' || c == 'W') 
			{
				*px = x;
				*py = y;
				*pdir = c;
				player_count++;
			}
			else
				return(printf("error: invalid char %c at [%d, %d]\n", c, y, x), -1);
			x++;
		}
		y++;
	}
	if(player_count != 1)
		return(printf("error: %d player spawn\n", player_count), -1);
	return(0);
}

int check_borders(char **map, int width, int height)
{
	int i;
	int j;

	j = -1;
	i = -1;
	while(++i < width)
	{
		if(map[0][i] != '1' && map[0][i] != ' ')
			return(printf("error: wall is open at [0, %d]\n", i), -1);
		if(map[height - 1][i] != '1' && map[height - 1][i] != ' ')
			return(printf("error: wall is open at [%d, %d]\n", height - 1, i), -1);
	}
	while(++j < height)
	{
		if(map[j][0] != '1' && map[j][0] != ' ')
			return(printf("error: wall is open at [0, %d]\n", j), -1);
		if(map[j][width - 1] != '1' && map[j][width - 1] != ' ')
			return(printf("error: wall is open at [%d, %d]\n", width - 1, j), -1);
	}
}

int flood(char **map_copy, int x, int y, int w, int h)
{
	if(x < 0 || y < 0 || x >= w || y >= h) 
		return(-1);
	if(map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return(0);
	if(map_copy[y][x] == ' ')
		return(-1);

	map_copy[y][x] = 'F';
	if (flood(map_copy, x + 1, y, w, h) == -1)
		return (-1);
    if (flood(map_copy, x - 1, y, w, h) == -1)
		return (-1);
    if (flood(map_copy, x, y + 1, w, h) == -1)
		return (-1);
    if (flood(map_copy, x, y - 1, w, h) == -1)
		return (-1);
    return (0);
}

int check_closed(char **map, int width, int height, int px, int py)
{
	int		y;
	char	**copy;
	
	copy = (char **)malloc(sizeof(char *) * height);
	if(!copy)
		return(printf("error: check_closed malloc\n"), -1);
	y = 0;
	while(y < height)
	{
		copy[y] = ft_strdup(map[y]);
		if(!copy[y])
			return(printf("error: check_closed: ft_strdup\n"), -1);
		y++;
	}
	copy[py][px] = '0';
	if(flood(copy, px, py, width, height) == -1)
		return(printf("error: map not closed\n"), -1);
	y = 0;
	while(y < height)
		free(copy[y++]);
	free(copy);
	return(0);
}

int validate_map(t_game *game_st, char **map, int h, int w)
{
	if(check_character(map, w, h, &game_st->px, &game_st->py, &game_st->pdir) == -1)
		return(-1);
	if(check_borders(map, w, h) == -1)
		return(-1);
	if(check_closed(map, w, h, game_st->px, game_st->py) == -1)
		return(-1);
	return(0);
}
