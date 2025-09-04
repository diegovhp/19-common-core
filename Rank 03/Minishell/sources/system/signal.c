/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:59 by tstevens          #+#    #+#             */
/*   Updated: 2025/08/25 13:18:09 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Gère le signal SIGINT (Ctrl+C) en mode interactif :
 affiche une nouvelle ligne,
 réinitialise la ligne en cours et redisplay le prompt. */
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

/* Gère le signal SIGINT en mode non interactif :
 se contente de repositionner le curseur sur une nouvelle ligne.*/
void	handle_interrupt_newline(int signal)
{
	char	newline;

	(void)signal;
	newline = '\n';
	write(STDOUT_FILENO, &newline, 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

// Ignore le signal SIGQUIT (Ctrl+\) en désactivant son comportement par défaut.
void	disable_quit_signal(void)
{
	struct sigaction	quit_action;
	void				*result;

	result = ft_memset(&quit_action, 0, sizeof(quit_action));
	(void)result;
	quit_action.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &quit_action, NULL);
}

/* Configure les signaux en mode interactif :
 ignore SIGQUIT et redéfinit SIGINT pour réinitialiser proprement le prompt.*/
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

/* Configure les signaux en mode non interactif :
 SIGINT et SIGQUIT n'affichent qu'un retour
 à la ligne sans interruption du processus.*/
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
