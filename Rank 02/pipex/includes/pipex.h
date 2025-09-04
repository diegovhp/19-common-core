/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:58:14 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/07/29 19:57:16 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef PIPEX_H
// # define PIPEX_H

// # include <unistd.h>
// # include <sys/types.h>
// # include <sys/wait.h>
// # include <sys/stat.h>
// # include <fcntl.h>
// # include <stdlib.h>
// # include <stdio.h>
// # include "../libft/libft.h"

// // pipex.c
// void	child_process(char **argv, char **envp, int *fd);
// void	parent_process(char **argv, char **envp, int *fd);
// void	create_pipe_and_forks(char **argv, char **envp, int *fd);
// int		main(int argc, char **argv, char **envp);

// // utils.c
// void	free_split(char **split);
// char	*get_command_path(char **cmd_args, char **envp);
// char	*join_path_cmd(char *dir, char *cmd);
// int		find_path_env(char **envp);
// void	wait_and_exit();

// // path.c
// char	*search_in_paths(char **paths, char *cmd);
// char	*find_path(char *cmd, char **envp);
// void	error(void);

// #endif

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

// main.c
void	child_process(char **argv, char **envp, int *fd);
void	parent_process(char **argv, char **envp, int *fd);
void	create_pipe_and_forks(char **argv, char **envp, int *fd);
int		main(int argc, char **argv, char **envp);

// utils.c
void	free_split(char **split);
char	*get_command_path(char **cmd_args, char **envp);
char	*join_path_cmd(char *dir, char *cmd);
int		find_path_env(char **envp);
void	wait_and_exit(int *fd);

// path.c
char	*search_in_paths(char **paths, char *cmd);
char	*find_path(char *cmd, char **envp);
void	error(void);

// Fonctions libft nécessaires (à implémenter ou inclure)
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *s, int fd);

#endif
