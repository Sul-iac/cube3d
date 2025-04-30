/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainInclude.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:25:32 by qbarron           #+#    #+#             */
/*   Updated: 2025/04/30 13:01:11 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAININCLUDE_H
# define MAININCLUDE_H
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"

typedef struct {
	void	*mlx_init;
	void	*mlx_windows;
	void	*mlx_img;
	char	*address;
	int		endian;
	int		line_length;
	int		bits_per_pixel;
	
}				minilibx_struct;

void put_pixel(minilibx_struct* data, int x, int y, int color);
void ft_minilibx_init();




#endif