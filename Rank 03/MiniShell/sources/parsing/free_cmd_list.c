/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst_utils_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:38 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/21 11:45:37 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_command_list(t_command **command_list,
								void (*deallocator)(void *))
{
	t_command	*next_node;

	next_node = NULL;
	while (*command_list != NULL)
	{
		next_node = (*command_list)->next;
		free_single_command(*command_list, deallocator);
		*command_list = next_node;
	}
}

void	free_single_command(t_command *cmd_node, void (*deallocator)(void *))
{
	if (cmd_node->command)
		(*deallocator)(cmd_node->command);
	if (cmd_node->args)
		cleanup_string_array(cmd_node->args);
	if (cmd_node->pipe_fd)
		(*deallocator)(cmd_node->pipe_fd);
	if (cmd_node->io_fds)
		cleanup_io_structure(cmd_node->io_fds);
	(*deallocator)(cmd_node);
}
