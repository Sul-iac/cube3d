/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_2d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:09:40 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 11:10:07 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mainInclude.h"

char	*ft_strcpy_and_fill(char *dest, char *src, int width, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		dest[i] = src[i];
	while (i < width)
	{
		dest[i] = ' ';
		i++;
	}
	dest[width] = '\0';
	return (dest);
}

void	malloc_and_send_map(tu_list *cur, char **map, int width)
{
	int		y;
	int		len;
	char	*src;

	y = 0;
	len = 0;
	while (cur)
	{
		map[y] = (char *)malloc(width + 1);
		if (!map[y])
		{
			printf("error: created_2d_map: cannot allocate map[y]");
			return ;
		}
		src = (char *)cur->content;
		len = ft_strlen(src);
		if (len && src[len - 1] == '\n')
			len--;
		ft_strcpy_and_fill(map[y], src, width, len);
		cur = cur->next;
		y++;
	}
}

char	**create_2d_map(int width, int height, tu_list **rows)
{
	int		y;
	int		len;
	char	*src;
	char	**map;
	tu_list	*cur;

	cur = *rows;
	len = 0;
	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (printf("error: created_2d_map: cannot allocate 2d map"), NULL);
	malloc_and_send_map(cur, map, width);
	map[height] = NULL;
	ft_lstclear(rows, free);
	return (map);
}
