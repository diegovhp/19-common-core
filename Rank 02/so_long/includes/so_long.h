/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:50:27 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/03 16:08:06 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

# define SPRITE_SIZE 64
# define MOVE_UP 119
# define MOVE_LEFT 97
# define MOVE_DOWN 115
# define MOVE_RIGHT 100
# define EXIT_KEY 65307

typedef struct s_position
{
	int			col;
	int			row;
}				t_position;

typedef struct s_pathfind
{
	int			**explored;
	int			collectibles_reached;
	int			exit_reachable;
}				t_pathfind;

typedef struct s_gamestate
{
	void		*mlx_ptr;
	void		*window_ptr;
	char		**grid;
	int			map_width;
	int			map_height;
	int			move_count;
	int			items_collected;
	int			player_instances;
	int			exit_instances;
	int			total_items;
	t_position	player_pos;
	void		*sprite_player;
	void		*sprite_wall;
	void		*sprite_floor;
	void		*sprite_item;
	void		*sprite_exit;
	t_pathfind	pathfinder;
}				t_gamestate;

void			validate_filename(char *filename);
void			setup_game(t_gamestate *game, char *filename);
void			launch_game(t_gamestate *game);

char			**extract_map(char *filename, t_gamestate *game);
void			validate_map_structure(t_gamestate *game);
void			validate_path_access(t_gamestate *game);
int				calculate_height(char **grid);
int				calculate_width(char **grid);
void			deallocate_map(char **grid);
void			prepare_pathfind(t_gamestate *game);
void			explore_paths(t_gamestate *game, int col, int row);

void			draw_game(t_gamestate *game);
int				handle_movement(int keycode, t_gamestate *game);
void			display_moves(int moves);

void			cleanup_all(t_gamestate *game);
void			error_exit(char *message);
void			safe_exit(t_gamestate *game, char *msg, int code);
void			cleanup_pathfind(t_gamestate *game);

void			free_both(char *tmp, char *line);
int				process_input(int keycode, t_gamestate *game);
int				handle_exit(t_gamestate *game);

#endif