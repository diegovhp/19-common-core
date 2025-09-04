/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:52:13 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/03 16:08:36 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static void	process_map_element(t_gamestate *game, char c, int col, int row)
{
	if (c == 'P')
	{
		game->player_pos.col = col;
		game->player_pos.row = row;
	}
	else if (c == 'C')
		game->total_items++;
}

int	handle_exit(t_gamestate *game)
{
	safe_exit(game, NULL, 0);
	return (0);
}

int	process_input(int keycode, t_gamestate *game)
{
	if (keycode == EXIT_KEY)
		safe_exit(game, NULL, 0);
	if (keycode == MOVE_UP || keycode == MOVE_LEFT || keycode == MOVE_DOWN
		|| keycode == MOVE_RIGHT)
		handle_movement(keycode, game);
	return (0);
}

static void	validate_element_counts(t_gamestate *game)
{
	if (game->total_items < 1)
		safe_exit(game, "Error:\nNo collectibles in map.", 1);
	if (game->player_instances != 1)
		safe_exit(game, "Error:\nThere must be exactly one player (P).", 1);
	if (game->exit_instances != 1)
		safe_exit(game, "Error:\nThere must be exactly one exit (E).", 1);
}

void	validate_map_structure(t_gamestate *game)
{
	int	col;
	int	row;

	row = -1;
	while (++row < game->map_height)
	{
		if ((int)ft_strlen(game->grid[row]) != game->map_width)
			safe_exit(game, "Error:\nMap is not rectangular.", 1);
		col = -1;
		while (++col < game->map_width)
		{
			if (!ft_strchr("01CEP", game->grid[row][col]))
				safe_exit(game, "Error:\nInvalid character in map.", 1);
			if ((row == 0 || row == game->map_height - 1 || col == 0
					|| col == game->map_width - 1)
				&& game->grid[row][col] != '1')
				safe_exit(game, "Error: Map is not closed.", 1);
			process_map_element(game, game->grid[row][col], col, row);
		}
	}
	validate_element_counts(game);
}
