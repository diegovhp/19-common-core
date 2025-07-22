/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_core2_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:19:23 by tstevens          #+#    #+#             */
/*   Updated: 2025/07/22 19:44:00 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*reconstruct_string_from_array(char **tab)
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

static bool	validate_heredoc_input(t_data *data, char **line,
	t_io_fds *io, bool *ret)
{
	if (*line == NULL)
	{
		print_command_error("warning",
			"here-document delimited by end-of-file: wanted",
			io->heredoc_limit, true);
		*ret = true;
		return (false);
	}
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

bool	process_heredoc_input(t_data *data, t_io_fds *io, int fd)
{
	char	*input_line;
	bool	operation_result;

	operation_result = false;
	input_line = NULL;
	while (1)
	{
		configure_interactive_signals();
		input_line = readline(">");
		configure_noninteractive_signals();
		if (!validate_heredoc_input(data, &input_line, io, &operation_result))
			break ;
		ft_putendl_fd(input_line, fd);
		cleanup_pointer(input_line);
	}
	cleanup_pointer(input_line);
	return (operation_result);
}
