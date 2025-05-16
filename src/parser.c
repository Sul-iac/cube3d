/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:31:36 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/16 23:47:25 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

char	*ft_strcpy_and_fill(char *dest, char *src, int width, int len)
{
	int i; 

	i = -1;
	while(++i < len)
		dest[i] = src[i];		
	while(i < width)
	{
		dest[i] = ' ';
		i++;
	}
	dest[width] = '\0';
	return(dest);
}

char	**create_2d_map(int width, int height, tu_list **rows)
{
	int		y;
	int		len;
	char	*src;
	char	**map;
	tu_list *cur;

	y = 0;
	cur = *rows;
	len = 0;
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if(!map)
	{
		printf("error: created_2d_map: cannot allocate 2d map");
		return(NULL);
	}
	map[height] = NULL;
	while(cur) 
	{
		map[y] = (char *)malloc(width + 1);
		if(!map[y]) 
		{
			printf("error: created_2d_map: cannot allocate map[y]");
			return(NULL);
		}
		src = (char *)cur->content;
		len = ft_strlen(src);
		if(len && src[len - 1] == '\n')
			len--;
		ft_strcpy_and_fill(map[y], src, width, len);
		cur = cur->next;
		y++;
	}
	ft_lstclear(rows, free);
	return(map);
}

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

static int	extract_rgb(char *line)
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
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
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

static int	parse_colors(char *path, t_game *game_st)
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
		return (-1);
	return (0);
}

int parse_map(char *path, t_game *game_st)
{
	int len;

	game_st->floor_color = -1;
	game_st->ceiling_color = -1;
	len = ft_strlen(path);
	if(strncmp(path + len - 4, ".cub", 4) == 0)
	{
		if (parse_colors(path, game_st) == -1)
		{
			printf("error with color parsing\n");
			return (-1);
		}
		printf("map_w: %d\n", game_st->map_w);
		printf("map_h: %d\n", game_st->map_h);
		if(get_map(path, &game_st->map, &game_st->map_h, &game_st->map_w) == -1)
		{
			printf("error with get_map\n");
			return(-1);
		}
		if(validate_map(game_st, game_st->map, game_st->map_h, game_st->map_w) == -1)
			return(-1);
		return(0);
	}
	printf("Map must be <map>.cub\n");
	return(-1);
}
