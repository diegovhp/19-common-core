/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:13:43 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/09 16:22:10 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static char	*read_map_lines(int fd, char *buffer, t_game *g)
{
	char	*line;
	char	*tmp;
	int		j;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		j = 0;
		while (line[j])
		{
			if (line[j] == 'P')
				g->player_count++;
			else if (line[j] == 'E')
				g->exit_count++;
			j++;
		}
		tmp = buffer;
		buffer = ft_strjoin(buffer, line);
		free(tmp);
		free(line);
	}
	return (buffer);
}

char	**parse_map(char *filename, t_game *g)
{
	int		fd;
	char	*buffer;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		clean_exit(g, NULL, EXIT_FAILURE);
	buffer = get_next_line(fd);
	if (!buffer)
		clean_exit(g, NULL, EXIT_FAILURE);
	buffer = read_map_lines(fd, buffer, g);
	close(fd);
	map = ft_split(buffer, '\n');
	if (!map)
		clean_exit(g, NULL, EXIT_FAILURE);
	if (buffer)
		free(buffer);
	g->height = map_height(map);
	g->width = map_width(map);
	return (map);
}

// char	**parse_map(char *filename, t_game *g)
// {
// 	int		fd;
// 	char	*line;
// 	char	*buffer;
// 	char	**map;
// 	char	*tmp;

// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		ft_error("Error: Failed to open map file.");
// 	buffer = get_next_line(fd);
// 	if (!buffer)
// 		ft_error("Error: Map is empty or invalid.");
// 	line = NULL;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		tmp = buffer;
// 		buffer = ft_strjoin(buffer, line);
// 		free(tmp);
// 		free(line);
// 	}
// 	close(fd);
// 	map = ft_split(buffer, '\n');
// 	free(buffer);
// 	g->height = map_height(map);
// 	g->width = map_width(map);
// 	return (map);
// }
