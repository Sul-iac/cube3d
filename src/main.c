/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:37:03 by qbarron           #+#    #+#             */
/*   Updated: 2025/04/30 13:01:46 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

void put_pixel(minilibx_struct* data, int x, int y, int color) {
	char *dst;

	dst = data->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void ft_minilibx_init() {
	minilibx_struct mlx_s;
	mlx_s.mlx_init = mlx_init();
	mlx_s.mlx_windows = mlx_new_window(mlx_s.mlx_init, 900, 700, "Cube3D");
	mlx_s.mlx_img = mlx_new_image(mlx_s.mlx_init, 900, 700);
	mlx_s.address = mlx_get_data_addr(mlx_s.mlx_img, &mlx_s.bits_per_pixel,
										 &mlx_s.line_length, &mlx_s.endian);
	put_pixel(&mlx_s, 5, 5, 0x00FF0000);
	for (int x = 50; x < 200; ++x)
		put_pixel(&mlx_s, x, 50, 0x00FFFFFF);
	mlx_put_image_to_window(mlx_s.mlx_init, mlx_s.mlx_windows, mlx_s.mlx_img, 0, 0);
	mlx_loop(mlx_s.mlx_init);
}

int main() {
	ft_minilibx_init();
}