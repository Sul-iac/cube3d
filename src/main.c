/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:37:03 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/01 14:25:30 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

void put_pixel(minilibx_struct* data, int x, int y, int color) {
	char *dst;

	dst = data->address + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_line(minilibx_struct *mlx_struct, int x0, int y0, int x1, int y1, int color) {
	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx;
	int sy;
	int err = dx + dy;
	int e2;

	if(x0 < x1) {
		sx = 1;
	} else {
		sx = -1;
	}

	if(y0 < y1) {
		sy = 1;
	} else {
		sy = -1;
	}

	while(1) {
		put_pixel(mlx_struct, x0, y0, color);
		if(x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if(e2 >= dy) {
			err += dy;
			x0	+= sx;
		}
		if(e2 <= dx) {
			err += dx;
			y0	+= sy;
		}
	}
}

void draw_cube(minilibx_struct mlx_s, int x, int y, int s, int color) {
	draw_line(&mlx_s, x, y, x + s, y, color);
	draw_line(&mlx_s, x + s, y, x + s, y + s, color);
	draw_line(&mlx_s, x + s, y + s, x, y + s, color);
	draw_line(&mlx_s, x, y + s, x, y, color);
}

void draw_triangle(minilibx_struct mlx_s) {
	int ax = 200, ay = 100;
	int bx = 700, by = 150;
	int cx = 450, cy = 550;
	int dx = 600, dy = 800;
	draw_line(&mlx_s, ax, ay, bx, by, 0x00FF0000);
	draw_line(&mlx_s, bx, by, cx, cy, 0x00FF0000);
	draw_line(&mlx_s, cx, cy, ax, ay, 0x00FF0000);
}

void ft_minilibx_init() {
	minilibx_struct mlx_s;
	mlx_s.mlx_init = mlx_init();
	mlx_s.mlx_windows = mlx_new_window(mlx_s.mlx_init, 900, 700, "Cube3D");
	mlx_s.mlx_img = mlx_new_image(mlx_s.mlx_init, 900, 700);
	mlx_s.address = mlx_get_data_addr(mlx_s.mlx_img, &mlx_s.bits_per_pixel,
										 &mlx_s.line_length, &mlx_s.endian);
	// draw_triangle(mlx_s);
	draw_cube(mlx_s, 200, 150, 300, 0x00FF0000);
	mlx_put_image_to_window(mlx_s.mlx_init, mlx_s.mlx_windows, mlx_s.mlx_img, 0, 0);
	mlx_loop(mlx_s.mlx_init);
}

int main() {
	ft_minilibx_init();
}