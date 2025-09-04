/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:26 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/22 19:44:25 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extract heredoc delim << and check if inside quotes
static char	*extract_delimiter_from_token(char *delim, bool *quotes)
{
	int	last_index;

	last_index = ft_strlen(delim) - 1;
	if ((delim[0] == '\"' && delim[last_index] == '\"')
		|| (delim[0] == '\'' && delim[last_index] == '\''))
	{
		*quotes = true;
		return (ft_strtrim(delim, "\'\""));
	}
	return (ft_strdup(delim));
}

// create unique heredoc file name
static char	*generate_unique_heredoc_filename(void)
{
	static int	counter;
	char		*filename;
	char		*number_str;

	number_str = ft_itoa(counter);
	if (!number_str)
		return (NULL);
	filename = ft_strjoin(HEREDOC_NAME, number_str);
	free(number_str);
	counter++;
	return (filename);
}

// handle <<
void	handle_heredoc_redirection(t_data *data,
		t_command **last_cmd, t_token **token_lst)
{
	t_token		*current_token;
	t_command	*target_cmd;
	t_io_fds	*io_streams;

	current_token = *token_lst;
	target_cmd = get_last_command_node(*last_cmd);
	setup_io_structure(target_cmd);
	io_streams = target_cmd->io_fds;
	if (!clear_existing_file_reference(io_streams, true))
		return ;
	io_streams->infile = generate_unique_heredoc_filename();
	io_streams->heredoc_limit = extract_delimiter_from_token
		(current_token->next->str, &(io_streams->heredoc_quotes));
	if (create_heredoc_file(data, io_streams))
		io_streams->fd_in = open(io_streams->infile, O_RDONLY);
	else
		io_streams->fd_in = -1;
	if (current_token->next->next)
		current_token = current_token->next->next;
	else
		current_token = current_token->next;
	*token_lst = current_token;
}

// cree et rempli fichier heredoc temp
bool	create_heredoc_file(t_data *data, t_io_fds *io)
{
	int		temp_fd;
	bool	success_status;

	success_status = true;
	temp_fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	success_status = process_heredoc_input(data, io, temp_fd);
	close(temp_fd);
	return (success_status);
}

char	*reconstruct_string_from_array(char **tab)
{
	char	*result_str;
	char	*temp_str;
	int		index;

	index = -1;
	while (tab[++index])
	{
		temp_str = result_str;
		if (index == 0)
			result_str = ft_strdup(tab[0]);
		else
		{
			result_str = ft_strjoin(temp_str, tab[index]);
			cleanup_pointer(temp_str);
		}
		if (tab[index + 1])
		{
			temp_str = result_str;
			result_str = ft_strjoin(temp_str, " ");
			cleanup_pointer(temp_str);
		}
	}
	cleanup_string_array(tab);
	return (result_str);
}
