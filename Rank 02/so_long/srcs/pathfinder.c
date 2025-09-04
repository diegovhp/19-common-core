/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:52:33 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/02 17:55:43 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

// alloc tab 2d pour marquer ce qu'on a visit. 0 = non visit, 1 = visited
void	prepare_pathfind(t_gamestate *game)
{
	int	i;

	game->pathfinder.collectibles_reached = 0;
	game->pathfinder.exit_reachable = 0;
	game->pathfinder.explored = malloc(sizeof(int *) * game->map_height);
	if (!game->pathfinder.explored)
		safe_exit(game, "Error\nMalloc failed for pathfinder.explored", 1);
	i = 0;
	while (i < game->map_height)
	{
		game->pathfinder.explored[i] = ft_calloc(game->map_width, sizeof(int));
		if (!game->pathfinder.explored[i])
			safe_exit(game, "Error\nMalloc failed for pathfinder.explored[i]",
				1);
		i++;
	}
}

// si 1, deja visited ou wall. Marquer comme visited, check si c ou e
// recursive 4 directions
void	explore_paths(t_gamestate *game, int col, int row)
{
	if (col < 0 || row < 0 || col >= game->map_width || row >= game->map_height)
		return ;
	if (game->pathfinder.explored[row][col] || game->grid[row][col] == '1')
		return ;
	game->pathfinder.explored[row][col] = 1;
	if (game->grid[row][col] == 'C')
		game->pathfinder.collectibles_reached++;
	if (game->grid[row][col] == 'E')
		game->pathfinder.exit_reachable = 1;
	explore_paths(game, col + 1, row);
	explore_paths(game, col - 1, row);
	explore_paths(game, col, row + 1);
	explore_paths(game, col, row - 1);
}

void	validate_path_access(t_gamestate *game)
{
	if (game->pathfinder.collectibles_reached != game->total_items
		|| game->pathfinder.exit_reachable != 1)
		safe_exit(game, "Error\nNo valid path to all collectibles or exit", 1);
}
