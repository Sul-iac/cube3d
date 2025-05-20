/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:37:03 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/20 13:35:12 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

int loop_hook(void *param)
{
	t_game		*game_st;
	
	game_st = (t_game *)param;
	update_player_position(game_st);
	ft_memset(game_st->mlx_struct.address, 0, 
  			game_st->mlx_struct.line_length * game_st->mlx_struct.win_h);
	render_raycast(game_st);
	render_minimap(game_st->map, game_st->map_w, 
		game_st->map_h, &game_st->mlx_struct, 
		game_st->px, game_st->py);
	mlx_put_image_to_window(game_st->mlx_struct.mlx_init, game_st->mlx_struct.mlx_windows, game_st->mlx_struct.mlx_img, 0, 0);
	return(0);
}

void init_texture_struct(t_game *game_st)
{
	game_st->no.img = mlx_xpm_file_to_image(game_st->mlx_struct.mlx_init, game_st->no_path, 
			&game_st->no.width, &game_st->no.height);
	game_st->no.addr = mlx_get_data_addr(game_st->no.img, &game_st->no.bpp, 
			&game_st->no.line_len, &game_st->no.endian);
	game_st->ea.img = mlx_xpm_file_to_image(game_st->mlx_struct.mlx_init, game_st->ea_path, 
			&game_st->ea.width, &game_st->ea.height);
	game_st->ea.addr = mlx_get_data_addr(game_st->ea.img, &game_st->ea.bpp, 
			&game_st->ea.line_len, &game_st->ea.endian);
	game_st->so.img = mlx_xpm_file_to_image(game_st->mlx_struct.mlx_init, game_st->so_path, 
			&game_st->so.width, &game_st->so.height);
	game_st->so.addr = mlx_get_data_addr(game_st->so.img, &game_st->so.bpp, 
			&game_st->so.line_len, &game_st->so.endian);
	game_st->we.img = mlx_xpm_file_to_image(game_st->mlx_struct.mlx_init, game_st->we_path, 
			&game_st->we.width, &game_st->we.height);
	game_st->we.addr = mlx_get_data_addr(game_st->we.img, &game_st->we.bpp, 
			&game_st->we.line_len, &game_st->we.endian);
}

void init_struct(t_game *game_st)
{
	ft_bzero(game_st, sizeof(t_game));
	ft_bzero(&game_st->ea, sizeof(t_texture));
	ft_bzero(&game_st->no, sizeof(t_texture));
	ft_bzero(&game_st->we, sizeof(t_texture));
	ft_bzero(&game_st->so, sizeof(t_texture));
	game_st->player.move_speed = 0.1;
	game_st->player.move_forward = 0;
	game_st->player.move_backward = 0;
	game_st->player.move_left = 0;
	game_st->player.move_right = 0;
	game_st->player.rotate_left = 0;
	game_st->player.rotate_right = 0;
}

void	init_player_direction(t_game *game_st)
{
	if (game_st->pdir == 'N')
	{
		game_st->player.dir_x = 0;
		game_st->player.dir_y = -1;
		game_st->player.plane_x = 0.66;
		game_st->player.plane_y = 0;
	}
	else if (game_st->pdir == 'S')
	{
		game_st->player.dir_x = 0;
		game_st->player.dir_y = 1;
		game_st->player.plane_x = -0.66;
		game_st->player.plane_y = 0;
	}
	else if (game_st->pdir == 'E')
	{
		game_st->player.dir_x = 1;
		game_st->player.dir_y = 0;
		game_st->player.plane_x = 0;
		game_st->player.plane_y = 0.66;
	}
	else if (game_st->pdir == 'W')
	{
		game_st->player.dir_x = -1;
		game_st->player.dir_y = 0;
		game_st->player.plane_x = 0;
		game_st->player.plane_y = -0.66;
	}
}

int main(int argc, char **argv)
{
	t_game			game_st;
	minilibx_struct mlx_s;
	
	if(argc != 2) 
	{
		printf("Error: bad arguments\n");
		return(-1);
	}
	init_struct(&game_st);
	if(parse_map(argv[1], &game_st) == -1)
		return(printf("error: main: cannot parse map\n"), -1);
	if(ft_minilibx_init(&game_st) == -1)
		return(printf("error: main: mlx_init error\n"), -1);
	init_texture_struct(&game_st);
	game_st.player.x = (float)game_st.px;
	game_st.player.y = (float)game_st.py;
	init_player_direction(&game_st);
	mlx_hook(game_st.mlx_struct.mlx_windows, 2, 1L << 0, key_press, &game_st);
	mlx_hook(game_st.mlx_struct.mlx_windows, 3, 1L << 1, key_release, &game_st);
	mlx_loop_hook(game_st.mlx_struct.mlx_init, (int (*)(void))loop_hook, &game_st);
	mlx_loop(game_st.mlx_struct.mlx_init);
	return(0);
}
