/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:31:36 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/01 19:12:57 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int get_map(char *map) {
	int fd;

	fd = open(map, STDIN_FILENO);
	if(fd != 0) { 
		printf("Error: function get_map: open: cannot open map\n");
		return(-1);
	} else {
		
	}
}

int parse_map(char *map) {
	int i = 0;
	while(map[i]) {
		if(strncmp(map, ".cub", 4)) {
			get_map(map);
			return(0);
		} else {
			printf("Map must be <map>.cub\n");
			return(-1);
		}
	}
	return(-1);
}