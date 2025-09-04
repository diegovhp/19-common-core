/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:40:27 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/29 21:31:31 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*create_line_and_backup(char **backup, size_t count)
{
	char	*line;
	char	*new_backup;

	if ((*backup)[count] == '\n')
		line = ft_substr(*backup, 0, count + 1);
	else
		line = ft_substr(*backup, 0, count);
	if (!line)
		return (NULL);
	if ((*backup)[count] == '\n' && (*backup)[count + 1])
		new_backup = ft_substr(*backup, count + 1,
				ft_strlen(*backup) - count - 1);
	else
		new_backup = NULL;
	if ((*backup)[count] == '\n' && (*backup)[count + 1] && !new_backup)
	{
		free(line);
		return (NULL);
	}
	free(*backup);
	*backup = new_backup;
	return (line);
}

static char	*get_line(char **backup)
{
	size_t	count;
	char	*line;

	count = 0;
	while ((*backup)[count] && (*backup)[count] != '\n')
		count++;
	line = create_line_and_backup(backup, count);
	if (!line)
	{
		if (*backup)
		{
			free(*backup);
			*backup = NULL;
		}
	}
	return (line);
}

static char	*add_to_backup(char **backup, char *buffer)
{
	char	*temp;

	if (!*backup)
	{
		*backup = ft_strdup(buffer);
		return (*backup);
	}
	temp = ft_strjoin(*backup, buffer);
	free(*backup);
	*backup = temp;
	return (*backup);
}

static int	read_and_update(int fd, char *buffer, char **backup)
{
	int	read_len;

	read_len = read(fd, buffer, BUFFER_SIZE);
	while (read_len > 0)
	{
		buffer[read_len] = '\0';
		if (!add_to_backup(backup, buffer))
			return (-1);
		if (ft_strchr(buffer, '\n'))
			break ;
		read_len = read(fd, buffer, BUFFER_SIZE);
	}
	return (read_len);
}

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*buffer;
	int			read_result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (backup && ft_strchr(backup, '\n'))
		return (get_line(&backup));
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_result = read_and_update(fd, buffer, &backup);
	free(buffer);
	if (read_result < 0 || !backup || *backup == '\0')
	{
		if (backup)
		{
			free(backup);
			backup = NULL;
		}
		return (NULL);
	}
	return (get_line(&backup));
}
