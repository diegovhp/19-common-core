/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:41 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:18:33 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_command_defaults(t_command **cmd)
{
	(*cmd)->command = NULL;
	(*cmd)->path = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe_output = false;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

t_command	*get_last_command_node(t_command *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	append_command_to_list(t_command **command_head, t_command *new_command)
{
	t_command	*current;

	current = *command_head;
	if (current == NULL)
	{
		*command_head = new_command;
		return ;
	}
	if (command_head && *command_head && new_command)
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_command;
		new_command->prev = current;
	}
}

t_command	*create_new_command_node(bool pipe_flag)
{
	t_command	*command_node;

	command_node = (t_command *)malloc(sizeof(t_command));
	if (!(command_node))
		return (NULL);
	ft_memset(command_node, 0, sizeof(t_command));
	command_node->pipe_output = pipe_flag;
	setup_command_defaults(&command_node);
	return (command_node);
}
