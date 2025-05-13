/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:37:03 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/13 15:18:46 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"
#include <math.h>

char map_debug[6][9] = {
	"#########",
	"#xxxxxxx#",
	"#xxxxxxx#",
	"#xxxxNxx#",
	"#xxxxxxx#",
	"#########"
};

int main(int argc, char **argv) {
	
	printf("[DEBUG] 1\n");
	
	int width = 600;
	int height = 400;
	
	minilibx_struct mlx_s;
	mlx_s.mlx_init = mlx_init();
	mlx_s.mlx_windows = mlx_new_window(mlx_s.mlx_init, width, height, "Cube3D");
	mlx_s.mlx_img = mlx_new_image(mlx_s.mlx_init, width, height);
	mlx_s.address = mlx_get_data_addr(mlx_s.mlx_img, &mlx_s.bits_per_pixel,
										 &mlx_s.line_length, &mlx_s.endian);
	
	mlx_put_image_to_window(mlx_s.mlx_init, mlx_s.mlx_windows, mlx_s.mlx_img, 0, 0);
	mlx_loop(mlx_s.mlx_init);
	
	return 0;
}