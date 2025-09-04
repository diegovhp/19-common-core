/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:18:38 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 05:50:16 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free toutes les ressources d'1 t_command
static void	release_command_resources(t_command *command_to_free,
									void (*memory_deallocator)(void *))
{
	if (command_to_free->command)
		(*memory_deallocator)(command_to_free->command);
	if (command_to_free->args)
		cleanup_string_array(command_to_free->args);
	if (command_to_free->pipe_fd)
		(*memory_deallocator)(command_to_free->pipe_fd);
	if (command_to_free->io_fds)
		cleanup_io_structure(command_to_free->io_fds);
	(*memory_deallocator)(command_to_free);
}

void	free_single_command(t_command *cmd_node, void (*deallocator)(void *))
{
	release_command_resources(cmd_node, deallocator);
}

// free toute la liste chainee t_command
void	destroy_command_list(t_command **command_list,
								void (*deallocator)(void *))
{
	t_command	*following_command;

	following_command = NULL;
	while (*command_list)
	{
		following_command = (*command_list)->next;
		release_command_resources(*command_list, deallocator);
		*command_list = following_command;
	}
}
