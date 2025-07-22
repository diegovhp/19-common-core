/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:44 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 11:46:29 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_argumentless_commands(t_data *data)
{
	t_command	*current_cmd;

	if (!data || !data->cmd)
		return ;
	current_cmd = data->cmd;
	while (current_cmd && current_cmd->command)
	{
		if (!current_cmd->args)
		{
			current_cmd->args = malloc(sizeof * current_cmd->args * 2);
			current_cmd->args[0] = ft_strdup(current_cmd->command);
			current_cmd->args[1] = NULL;
		}
		current_cmd = current_cmd->next;
	}
	current_cmd = get_last_command_node(data->cmd);
}

void	build_command_structures(t_data *data, t_token *token)
{
	t_token	*current_token;

	current_token = token;
	if (current_token->type == END)
		return ;
	while (current_token->next != NULL)
	{
		if (current_token == token)
			append_command_to_list(&data->cmd, create_new_command_node(false));
		if (current_token->type == WORD || current_token->type == VAR)
			handle_word_tokens(&data->cmd, &current_token);
		else if (current_token->type == INPUT)
			process_input_token(&data->cmd, &current_token);
		else if (current_token->type == TRUNC)
			process_output_redirection(&data->cmd, &current_token);
		else if (current_token->type == HEREDOC)
			handle_heredoc_redirection(data, &data->cmd, &current_token);
		else if (current_token->type == APPEND)
			handle_append_redirection(&data->cmd, &current_token);
		else if (current_token->type == PIPE)
			handle_pipeline_connection(&data->cmd, &current_token);
		else if (current_token->type == END)
			break ;
	}
	setup_argumentless_commands(data);
}
