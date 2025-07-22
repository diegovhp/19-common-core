/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:42 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/22 19:49:51 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_file_path(char *file_to_open)
{
	char	*current_dir;
	char	*result;

	if (file_to_open[0] == '/')
		return (ft_strdup(file_to_open));
	current_dir = ft_strdup("./");
	result = ft_strjoin(current_dir, file_to_open);
	printf("PARSING - Get_rel_path function return : %s\n", result);
	return (result);
}

static void	initialize_output_truncate_mode(t_io_fds *io,
							char *file, char *var_filename)
{
	if (!clear_existing_file_reference(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		print_command_error(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		print_command_error(io->outfile, NULL, strerror(errno), false);
}

void	process_output_redirection(t_command **last_cmd, t_token **token_lst)
{
	t_token		*current_token;
	t_command	*command_node;

	current_token = *token_lst;
	command_node = get_last_command_node(*last_cmd);
	setup_io_structure(command_node);
	initialize_output_truncate_mode(command_node->io_fds,
		current_token->next->str, current_token->next->str_save);
	if (current_token->next->next)
		current_token = current_token->next->next;
	else
		current_token = current_token->next;
	*token_lst = current_token;
}

static void	configure_append_output(t_io_fds *io,
						char *file, char *var_filename)
{
	if (!clear_existing_file_reference(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0' && var_filename)
	{
		print_command_error(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (io->fd_out == -1)
		print_command_error(io->outfile, NULL, strerror(errno), false);
}

void	handle_append_redirection(t_command **last_cmd, t_token **token_lst)
{
	t_token		*current_token;
	t_command	*target_cmd;

	current_token = *token_lst;
	target_cmd = get_last_command_node(*last_cmd);
	setup_io_structure(target_cmd);
	configure_append_output(target_cmd->io_fds,
		current_token->next->str, current_token->next->str_save);
	if (current_token->next->next)
		current_token = current_token->next->next;
	else
		current_token = current_token->next;
	*token_lst = current_token;
}
