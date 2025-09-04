/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:41 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 05:46:34 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_command_fields_to_null(t_command **cmd)
{
	(*cmd)->command = NULL;
	(*cmd)->path = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe_output = false;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

//find last
static t_command	*find_tail_command(t_command *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

//new command at end of list
void	append_command_to_list(t_command **command_head, t_command *new_command)
{
	t_command	*traverser;

	traverser = *command_head;
	if (traverser == NULL)
	{
		*command_head = new_command;
		return ;
	}
	if (command_head && *command_head && new_command)
	{
		traverser = find_tail_command(traverser);
		traverser->next = new_command;
		new_command->prev = traverser;
	}
}

t_command	*get_last_command_node(t_command *cmd)
{
	return (find_tail_command(cmd));
}

//allocate new t_command
t_command	*create_new_command_node(bool pipe_flag)
{
	t_command	*command_node;

	command_node = (t_command *)malloc(sizeof(t_command));
	if (!command_node)
		return (NULL);
	ft_memset(command_node, 0, sizeof(t_command));
	command_node->pipe_output = pipe_flag;
	reset_command_fields_to_null(&command_node);
	return (command_node);
}
