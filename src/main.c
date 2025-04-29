/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:37:03 by qbarron           #+#    #+#             */
/*   Updated: 2025/04/29 18:11:29 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

void ft_minilibx_init() {
	Minilibx_struct mlx_s;
	mlx_s.mlx_init = mlx_init();
	mlx_s.mlx_windows = mlx_new_window(mlx_s.mlx_init, 900, 700, "Cube3D");
	mlx_loop(mlx_s.mlx_init);
}

int main() {
	ft_minilibx_init();
}