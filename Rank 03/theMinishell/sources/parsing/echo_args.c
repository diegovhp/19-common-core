/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:14 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 06:02:05 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_existing_arguments(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

static char	**allocate_expanded_array(int existing_count, int new_count)
{
	char	**new_array;
	int		total_size;

	total_size = existing_count + new_count + 1;
	new_array = malloc(sizeof(char *) * total_size);
	return (new_array);
}

static void	advance_to_next_token_type(t_token **current)
{
	while ((*current)->type == WORD || (*current)->type == VAR)
		*current = (*current)->next;
}

int	extend_echo_arguments(t_token **token_node, t_command *last_cmd)
{
	int		existing_count;
	int		new_arg_count;
	char	**expanded_array;
	t_token	*current;

	filter_empty_variable_args(token_node);
	current = *token_node;
	new_arg_count = calculate_expanded_args(current);
	existing_count = count_existing_arguments(last_cmd->args);
	expanded_array = allocate_expanded_array(existing_count, new_arg_count);
	if (!expanded_array)
		return (FAILURE);
	expanded_array = duplicate_args_with_expansion(existing_count,
			expanded_array, last_cmd, current);
	free(last_cmd->args);
	last_cmd->args = expanded_array;
	advance_to_next_token_type(&current);
	*token_node = current;
	return (SUCCESS);
}

int	initialize_echo_arguments(t_token **token_node, t_command *last_cmd)
{
	int		arg_count;
	t_token	*current;
	int		position;

	filter_empty_variable_args(token_node);
	current = *token_node;
	arg_count = calculate_expanded_args(current);
	last_cmd->args = malloc(sizeof(char *) * (arg_count + 2));
	if (!last_cmd->args)
		return (FAILURE);
	position = 0;
	last_cmd->args[position] = ft_strdup(last_cmd->command);
	position++;
	while (current->type == WORD || current->type == VAR)
	{
		if (current->join == true)
			last_cmd->args[position] = concatenate_variable_tokens(&current);
		else
			last_cmd->args[position] = ft_strdup(current->str);
		position++;
		current = current->next;
	}
	last_cmd->args[position] = NULL;
	*token_node = current;
	return (SUCCESS);
}
