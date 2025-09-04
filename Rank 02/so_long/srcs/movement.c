/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:53:07 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/02 17:54:55 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static void	check_victory(t_gamestate *game)
{
	if (game->items_collected == game->total_items)
	{
		ft_printf("You win in %d moves!\n", game->move_count + 1);
		safe_exit(game, NULL, 0);
	}
}

// check si dans la carte, pas de mur, sortie si jeu fini
// si collectible, ramasser (C++) et mettre a 0
// pos, compteur, affichage
static void	attempt_move(t_gamestate *game, int new_col, int new_row)
{
	char	target_cell;

	if (new_col < 0 || new_row < 0 || new_col >= game->map_width
		|| new_row >= game->map_height)
		return ;
	target_cell = game->grid[new_row][new_col];
	if (target_cell == '1')
		return ;
	if (target_cell == 'E' && game->items_collected == game->total_items)
	{
		check_victory(game);
		return ;
	}
	if (target_cell == 'C')
	{
		game->items_collected++;
		game->grid[new_row][new_col] = '0';
	}
	game->player_pos.col = new_col;
	game->player_pos.row = new_row;
	game->move_count++;
	display_moves(game->move_count);
	draw_game(game);
}

int	handle_movement(int keycode, t_gamestate *game)
{
	int	new_col;
	int	new_row;

	new_col = game->player_pos.col;
	new_row = game->player_pos.row;
	if (keycode == MOVE_UP)
		new_row--;
	else if (keycode == MOVE_DOWN)
		new_row++;
	else if (keycode == MOVE_LEFT)
		new_col--;
	else if (keycode == MOVE_RIGHT)
		new_col++;
	else
		return (0);
	attempt_move(game, new_col, new_row);
	return (1);
}
