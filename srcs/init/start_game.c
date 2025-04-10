/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:23:18 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/09 16:21:48 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	handle_key(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		clean_exit(g, NULL, 0);
	if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
		move_player(keycode, g);
	return (0);
}

static int	handle_exit(t_game *g)
{
	clean_exit(g, NULL, 0);
	return (0);
}

void	start_game(t_game *g)
{
	render_map(g);
	mlx_hook(g->win, 2, 1L << 0, handle_key, g);
	mlx_hook(g->win, 17, 0, handle_exit, g);
	mlx_loop(g->mlx);
}
