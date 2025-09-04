/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:32 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/22 19:49:26 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// clean infile or outfile reference
bool	clear_existing_file_reference(t_io_fds *io, bool input_mode)
{
	if (input_mode == true && io->infile)
	{
		if (io->fd_in == -1 || (io->outfile && io->fd_out == -1))
			return (false);
		if (io->heredoc_limit != NULL)
		{
			cleanup_pointer(io->heredoc_limit);
			io->heredoc_limit = NULL;
			unlink(io->infile);
		}
		cleanup_pointer(io->infile);
		close(io->fd_in);
	}
	else if (input_mode == false && io->outfile)
	{
		if (io->fd_out == -1 || (io->infile && io->fd_in == -1))
			return (false);
		cleanup_pointer(io->outfile);
		close(io->fd_out);
	}
	return (true);
}

// affecte infile a la cmd si <
static void	configure_input_file(t_io_fds *io,
			char *file, char *original_filename)
{
	if (!clear_existing_file_reference(io, true))
		return ;
	io->infile = ft_strdup(file);
	if (io->infile && io->infile[0] == '\0')
	{
		print_command_error(original_filename, NULL,
			"ambiguous redirect", false);
		return ;
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		print_command_error(io->infile, NULL, strerror(errno), false);
}

// process input token <
void	process_input_token(t_command **last_cmd, t_token **token_lst)
{
	t_token		*current_token;
	t_command	*command_node;

	current_token = *token_lst;
	command_node = get_last_command_node(*last_cmd);
	setup_io_structure(command_node);
	configure_input_file(command_node->io_fds,
		current_token->next->str, current_token->next->str_save);
	if (current_token->next->next)
		current_token = current_token->next->next;
	else
		current_token = current_token->next;
	*token_lst = current_token;
}

// handle pipe in tokens
void	handle_pipeline_connection(t_command **cmd, t_token **token_lst)
{
	t_command	*current_command;

	current_command = get_last_command_node(*cmd);
	current_command->pipe_output = true;
	append_command_to_list(&current_command, create_new_command_node(false));
	*token_lst = (*token_lst)->next;
}
