/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:20:41 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/23 11:18:26 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_pointer(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	cleanup_string_array(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				cleanup_pointer(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	cleanup_io_structure(t_io_fds *io)
{
	if (!io)
		return ;
	reset_io_redirection(io);
	if (io->heredoc_limit)
	{
		unlink(io->infile);
		cleanup_pointer(io->heredoc_limit);
	}
	if (io->infile)
		cleanup_pointer(io->infile);
	if (io->outfile)
		cleanup_pointer(io->outfile);
	if (io)
		cleanup_pointer(io);
}

void	cleanup_file_descriptors(t_command *cmds, bool close_backups)
{
	if (cmds->io_fds)
	{
		if (cmds->io_fds->fd_in != -1)
			close(cmds->io_fds->fd_in);
		if (cmds->io_fds->fd_out != -1)
			close(cmds->io_fds->fd_out);
		if (close_backups)
			reset_io_redirection(cmds->io_fds);
	}
	cleanup_unused_pipe_fds(cmds, NULL);
}

void	cleanup_shell_data(t_data *data, bool clear_history)
{
	if (data && data->user_input)
	{
		cleanup_pointer(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		free_entire_token_list(&data->token, &cleanup_pointer);
	if (data && data->cmd)
		destroy_command_list(&data->cmd, &cleanup_pointer);
	if (clear_history == true)
	{
		if (data && data->working_dir)
			cleanup_pointer(data->working_dir);
		if (data && data->old_working_dir)
			cleanup_pointer(data->old_working_dir);
		if (data && data->env)
			cleanup_string_array(data->env);
		rl_clear_history();
	}
}
