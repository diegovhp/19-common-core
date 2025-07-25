/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:59 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 06:32:00 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_interrupt_prompt_reset(int signo)
{
	char	newline;

	(void)signo;
	newline = '\n';
	write(STDOUT_FILENO, &newline, 1);
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
	struct sigaction	quit_action;
	void				*result;

	result = ft_memset(&quit_action, 0, sizeof(quit_action));
	(void)result;
	quit_action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &quit_action, NULL);
}

void	configure_interactive_signals(void)
{
	struct sigaction	interrupt_action;
	void				*memset_result;

	disable_quit_signal();
	memset_result = ft_memset(&interrupt_action, 0, sizeof(interrupt_action));
	(void)memset_result;
	interrupt_action.sa_handler = &handle_interrupt_prompt_reset;
	sigaction(SIGINT, &interrupt_action, NULL);
}

void	configure_noninteractive_signals(void)
{
	struct sigaction	signal_action;
	void				*init_result;

	init_result = ft_memset(&signal_action, 0, sizeof(signal_action));
	(void)init_result;
	signal_action.sa_handler = &handle_interrupt_newline;
	sigaction(SIGINT, &signal_action, NULL);
	sigaction(SIGQUIT, &signal_action, NULL);
}
