/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:37:03 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/15 15:11:06 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int loop_hook(void *param)
{
	t_game *game_st;
	
	game_st = (t_game *)param;
	update_player_position(game_st);
	render_minimap(game_st->map, game_st->map_w, 
					game_st->map_h, &game_st->mini_map, 
					game_st->px, game_st->py);
	mlx_put_image_to_window(game_st->mlx_init, game_st->mlx_windows, game_st->mini_map.ptr, 8, 8);
	return(0);
}

t_game init_struct(t_game *game_st)
{
	ft_bzero(game_st, sizeof(t_game));
	game_st->player.move_speed = 0.1;
	game_st->player.dir_x = 1;
	game_st->player.dir_y = 0;
	game_st->player.move_forward = 0;
	game_st->player.move_backward = 0;
	game_st->player.move_left = 0;
	game_st->player.move_right = 0;
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
	game_st.player.x = (float)game_st.px;
	game_st.player.y = (float)game_st.py;
	// hook des touches ici, jai pas capte le 1L << 0 et 1L << 1 mais j'ai vu ca sur : https://harm-smits.github.io/42docs/libs/minilibx/events.html#:~:text=(1L%3C%3C0)-,KeyPressMask,-(1L%3C%3C13)
	mlx_hook(game_st.mlx_windows, 2, 1L << 0, key_press, &game_st);
	mlx_hook(game_st.mlx_windows, 3, 1L << 1, key_release, &game_st);
	loop_hook(&game_st);
	mlx_loop_hook(game_st.mlx_init, (int (*)(void))loop_hook, &game_st);
	mlx_loop(game_st.mlx_init);
	return(0);
}