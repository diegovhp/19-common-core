/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:21:26 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/08/28 14:21:59 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Gère le signal SIGINT pendant un heredoc :
 utilise g_last_exit_code pour signaler l'interruption. */
void	handle_heredoc_interrupt(int signo)
{
	char	newline;

	(void)signo;
	g_last_exit_code = 130;
	newline = '\n';
	write(STDOUT_FILENO, &newline, 1);
}

/* Configure les signaux spécifiquement pour le heredoc :
 ignore SIGQUIT et configure SIGINT pour interrompre le heredoc.*/
void	configure_heredoc_signals(void)
{
	struct sigaction	interrupt_action;
	void				*memset_result;

	disable_quit_signal();
	memset_result = ft_memset(&interrupt_action, 0, sizeof(interrupt_action));
	(void)memset_result;
	interrupt_action.sa_handler = &handle_heredoc_interrupt;
	sigaction(SIGINT, &interrupt_action, NULL);
}
