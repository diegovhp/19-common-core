/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:38 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:18:04 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	validate_newline_option(char *argument)
{
	int		position;
	bool	is_valid_flag;

	is_valid_flag = false;
	position = 0;
	if (argument[position] != '-')
		return (is_valid_flag);
	position++;
	while (argument[position] && argument[position] == 'n')
		position++;
	if (argument[position] == '\0')
		is_valid_flag = true;
	return (is_valid_flag);
}

static int	skip_option_arguments(char **arguments)
{
	int	start_index;

	start_index = 1;
	while (arguments[start_index] && validate_newline_option
		(arguments[start_index]))
	{
		start_index++;
	}
	return (start_index);
}

static bool	determine_newline_suppression(char **arguments)
{
	bool	suppress_newline;
	int		check_index;

	suppress_newline = false;
	check_index = 1;
	while (arguments[check_index] && validate_newline_option
		(arguments[check_index]))
	{
		suppress_newline = true;
		check_index++;
	}
	return (suppress_newline);
}

static void	print_arguments_with_spacing(char **arguments,
		bool suppress_newline, int start_pos)
{
	if (!arguments[start_pos])
	{
		if (!suppress_newline)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (arguments[start_pos])
	{
		ft_putstr_fd(arguments[start_pos], STDOUT_FILENO);
		if (arguments[start_pos + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!arguments[start_pos + 1] && !suppress_newline)
			ft_putchar_fd('\n', STDOUT_FILENO);
		start_pos++;
	}
}

int	builtin_echo_command(t_data *data, char **args)
{
	int		argument_start;
	bool	newline_suppressed;

	(void)data;
	newline_suppressed = determine_newline_suppression(args);
	argument_start = skip_option_arguments(args);
	print_arguments_with_spacing(args, newline_suppressed, argument_start);
	return (EXIT_SUCCESS);
}
