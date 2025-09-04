/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:17:20 by tstevens          #+#    #+#             */
/*   Updated: 2025/08/07 16:15:15 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Vérifie si le chemin donné correspond à un répertoire en utilisant stat.*/
bool	is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

/*Vérifie la validité d'une commande : existence,
non-répertoire, et permissions d'exécution ; affiche une erreur sinon.*/
int	check_cmd_valid(t_data *data, t_command *cmd)
{
	if (ft_strchr(cmd->command, '/') == NULL
		&& ft_find_environment_variable_index(data->env, "PATH") != -1)
		return (print_command_error(cmd->command, NULL, "command not found",
				CMD_NOT_FOUND));
	if (access(cmd->command, F_OK) != 0)
		return (print_command_error(cmd->command, NULL, strerror(errno),
				CMD_NOT_FOUND));
	else if (is_dir(cmd->command))
		return (print_command_error(cmd->command, NULL, "Is a directory",
				CMD_NOT_EXECUTABLE));
	else if (access(cmd->command, F_OK | X_OK) != 0)
		return (print_command_error(cmd->command, NULL, strerror(errno),
				CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
