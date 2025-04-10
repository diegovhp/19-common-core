/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:17:02 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/10 13:43:14 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static void	count_elements(t_game *g, char c, int x, int y)
{
	if (c == 'P')
	{
		g->player.x = x;
		g->player.y = y;
	}
	else if (c == 'C')
		g->total_collectibles++;
}

void	check_map_validity(t_game *g)
{
	int	x;
	int	y;

	y = -1;
	while (++y < g->height)
	{
		if ((int)ft_strlen(g->map[y]) != g->width)
			clean_exit(g, "Error:\nMap is not rectangular.", 1);
		x = -1;
		while (++x < g->width)
		{
			if (!ft_strchr("01CEP", g->map[y][x]))
				clean_exit(g, "Error:\nInvalid character in map.", 1);
			if ((y == 0 || y == g->height - 1 || x == 0 || x == g->width - 1)
				&& g->map[y][x] != '1')
				clean_exit(g, "Error: Map is not closed.", 1);
			count_elements(g, g->map[y][x], x, y);
		}
	}
	if (g->total_collectibles < 1)
		clean_exit(g, "Error:\nNo collectibles in map.", 1);
	if (g->player_count != 1)
		clean_exit(g, "Error:\nThere must be exactly one player (P)", 1);
	if (g->exit_count != 1)
		clean_exit(g, "Error:\nThere must be exactly one exit (E).", 1);
}
