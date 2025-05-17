/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:27:39 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/17 00:37:16 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int ft_minilibx_init(t_game *game_st)
{
	game_st->mlx_init = mlx_init();
	if(!game_st->mlx_init)
		return(-1);
	game_st->mlx_struct.win_h = 700;
	game_st->mlx_struct.win_w = 900;
	game_st->mlx_windows = mlx_new_window(game_st->mlx_init, game_st->mlx_struct.win_w, 
											game_st->mlx_struct.win_h, "Cube3D");
	if(!game_st->mlx_windows)
		return(-1);
	game_st->mlx_struct.ptr = mlx_new_image(game_st->mlx_init, game_st->mlx_struct.win_w, game_st->mlx_struct.win_h);
	if (!game_st->mlx_struct.ptr)
		return (-1);
	game_st->mlx_struct.address = mlx_get_data_addr(game_st->mlx_struct.ptr, &game_st->mlx_struct.bits_per_pixel,
										 &game_st->mlx_struct.line_length, &game_st->mlx_struct.endian);
	if (!game_st->mlx_struct.address)
		return (-1);
	return(0);
}