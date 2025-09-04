/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:52:48 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/03 16:08:32 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	place_sprite(t_gamestate *game, void *sprite, int col, int row)
{
	mlx_put_image_to_window(game->mlx_ptr, game->window_ptr, sprite, col
		* SPRITE_SIZE, row * SPRITE_SIZE);
}

// display layer by layer, sol ou mur, collectible dessus, joueur et sortie
void	draw_game(t_gamestate *game)
{
	int	col;
	int	row;

	row = -1;
	while (++row < game->map_height)
	{
		col = -1;
		while (++col < game->map_width)
		{
			if (game->grid[row][col] == '1')
				place_sprite(game, game->sprite_wall, col, row);
			else
				place_sprite(game, game->sprite_floor, col, row);
			if (game->grid[row][col] == 'C')
				place_sprite(game, game->sprite_item, col, row);
			else if (game->grid[row][col] == 'E'
				&& game->items_collected == game->total_items)
				place_sprite(game, game->sprite_exit, col, row);
			else if (game->player_pos.col == col && game->player_pos.row == row)
				place_sprite(game, game->sprite_player, col, row);
		}
	}
}

void	display_moves(int moves)
{
	ft_printf("Moves: %d\n", moves);
}

void	launch_game(t_gamestate *game)
{
	draw_game(game);
	mlx_hook(game->window_ptr, 2, 1L << 0, process_input, game);
	mlx_hook(game->window_ptr, 17, 0, handle_exit, game);
	mlx_loop(game->mlx_ptr);
}
