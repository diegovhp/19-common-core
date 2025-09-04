/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:53:52 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/02 17:56:04 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

void	error_exit(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	safe_exit(t_gamestate *game, char *msg, int code)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	if (game)
		cleanup_all(game);
	exit(code);
}

void	free_both(char *tmp, char *line)
{
	if (tmp)
		free(tmp);
	if (line)
		free(line);
}
