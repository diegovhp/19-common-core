/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:21:38 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/10 13:35:07 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

void	init_flood_structure(t_game *g)
{
	int	i;

	g->flood.collectibles_found = 0;
	g->flood.exit_found = 0;
	g->flood.visited = malloc(sizeof(int *) * g->height);
	if (!g->flood.visited)
		clean_exit(g, "Error\nMalloc failed for flood.visited", 1);
	i = 0;
	while (i < g->height)
	{
		g->flood.visited[i] = ft_calloc(g->width, sizeof(int));
		if (!g->flood.visited[i])
			clean_exit(g, "Error\nMalloc failed for flood.visited[i]", 1);
		i++;
	}
}

void	flood_fill(t_game *g, int x, int y)
{
	if (x < 0 || y < 0 || x >= g->width || y >= g->height)
		return ;
	if (g->flood.visited[y][x] || g->map[y][x] == '1')
		return ;
	g->flood.visited[y][x] = 1;
	if (g->map[y][x] == 'C')
		g->flood.collectibles_found++;
	if (g->map[y][x] == 'E')
		g->flood.exit_found = 1;
	flood_fill(g, x + 1, y);
	flood_fill(g, x - 1, y);
	flood_fill(g, x, y + 1);
	flood_fill(g, x, y - 1);
}

void	check_path_validity(t_game *g)
{
	if (g->flood.collectibles_found != g->total_collectibles
		|| g->flood.exit_found != 1)
		clean_exit(g, "Error\nNo valid path to all collectibles or exit", 1);
}

// static char	**dup_map(char **map)
// {
// 	int		i;
// 	char	**copy;

// 	i = 0;
// 	while (map[i])
// 		i++;
// 	copy = malloc(sizeof(char *) * (i + 1));
// 	if (!copy)
// 		return (NULL);
// 	i = -1;
// 	while (map[++i])
// 		copy[i] = ft_strdup(map[i]);
// 	copy[i] = NULL;
// 	return (copy);
// }

// void	check_path(t_game *g)
// {
// 	char	**copy;

// 	copy = dup_map(g->map);
// 	if (!copy)
// 		ft_error("Error: malloc failed during flood fill.");
// 	dfs(copy, g->player.x, g->player.y, g);
// 	free_map(copy);
// }
