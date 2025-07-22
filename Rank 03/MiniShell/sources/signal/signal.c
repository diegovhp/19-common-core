/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:59 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 11:41:11 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_interrupt_prompt_reset(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_interrupt_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	disable_quit_signal(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	configure_interactive_signals(void)
{
	struct sigaction	act;

	disable_quit_signal();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_interrupt_prompt_reset;
	sigaction(SIGINT, &act, NULL);
}

void	configure_noninteractive_signals(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handle_interrupt_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
