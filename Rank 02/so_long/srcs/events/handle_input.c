/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:22:14 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/09 16:19:45 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static void	check_win(t_game *g)
{
	if (g->collected == g->total_collectibles)
	{
		ft_printf("You win in %d moves!\n", g->moves + 1);
		clean_exit(g, NULL, 0);
	}
}

static void	move_to(t_game *g, int nx, int ny)
{
	char	next;

	if (nx < 0 || ny < 0 || nx >= g->width || ny >= g->height)
		return ;
	next = g->map[ny][nx];
	if (next == '1')
		return ;
	if (next == 'E' && g->collected == g->total_collectibles)
	{
		check_win(g);
		return ;
	}
	if (next == 'C')
	{
		g->collected++;
		g->map[ny][nx] = '0';
	}
	g->player.x = nx;
	g->player.y = ny;
	g->moves++;
	print_moves(g->moves);
	render_map(g);
}

int	move_player(int keycode, t_game *g)
{
	int	nx;
	int	ny;

	nx = g->player.x;
	ny = g->player.y;
	if (keycode == KEY_W)
		ny--;
	else if (keycode == KEY_S)
		ny++;
	else if (keycode == KEY_A)
		nx--;
	else if (keycode == KEY_D)
		nx++;
	else
		return (0);
	move_to(g, nx, ny);
	return (1);
}
