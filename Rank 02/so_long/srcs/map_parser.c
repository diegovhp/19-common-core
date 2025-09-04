/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:51:52 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/02 17:50:18 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static char	*read_file_content(int fd, char *buffer, t_gamestate *game)
{
	char	*line;
	char	*temp;
	int		i;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
		while (line[i])
		{
			if (line[i] == 'P')
				game->player_instances++;
			else if (line[i] == 'E')
				game->exit_instances++;
			i++;
		}
		temp = buffer;
		buffer = ft_strjoin(buffer, line);
		if (!buffer)
			return (free_both(temp, line), NULL);
		free_both(temp, line);
	}
	return (buffer);
}

// lecture line par linge, check P et E, tableau 2d avec split, check size
char	**extract_map(char *filename, t_gamestate *game)
{
	int		fd;
	char	*buffer;
	char	**grid;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		safe_exit(game, NULL, EXIT_FAILURE);
	buffer = get_next_line(fd);
	if (!buffer)
		safe_exit(game, NULL, EXIT_FAILURE);
	buffer = read_file_content(fd, buffer, game);
	close(fd);
	grid = ft_split(buffer, '\n');
	if (!grid)
		safe_exit(game, NULL, EXIT_FAILURE);
	if (buffer)
		free(buffer);
	game->map_height = calculate_height(grid);
	game->map_width = calculate_width(grid);
	return (grid);
}

int	calculate_height(char **grid)
{
	int	height;

	height = 0;
	while (grid[height])
		height++;
	return (height);
}

int	calculate_width(char **grid)
{
	if (!grid || !grid[0])
		return (0);
	return (ft_strlen(grid[0]));
}

void	deallocate_map(char **grid)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}
