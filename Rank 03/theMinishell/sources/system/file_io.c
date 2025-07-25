/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:51 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/25 06:12:33 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	backup_standard_streams(t_io_fds *io)
{
	bool	success;

	success = true;
	io->stdin_save = dup(STDIN_FILENO);
	if (io->stdin_save == -1)
		success = print_command_error("dup",
				"stdin backup", strerror(errno), false);
	io->stdout_save = dup(STDOUT_FILENO);
	if (io->stdout_save == -1)
		success = print_command_error("dup",
				"stdout backup", strerror(errno), false);
	return (success);
}

static bool	apply_stream_redirections(t_io_fds *io)
{
	bool	success;

	success = true;
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			success = print_command_error("dup2",
					io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			success = print_command_error("dup2",
					io->outfile, strerror(errno), false);
	return (success);
}

bool	validate_file_descriptors(t_io_fds *io)
{
	if (!io || (!io->infile && !io->outfile))
		return (true);
	if ((io->infile && io->fd_in == -1)
		|| (io->outfile && io->fd_out == -1))
		return (false);
	return (true);
}

bool	setup_io_redirection(t_io_fds *io)
{
	bool	backup_result;
	bool	redirect_result;

	if (!io)
		return (true);
	backup_result = backup_standard_streams(io);
	redirect_result = apply_stream_redirections(io);
	return (backup_result && redirect_result);
}

bool	reset_io_redirection(t_io_fds *io)
{
	bool	result;

	result = true;
	if (!io)
		return (result);
	if (io->stdin_save != -1)
	{
		if (dup2(io->stdin_save, STDIN_FILENO) == -1)
			result = false;
		close(io->stdin_save);
		io->stdin_save = -1;
	}
	if (io->stdout_save != -1)
	{
		if (dup2(io->stdout_save, STDOUT_FILENO) == -1)
			result = false;
		close(io->stdout_save);
		io->stdout_save = -1;
	}
	return (result);
}
