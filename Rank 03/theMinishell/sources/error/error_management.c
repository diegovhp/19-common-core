/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:20:45 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 07:01:44 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concatenate_strings(char *str, char *add)
{
	char	*original_str;
	char	*new_string;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	original_str = str;
	new_string = ft_strjoin(original_str, add);
	cleanup_pointer(original_str);
	return (new_string);
}

static bool	requires_quote_formatting(char *command)
{
	bool	is_export;
	bool	is_unset;
	bool	needs_quotes;

	is_export = (ft_strncmp(command, "export", 7) == 0);
	is_unset = (ft_strncmp(command, "unset", 6) == 0);
	needs_quotes = (is_export || is_unset);
	return (needs_quotes);
}

int	print_command_error(char *command, char *detail,
				char *error_message, int error_nb)
{
	char	*message_buffer;
	bool	use_quotes;
	int		return_code;

	use_quotes = requires_quote_formatting(command);
	message_buffer = ft_strdup("minishell: ");
	return_code = error_nb;
	if (command != NULL)
	{
		message_buffer = concatenate_strings(message_buffer, command);
		message_buffer = concatenate_strings(message_buffer, ": ");
	}
	if (detail != NULL)
	{
		if (use_quotes)
			message_buffer = concatenate_strings(message_buffer, "`");
		message_buffer = concatenate_strings(message_buffer, detail);
		if (use_quotes)
			message_buffer = concatenate_strings(message_buffer, "'");
		message_buffer = concatenate_strings(message_buffer, ": ");
	}
	message_buffer = concatenate_strings(message_buffer, error_message);
	ft_putendl_fd(message_buffer, STDERR_FILENO);
	cleanup_pointer(message_buffer);
	return (return_code);
}

void	print_syntax_error(char *errmsg, char *detail, int quotes)
{
	char	*error_buffer;
	bool	should_quote;

	error_buffer = ft_strdup("minishell: ");
	should_quote = (quotes != 0);
	error_buffer = concatenate_strings(error_buffer, errmsg);
	if (should_quote)
		error_buffer = concatenate_strings(error_buffer, " `");
	else
		error_buffer = concatenate_strings(error_buffer, ": ");
	error_buffer = concatenate_strings(error_buffer, detail);
	if (should_quote)
		error_buffer = concatenate_strings(error_buffer, "'");
	ft_putendl_fd(error_buffer, STDERR_FILENO);
	cleanup_pointer(error_buffer);
}

bool	display_usage(bool return_value)
{
	bool	result;
	int		stderr_fd;

	result = return_value;
	stderr_fd = 2;
	ft_putendl_fd("Usage: ./minishell", stderr_fd);
	ft_putendl_fd("Usage: ./minishell -c \"input line\"", stderr_fd);
	return (result);
}
