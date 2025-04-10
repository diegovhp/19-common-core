/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:22:01 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/05 20:32:28 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_tile(t_game *g, void *img, int x, int y)
{
	mlx_put_image_to_window(g->mlx, g->win, img, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < g->height)
	{
		x = -1;
		while (++x < g->width)
		{
			if (g->map[y][x] == '1')
				render_tile(g, g->wall_img, x, y);
			else
				render_tile(g, g->floor_img, x, y);
			if (g->map[y][x] == 'C')
				render_tile(g, g->collectible_img, x, y);
			else if (g->map[y][x] == 'E'
				&& g->collected == g->total_collectibles)
				render_tile(g, g->exit_img, x, y);
			else if (g->player.x == x && g->player.y == y)
				render_tile(g, g->player_img, x, y);
		}
	}
}
