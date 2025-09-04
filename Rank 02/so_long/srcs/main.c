/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:51:11 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/02 17:55:12 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	verify_sprites_loaded(t_gamestate *game)
{
	if (!game->sprite_player || !game->sprite_wall || !game->sprite_floor
		|| !game->sprite_item || !game->sprite_exit)
	{
		safe_exit(game, "Error: Failed to load one or more .xpm textures.", 1);
	}
}

static void	initialize_sprites(t_gamestate *game)
{
	int	dummy;

	game->sprite_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/player.xpm", &dummy, &dummy);
	game->sprite_wall = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/wall.xpm", &dummy, &dummy);
	game->sprite_floor = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/floor.xpm", &dummy, &dummy);
	game->sprite_item = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/collectible.xpm", &dummy, &dummy);
	game->sprite_exit = mlx_xpm_file_to_image(game->mlx_ptr,
			"textures/exit.xpm", &dummy, &dummy);
	verify_sprites_loaded(game);
}

void	setup_game(t_gamestate *game, char *filename)
{
	ft_bzero(game, sizeof(t_gamestate));
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		safe_exit(game, NULL, EXIT_FAILURE);
	game->grid = extract_map(filename, game);
	validate_map_structure(game);
	prepare_pathfind(game);
	explore_paths(game, game->player_pos.col, game->player_pos.row);
	validate_path_access(game);
	cleanup_pathfind(game);
	game->window_ptr = mlx_new_window(game->mlx_ptr, game->map_width
			* SPRITE_SIZE, game->map_height * SPRITE_SIZE, "so_long");
	if (!game->window_ptr)
		safe_exit(game, NULL, EXIT_FAILURE);
	initialize_sprites(game);
	game->move_count = 0;
	game->items_collected = 0;
}

void	validate_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		error_exit("Error:\nInvalid file extension (expected .ber)");
}

int	main(int argc, char **argv)
{
	t_gamestate	game;

	if (argc != 2)
		error_exit("Error:\nTry ./so_long <map.ber>");
	validate_filename(argv[1]);
	setup_game(&game, argv[1]);
	launch_game(&game);
	safe_exit(&game, NULL, 0);
	return (0);
}
