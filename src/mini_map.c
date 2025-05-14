/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:56:28 by qbarron           #+#    #+#             */
/*   Updated: 2025/05/14 12:33:21 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mainInclude.h"

static void draw_tile(minilibx_struct *img, int grid_x, int grid_y, int col)
{
    int px;
    int py;

    py = 0;
    while (py < TILE)
    {
        px = 0;
        while (px < TILE)
        {
            put_pixel(img, grid_x * TILE + px, grid_y * TILE + py, col);
            px++;
        }
        py++;
    }
}

void render_minimap(char **map, int w, int h, minilibx_struct *mm, int px, int py)
{
    int y;
    int x;
    char c;

    y = 0;
    while (y < h)
    {
        x = 0;
        while (x < w)
        {
            c = map[y][x];
            if (c == '1')
                draw_tile(mm, x, y, COL_WALL);
            else if (c == '0')
                draw_tile(mm, x, y, COL_FLOOR);
            else
                draw_tile(mm, x, y, COL_EMPTY);
            x++;
        }
        y++;
    }
    draw_tile(mm, px, py, COL_PLAYER);
}