/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:42:46 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/01/09 20:06:02 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] && line[count] != '\n')
		count++;
	if (!line[count])
		return (NULL);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count - 1);
	if (!backup)
		return (NULL);
	line[count + 1] = '\0';
	return (backup);
}

static char	*update_backup(char **backup, char *buffer)
{
	char	*temp;

	if (!*backup)
		*backup = ft_strdup("");
	if (!*backup)
		return (NULL);
	temp = ft_strjoin(*backup, buffer);
	free(*backup);
	if (!temp)
		return (NULL);
	*backup = temp;
	return (*backup);
}

static char	*handle_read(int fd, char *buffer, char **backup)
{
	int	read_len;

	read_len = read(fd, buffer, BUFFER_SIZE);
	while (read_len > 0)
	{
		buffer[read_len] = '\0';
		if (!update_backup(backup, buffer))
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
		read_len = read(fd, buffer, BUFFER_SIZE);
	}
	if (read_len < 0)
	{
		free(*backup);
		*backup = NULL;
		return (NULL);
	}
	return (*backup);
}

static char	*read_fd(int fd, char *buffer, char **backup)
{
	char	*result;

	result = handle_read(fd, buffer, backup);
	if (!result)
	{
		if (*backup && **backup == '\0')
		{
			free(*backup);
			*backup = NULL;
		}
		return (NULL);
	}
	return (*backup);
}

char	*get_next_line(int fd)
{
	static char	*backup = NULL;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_fd(fd, buffer, &backup);
	free(buffer);
	if (!line)
		return (NULL);
	backup = extract_line(line);
	if (!backup && ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
