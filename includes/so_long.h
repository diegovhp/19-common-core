/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:20:49 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/04/09 16:13:18 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "../libft/libft.h"

# define TILE_SIZE 64
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_flood
{
	int			**visited;
	int			collectibles_found;
	int			exit_found;
}	t_flood;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	int			width;
	int			height;
	int			moves;
	int			collected;
	int			player_count;
	int			exit_count;
	int			total_collectibles;
	t_vector	player;
	void		*player_img;
	void		*wall_img;
	void		*floor_img;
	void		*collectible_img;
	void		*exit_img;
	t_flood		flood;
}	t_game;

/* main/init */
void	check_file_extension(char *filename);
void	init_game(t_game *g, char *filename);
void	start_game(t_game *g);

/* parsing */
char	**parse_map(char *filename, t_game *g);
void	check_map_validity(t_game *g);
void	check_path_validity(t_game *g);
int		map_height(char **map);
int		map_width(char **map);
void	free_map(char **map);
void	init_flood_structure(t_game *g);
void	flood_fill(t_game *g, int x, int y);

/* rendering + input */
void	render_map(t_game *g);
int		move_player(int keycode, t_game *g);
void	print_moves(int moves);

/* events */
void	free_all(t_game *g);
void	ft_error(char *message);
void	clean_exit(t_game *g, char *msg, int code);
void	free_flood(t_game *g);

#endif
