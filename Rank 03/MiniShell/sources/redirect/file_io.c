/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:51 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/22 19:48:06 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	io->stdin_save = dup(STDIN_FILENO);
	if (io->stdin_save == -1)
		ret = print_command_error("dup",
				"stdin backup", strerror(errno), false);
	io->stdout_save = dup(STDOUT_FILENO);
	if (io->stdout_save == -1)
		ret = print_command_error("dup",
				"stdout backup", strerror(errno), false);
	if (io->fd_in != -1)
		if (dup2(io->fd_in, STDIN_FILENO) == -1)
			ret = print_command_error("dup2",
					io->infile, strerror(errno), false);
	if (io->fd_out != -1)
		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
			ret = print_command_error("dup2",
					io->outfile, strerror(errno), false);
	return (ret);
}

bool	reset_io_redirection(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_save != -1)
	{
		if (dup2(io->stdin_save, STDIN_FILENO) == -1)
			ret = false;
		close(io->stdin_save);
		io->stdin_save = -1;
	}
	if (io->stdout_save != -1)
	{
		if (dup2(io->stdout_save, STDOUT_FILENO) == -1)
			ret = false;
		close(io->stdout_save);
		io->stdout_save = -1;
	}
	return (ret);
}
