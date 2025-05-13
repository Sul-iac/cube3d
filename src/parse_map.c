/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:56:40 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/13 12:10:23 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int parse_inside_map(char ***map, int *h, int *w) {
	for(int i = 0; i < h; i++) {
		printf("%s", map[i]);
	}
}