/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:16:07 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/02 16:34:01 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(tu_list **lst, tu_list *new)
{
	tu_list	*temp;

	if (lst)
	{
		if (!*lst)
			*lst = new;
		else
		{
			temp = ft_lstlast(*(lst));
			temp->next = new;
		}
	}
}
