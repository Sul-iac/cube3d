/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:31:36 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 11:13:45 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

static int is_map_line(char *src)
{
	int has_wall;

	has_wall = 0;
    while (*src && *src != '\n')
    {
        if (*src == '0' || *src == '1')
			has_wall = 1;
		else if(*src != 'N' && *src != 'S' && *src != 'E' && *src != 'W' && *src != ' ')
            return (0);
        src++;
    }
    return (has_wall);
}

int get_map(char *path, char ***map, int *height, int *width)
{
	int		fd;
	char	*get_line;
	tu_list *rows;
	tu_list *node_next_line;
	int 	len;
	int		in_map;

	in_map = 0;	
	rows = NULL;
	len = 0;
	*width = 0;
	*height = 0;
	fd = open(path, O_RDONLY);

	if(fd == -1)
		return(printf("Error: function get_map: open: cannot open map\n"), -1);
	get_line = get_next_line(fd);
	while(get_line)
	{
		if(!in_map)
		{
			if(is_map_line(get_line))
				in_map = 1;
			else
			{
				free(get_line);
				get_line = get_next_line(fd);
				continue;
			}
		}
		len = ft_strlen(get_line);
		if(len && get_line[len - 1] == '\n')
			len--;
		if(len > *width)
			*width = len;
		node_next_line = ft_lstnew(get_line);
		if(!node_next_line) 
		{
			printf("Error: function get_map: ft_lst_new error\n");
			close(fd);
			return(-1);
		}
		ft_lstadd_back(&rows, node_next_line);
		(*height)++;
		get_line = get_next_line(fd);
	}
	close(fd);
	*map = create_2d_map(*width, *height, &rows);
	return(0);
}

int parse_map(char *path, t_game *game_st)
{
	int len;

	game_st->floor_color = -1;
	game_st->ceiling_color = -1;
	len = ft_strlen(path);
	if(strncmp(path + len - 4, ".cub", 4) == 0)
	{
		if (parse_textures(path, game_st) == -1)
			return (printf("error: parse_map: error with texture parsing\n"), -1);
		if (parse_colors(path, game_st) == -1)
			return (printf("error: parse_map: error with color parsing\n"), -1);
		if(get_map(path, &game_st->map, &game_st->map_h, &game_st->map_w) == -1)
			return(printf("error: parse_map: cannot get_map\n"), -1);
		if(validate_map(game_st, game_st->map, game_st->map_h, game_st->map_w) == -1)
			return(printf("error: parse_map: invalid map\n"), -1);
		return(0);
	}
	printf("Map must be <map>.cub\n");
	return(-1);
}
