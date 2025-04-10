/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:22:41 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/10 14:13:55 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

static void	free_images(t_game *g)
{
	if (g->player_img)
		mlx_destroy_image(g->mlx, g->player_img);
	if (g->wall_img)
		mlx_destroy_image(g->mlx, g->wall_img);
	if (g->floor_img)
		mlx_destroy_image(g->mlx, g->floor_img);
	if (g->collectible_img)
		mlx_destroy_image(g->mlx, g->collectible_img);
	if (g->exit_img)
		mlx_destroy_image(g->mlx, g->exit_img);
}

void	free_flood(t_game *g)
{
	int	i;

	if (!g->flood.visited)
		return ;
	i = 0;
	while (i < g->height)
		free(g->flood.visited[i++]);
	free(g->flood.visited);
	g->flood.visited = NULL;
}

void	free_all(t_game *g)
{
	free_flood(g);
	if (g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	free_images(g);
	free_map(g->map);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}
