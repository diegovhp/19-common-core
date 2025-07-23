/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:20:45 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 11:39:42 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concatenate_strings(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	cleanup_pointer(tmp);
	return (str);
}

static bool	requires_quote_formatting(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

int	print_command_error(char *command, char *detail,
				char *error_message, int error_nb)
{
	char	*msg;
	bool	quote;

	quote = requires_quote_formatting(command);
	msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		msg = concatenate_strings(msg, command);
		msg = concatenate_strings(msg, ": ");
	}
	if (detail != NULL)
	{
		if (quote)
			msg = concatenate_strings(msg, "`");
		msg = concatenate_strings(msg, detail);
		if (quote)
			msg = concatenate_strings(msg, "'");
		msg = concatenate_strings(msg, ": ");
	}
	msg = concatenate_strings(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	cleanup_pointer(msg);
	return (error_nb);
}

void	print_syntax_error(char *errmsg, char *detail, int quotes)
{
	char	*msg;

	msg = ft_strdup("minishell: ");
	msg = concatenate_strings(msg, errmsg);
	if (quotes)
		msg = concatenate_strings(msg, " `");
	else
		msg = concatenate_strings(msg, ": ");
	msg = concatenate_strings(msg, detail);
	if (quotes)
		msg = concatenate_strings(msg, "'");
	ft_putendl_fd(msg, STDERR_FILENO);
	cleanup_pointer(msg);
}

bool	display_usage(bool return_value)
{
	ft_putendl_fd("Usage: ./minishell", 2);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", 2);
	return (return_value);
}
