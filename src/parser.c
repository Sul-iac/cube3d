/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:31:36 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/13 15:38:47 by qbarron          ###   ########.fr       */
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

int parse_map(char *path)
{
	int len;
	char **map;
	int	h;
	int	w;

	len = ft_strlen(path);
	if(strncmp(path + len - 4, ".cub", 4) == 0)
	{
		if(get_map(path, &map, &h, &w) == -1)
		{
			printf("error with get_map\n");
			return(-1);
		}
		if(validate_map(map, h, w) == -1)
			return(-1);
		return(0);
	}
	printf("Map must be <map>.cub\n");
	return(-1);
}
