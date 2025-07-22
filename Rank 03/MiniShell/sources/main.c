/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:21:02 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/22 18:24:39 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	validate_startup_args(t_data *data, int ac, char **av)
{
	if (ac != 1 && ac != 3)
		return (display_usage(false));
	if (ac == 3)
	{
		data->interactive = false;
		if (!av[1] || (av[1] && ft_strcmp(av[1], "-c") != 0))
			return (display_usage(false));
		else if (!av[2] || (av[2] && av[2][0] == '\0'))
			return (display_usage(false));
	}
	else
		data->interactive = true;
	return (true);
}

void	run_command_mode(t_data *data, char *arg)
{
	char	**command_list;
	int		i;

	command_list = ft_split(arg, ';');
	if (!command_list)
		terminate_shell(data, EXIT_FAILURE);
	i = 0;
	while (command_list[i])
	{
		data->user_input = ft_strdup(command_list[i]);
		if (process_command_line(data) == true)
			g_last_exit_code = ft_execute_command_pipeline(data);
		else if (g_last_exit_code != SYNTAX)
			g_last_exit_code = 1;
		i++;
		cleanup_shell_data(data, false);
	}
	cleanup_string_array(command_list);
}

void	run_interactive_mode(t_data *data)
{
	while (1)
	{
		configure_interactive_signals();
		data->user_input = readline(PROMPT);
		configure_noninteractive_signals();
		if (process_command_line(data) == true)
			g_last_exit_code = ft_execute_command_pipeline(data);
		else if (g_last_exit_code != SYNTAX)
			g_last_exit_code = 1;
		cleanup_shell_data(data, false);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	if (!validate_startup_args(&data, ac, av)
		|| !initialize_shell_data(&data, env))
		terminate_shell(NULL, EXIT_FAILURE);
	if (data.interactive)
		run_interactive_mode(&data);
	else
		run_command_mode(&data, av[2]);
	terminate_shell(&data, g_last_exit_code);
	return (0);
}
