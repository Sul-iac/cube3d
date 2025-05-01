/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:31:36 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/01 20:13:06 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int get_map(char *map) {
	int fd;
	char* read_map;
	
	fd = open(map, O_RDONLY);
	if(fd == -1) { 
		printf("Error: function get_map: open: cannot open map\n");
		return(-1);
	} else {
		read_map = get_next_line(fd);
	}
}

int parse_map(char *path) {
	int i = -1;
	while(path[++i]) {
		if(strncmp(path, ".cub", 4)) {
			get_map(path);
			return(0);
		} else {
			printf("Map must be <map>.cub\n");
			return(-1);
		}
	}
	return(-1);
}