/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:31:36 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 13:39:04 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int	is_map_line(char *src)
{
	int	has_wall;

	has_wall = 0;
	while (*src && *src != '\n')
	{
		if (*src == '0' || *src == '1')
			has_wall = 1;
		else if (*src != 'N' && *src != 'S' && *src != 'E' && *src != 'W'
			&& *src != ' ')
			return (0);
		src++;
	}
	return (has_wall);
}

void	init_get_map_struct(t_get_map *get_map, char *path)
{
	get_map->in_map = 0;
	get_map->rows = NULL;
	get_map->node_next_line = NULL;
	get_map->len = 0;
	get_map->fd = open(path, O_RDONLY);
	if (get_map->fd == -1)
	{
		printf("Error: function get_map: open: cannot open map\n");
		return ;
	}
	get_map->get_line = get_next_line(get_map->fd);
}

int	get_line_to_list(t_get_map *get_map, int *width, int *height)
{
	get_map->len = ft_strlen(get_map->get_line);
	if (get_map->len && get_map->get_line[get_map->len - 1] == '\n')
		get_map->len--;
	if (get_map->len > *width)
		*width = get_map->len;
	get_map->node_next_line = ft_lstnew(get_map->get_line);
	if (!get_map->node_next_line)
	{
		printf("error: function get_line_to_list: ft_lst_new error\n");
		close(get_map->fd);
		return (-1);
	}
	ft_lstadd_back(&get_map->rows, get_map->node_next_line);
	(*height)++;
	get_map->get_line = get_next_line(get_map->fd);
}

int	get_map(char *path, char ***map, int *height, int *width)
{
	t_get_map	get_map;

	*width = 0;
	*height = 0;
	init_get_map_struct(&get_map, path);
	while (get_map.get_line)
	{
		if (!get_map.in_map)
		{
			if (is_map_line(get_map.get_line))
				get_map.in_map = 1;
			else
			{
				free(get_map.get_line);
				get_map.get_line = get_next_line(get_map.fd);
				continue ;
			}
		}
		get_line_to_list(&get_map, width, height);
	}
	close(get_map.fd);
	*map = create_2d_map(*width, *height, &get_map.rows);
	return (0);
}

int	parse_map(char *path, t_game *game_st)
{
	int	len;

	game_st->floor_color = -1;
	game_st->ceiling_color = -1;
	len = ft_strlen(path);
	if (strncmp(path + len - 4, ".cub", 4) == 0)
	{
		if (parse_textures(path, game_st) == -1)
			return (printf("error: parse_map: error with texture parsing\n"),
				-1);
		if (parse_colors(path, game_st) == -1)
			return (printf("error: parse_map: error with color parsing\n"), -1);
		if (get_map(path, &game_st->map, &game_st->map_h,
				&game_st->map_w) == -1)
			return (printf("error: parse_map: cannot get_map\n"), -1);
		if (validate_map(game_st) == -1)
			return (printf("error: parse_map: invalid map\n"), -1);
		return (0);
	}
	printf("Map must be <map>.cub\n");
	return (-1);
}
