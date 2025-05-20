/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_and_colors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:13:17 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 13:39:26 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mainInclude.h"

void	split_rgb(int *r, int *g, int *b, char **split)
{
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
}

int	extract_rgb(char *line)
{
	int		r;
	int		g;
	int		b;
	char	**split;
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (-1);
	split = ft_split(trimmed, ',');
	free(trimmed);
	if (!split || !split[0] || !split[1] || !split[2])
		return (-1);
	split_rgb(&r, &g, &b, split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		while (split && *split)
			free(*split++);
		free(split - 3);
		return (-1);
	}
	while (split && *split)
		free(*split++);
	free(split - 3);
	return (r << 16 | g << 8 | b);
}

void	init_path_texture(t_game *game_st, int fd)
{
	char	*tmp;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		tmp = line;
		while (*tmp && (*tmp == ' ' || *tmp == '\t'))
			tmp++;
		if (ft_strncmp(tmp, "NO ", 3) == 0)
			game_st->no_path = ft_strtrim(tmp + 2, " \t\n\r");
		else if (ft_strncmp(tmp, "SO ", 3) == 0)
			game_st->so_path = ft_strtrim(tmp + 2, " \t\n\r");
		else if (ft_strncmp(tmp, "WE ", 3) == 0)
			game_st->we_path = ft_strtrim(tmp + 2, " \t\n\r");
		else if (ft_strncmp(tmp, "EA ", 3) == 0)
			game_st->ea_path = ft_strtrim(tmp + 2, " \t\n\r");
		free(line);
		line = get_next_line(fd);
	}
}

int	parse_textures(char *path, t_game *game_st)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	init_path_texture(game_st, fd);
	close(fd);
	if (!game_st->no_path || !game_st->so_path || !game_st->we_path
		|| !game_st->ea_path)
		return (printf("error: parse_texture: missing texture path\n"), -1);
	return (0);
}

int	parse_colors(char *path, t_game *game_st)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		tmp = line;
		while (*tmp && (*tmp == ' ' || *tmp == '\t'))
			tmp++;
		if (*tmp == 'F' && *(tmp + 1) == ' ')
			game_st->floor_color = extract_rgb(tmp + 2);
		else if (*tmp == 'C' && *(tmp + 1) == ' ')
			game_st->ceiling_color = extract_rgb(tmp + 2);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game_st->floor_color == -1 || game_st->ceiling_color == -1)
		return (printf("error: parse_colors: no colors found\n"), -1);
	return (0);
}
