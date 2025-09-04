/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:53:23 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/03 16:08:22 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_sprites(t_gamestate *game)
{
	if (game->sprite_player)
		mlx_destroy_image(game->mlx_ptr, game->sprite_player);
	if (game->sprite_wall)
		mlx_destroy_image(game->mlx_ptr, game->sprite_wall);
	if (game->sprite_floor)
		mlx_destroy_image(game->mlx_ptr, game->sprite_floor);
	if (game->sprite_item)
		mlx_destroy_image(game->mlx_ptr, game->sprite_item);
	if (game->sprite_exit)
		mlx_destroy_image(game->mlx_ptr, game->sprite_exit);
}

void	cleanup_pathfind(t_gamestate *game)
{
	int	i;

	if (!game->pathfinder.explored)
		return ;
	i = 0;
	while (i < game->map_height)
		free(game->pathfinder.explored[i++]);
	free(game->pathfinder.explored);
	game->pathfinder.explored = NULL;
}

void	cleanup_all(t_gamestate *game)
{
	cleanup_pathfind(game);
	if (game->mlx_ptr && game->window_ptr)
		mlx_destroy_window(game->mlx_ptr, game->window_ptr);
	destroy_sprites(game);
	deallocate_map(game->grid);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}
