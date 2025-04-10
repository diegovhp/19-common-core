/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:47:04 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/09 16:22:32 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_error("Error:\nTry ./so_long <map.ber>");
	check_file_extension(argv[1]);
	init_game(&game, argv[1]);
	start_game(&game);
	clean_exit(&game, NULL, 0);
	return (0);
}
