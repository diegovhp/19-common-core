/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core2_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:23 by tstevens          #+#    #+#             */
/*   Updated: 2025/08/25 13:18:56 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_last_exit_code;

// apply expansion VAR dans une line si quotes absentes
static char	*expand_variables_in_line(t_data *data, char *line)
{
	char	**word_array;
	int		index;

	word_array = ft_split(line, ' ');
	if (!word_array)
		return (NULL);
	index = 0;
	while (word_array[index])
	{
		if (ft_strchr(word_array[index], '$'))
		{
			word_array[index] = expand_heredoc_variables(
					data, word_array[index]);
			if (!word_array[index])
				return (NULL);
		}
		index++;
	}
	return (reconstruct_string_from_array(word_array));
}

// read a line character by character using read()
static char	*read_heredoc_line(void)
{
	char	buffer[1000];
	char	c;
	int		bytes_read;
	int		i;

	i = 0;
	write(STDOUT_FILENO, ">", 1);
	while (1)
	{
		bytes_read = read(STDIN_FILENO, &c, 1);
		if (bytes_read <= 0 || g_last_exit_code == 130)
			return (NULL);
		if (c == '\n')
			break ;
		if (i < 999)
			buffer[i++] = c;
	}
	buffer[i] = '\0';
	if (i == 0 && bytes_read <= 0)
		return (NULL);
	return (ft_strdup(buffer));
}

// check if line read is NULL, match delimiter, contains VAR to expand
// handle heredoc termination (EOF or interruption)
static bool	handle_heredoc_termination(char **line, t_io_fds *io, bool *ret)
{
	if (*line == NULL || g_last_exit_code == 130)
	{
		if (g_last_exit_code != 130)
			print_command_error("warning",
				"here-document delimited by end-of-file: wanted",
				io->heredoc_limit, true);
		if (g_last_exit_code == 130)
			*ret = false;
		else
			*ret = true;
		return (false);
	}
	return (true);
}

// check if line read is NULL, match delimiter, contains VAR to expand
static bool	validate_heredoc_input(t_data *data, char **line,
	t_io_fds *io, bool *ret)
{
	if (!handle_heredoc_termination(line, io, ret))
		return (false);
	if (ft_strcmp(*line, io->heredoc_limit) == 0)
	{
		*ret = true;
		return (false);
	}
	if (io->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = expand_variables_in_line(data, *line);
		if (!(*line))
		{
			cleanup_pointer(*line);
			*ret = false;
			return (false);
		}
	}
	return (true);
}

// read line by line, validate and write in temp heredoc file
bool	process_heredoc_input(t_data *data, t_io_fds *io, int fd)
{
	char	*input_line;
	bool	operation_result;
	int		saved_exit_code;

	saved_exit_code = g_last_exit_code;
	operation_result = false;
	input_line = NULL;
	while (1)
	{
		configure_heredoc_signals();
		input_line = read_heredoc_line();
		configure_noninteractive_signals();
		if (!validate_heredoc_input(data, &input_line, io, &operation_result))
			break ;
		ft_putendl_fd(input_line, fd);
		cleanup_pointer(input_line);
	}
	cleanup_pointer(input_line);
	if (g_last_exit_code != 130)
		g_last_exit_code = saved_exit_code;
	return (operation_result);
}
