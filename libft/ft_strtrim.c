/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:30:40 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/01 19:19:24 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim(const char *s1, int start, int end)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (end - start + 2));
	if (dest == NULL)
		return (NULL);
	while (start <= end)
	{
		dest[i] = s1[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*dest;

	start = 0;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	while (end >= start && ft_strchr(set, s1[end]))
		end--;
	if (start > end)
	{
		dest = (char *)malloc(1);
		if (dest == NULL)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	return (ft_trim(s1, start, end));
}
