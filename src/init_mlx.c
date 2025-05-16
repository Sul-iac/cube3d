/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:27:39 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/16 17:30:42 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int ft_minilibx_init(t_game *game_st)
{
	game_st->mlx_init = mlx_init();
	if(!game_st->mlx_init)
		return(-1);
	game_st->mini_map.win_h = 900;
	game_st->mini_map.win_w = 700;
	game_st->mlx_windows = mlx_new_window(game_st->mlx_init, game_st->mini_map.win_h, 
											game_st->mini_map.win_w, "Cube3D");
	if(!game_st->mlx_windows)
		return(-1);
	game_st->mini_map.ptr = mlx_new_image(game_st->mlx_init, 120, 120);
	game_st->mini_map.address = mlx_get_data_addr(game_st->mini_map.ptr, &game_st->mini_map.bits_per_pixel,
										 &game_st->mini_map.line_length, &game_st->mini_map.endian);
	return(0);
}