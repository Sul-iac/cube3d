/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:27:39 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/01 18:52:58 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

void ft_minilibx_init() {
	minilibx_struct mlx_s;
	mlx_s.mlx_init = mlx_init();
	mlx_s.mlx_windows = mlx_new_window(mlx_s.mlx_init, 900, 700, "Cube3D");
	mlx_s.mlx_img = mlx_new_image(mlx_s.mlx_init, 900, 700);
	mlx_s.address = mlx_get_data_addr(mlx_s.mlx_img, &mlx_s.bits_per_pixel,
										 &mlx_s.line_length, &mlx_s.endian);
	mlx_put_image_to_window(mlx_s.mlx_init, mlx_s.mlx_windows, mlx_s.mlx_img, 0, 0);
	mlx_loop(mlx_s.mlx_init);
}