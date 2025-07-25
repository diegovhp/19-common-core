/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:50 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:18:15 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_key_value_array(char *argument)
{
	char	**pair;
	char	*delimiter;
	int		key_length;

	delimiter = ft_strchr(argument, '=');
	pair = malloc(sizeof(char *) * 3);
	key_length = delimiter - argument;
	pair[0] = ft_substr(argument, 0, key_length);
	pair[1] = ft_substr(delimiter, 1, ft_strlen(delimiter));
	pair[2] = NULL;
	return (pair);
}

static int	handle_invalid_identifier(char *arg)
{
	print_command_error("export", arg, "not a valid identifier", false);
	return (EXIT_FAILURE);
}

static int	process_assignment(t_data *data, char *arg)
{
	char	**key_val_pair;

	key_val_pair = create_key_value_array(arg);
	ft_set_environment_variable(data, key_val_pair[0], key_val_pair[1]);
	cleanup_string_array(key_val_pair);
	return (EXIT_SUCCESS);
}

static int	validate_and_process_argument(t_data *data, char *arg)
{
	if (!ft_validate_environment_variable_key(arg))
		return (handle_invalid_identifier(arg));
	if (ft_strchr(arg, '=') != NULL)
		return (process_assignment(data, arg));
	return (EXIT_SUCCESS);
}

int	builtin_export_variable(t_data *data, char **args)
{
	int	current_index;
	int	exit_status;
	int	process_result;

	if (!args[1])
		return (builtin_environment_display(data, NULL));
	exit_status = EXIT_SUCCESS;
	current_index = 1;
	while (args[current_index])
	{
		process_result = validate_and_process_argument(data,
				args[current_index]);
		if (process_result == EXIT_FAILURE)
			exit_status = EXIT_FAILURE;
		current_index++;
	}
	return (exit_status);
}
