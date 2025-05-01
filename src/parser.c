/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:31:36 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/01 20:22:51 by qbarron          ###   ########.fr       */
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
		while(read_map = get_next_line(fd)) {
			if(!get_next_line(fd)) {
				printf("Error: function get_map: GNL error\n");
			}
			
		} 
	}
}

int parse_map(char *path) {
	int i = -1;
	int len;

	len = strlen(path);
	if(strncmp(path + len - 4, ".cub", 4)) {
		get_map(path);
		return(0);
	} else {
		printf("Map must be <map>.cub\n");
		return(-1);
	}
	return(-1);
}