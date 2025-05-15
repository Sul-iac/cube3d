/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:37:03 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/15 14:27:03 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int loop_hook(void *param)
{
	t_game *game_st;
	
	game_st = (t_game *)param;
	render_minimap(game_st->map, game_st->map_w, 
					game_st->map_h, &game_st->mini_map, 
					game_st->px, game_st->py);
	mlx_put_image_to_window(game_st->mlx_init, game_st->mlx_windows, game_st->mini_map.ptr, 8, 8);
	return(0);
}

t_game init_struct(t_game *game_st)
{
	ft_bzero(game_st, sizeof(t_game));
}

int main(int argc, char **argv)
{
	t_game			game_st;
	minilibx_struct mlx_s;
	
	if(argc != 2) {
		printf("Error: bad arguments\n");
		return(-1);
	}
	init_struct(&game_st);
	if(parse_map(argv[1], &game_st) == -1)
		return(printf("error: main: cannot parse map\n"), -1);
	if(ft_minilibx_init(&game_st) == -1)
		return(printf("error: main: mlx_init error\n"), -1);
	loop_hook(&game_st);
	mlx_loop_hook(game_st.mlx_init, (int (*)(void))loop_hook, &game_st);
	mlx_loop(game_st.mlx_init);
	return(0);
}