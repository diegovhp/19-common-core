/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:48:33 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/10 13:39:30 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:48:33 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/04 17:45:00 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static void	check_xpm_loaded(t_game *g)
{
	if (!g->player_img || !g->wall_img || !g->floor_img
		|| !g->collectible_img || !g->exit_img)
	{
		clean_exit(g, "Error: Failed to load one or more .xpm textures.", 1);
	}
}

static void	load_images(t_game *g)
{
	int	ignore;

	g->player_img = mlx_xpm_file_to_image(g->mlx,
			"textures/player.xpm", &ignore, &ignore);
	g->wall_img = mlx_xpm_file_to_image(g->mlx,
			"textures/wall.xpm", &ignore, &ignore);
	g->floor_img = mlx_xpm_file_to_image(g->mlx,
			"textures/floor.xpm", &ignore, &ignore);
	g->collectible_img = mlx_xpm_file_to_image(g->mlx,
			"textures/collectible.xpm", &ignore, &ignore);
	g->exit_img = mlx_xpm_file_to_image(g->mlx,
			"textures/exit.xpm", &ignore, &ignore);
	check_xpm_loaded(g);
}

void	init_game(t_game *g, char *filename)
{
	ft_bzero(g, sizeof(t_game));
	g->mlx = mlx_init();
	if (!g->mlx)
		clean_exit(g, NULL, EXIT_FAILURE);
	g->map = parse_map(filename, g);
	check_map_validity(g);
	init_flood_structure(g);
	flood_fill(g, g->player.x, g->player.y);
	check_path_validity(g);
	free_flood(g);
	g->win = mlx_new_window(g->mlx, g->width * TILE_SIZE,
			g->height * TILE_SIZE, "so_long");
	if (!g->win)
		clean_exit(g, NULL, EXIT_FAILURE);
	load_images(g);
	g->moves = 0;
	g->collected = 0;
}

void	check_file_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		ft_error("Error:\nInvalid file extension (expected .ber)");
}
