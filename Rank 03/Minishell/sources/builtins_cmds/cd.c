/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:34 by tstevens          #+#    #+#             */
/*   Updated: 2025/08/07 16:29:23 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Construit un chemin de secours
basé sur le répertoire de travail stocké dans data et le nom cible.*/
static char	*construct_fallback_path(t_data *data, char *target)
{
	char	*base_path;
	char	*separator;
	char	*final_path;

	base_path = ft_strjoin(data->working_dir, "/");
	separator = base_path;
	final_path = ft_strjoin(separator, target);
	cleanup_pointer(separator);
	return (final_path);
}

/*Récupère le chemin absolu du répertoire courant,
ou utilise le chemin de secours en cas d'échec.*/
static char	*obtain_current_directory(t_data *data, char *target)
{
	char	*current_dir;
	char	buffer[PATH_MAX];

	current_dir = getcwd(buffer, PATH_MAX);
	if (!current_dir)
	{
		print_command_error("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		return (construct_fallback_path(data, target));
	}
	return (ft_strdup(buffer));
}

/*Met à jour les variables d'environnement PWD et
OLDPWD ainsi que les champs correspondants dans data.*/
static void	update_environment_paths(t_data *data, char *new_path)
{
	ft_set_environment_variable(data, "OLDPWD",
		ft_extract_environment_variable_value(data->env, "PWD"));
	ft_set_environment_variable(data, "PWD", new_path);
	if (data->old_working_dir)
	{
		cleanup_pointer(data->old_working_dir);
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
	{
		cleanup_pointer(data->working_dir);
		data->working_dir = ft_strdup(new_path);
	}
	cleanup_pointer(new_path);
}

/*Tente de changer de répertoire vers destination,
gère les erreurs, puis met à jour l'environnement.*/
static int	handle_directory_change(t_data *data, char *destination)
{
	char	*resolved_path;

	if (chdir(destination) != 0)
	{
		if (errno == ESTALE)
			errno = ENOENT;
		print_command_error("cd", destination, strerror(errno), errno);
		return (EXIT_FAILURE);
	}
	resolved_path = obtain_current_directory(data, destination);
	update_environment_paths(data, resolved_path);
	return (EXIT_SUCCESS);
}

/*Implémente la commande `cd` avec gestion des arguments spéciaux et erreurs.*/
int	builtin_change_directory(t_data *data, char **args)
{
	char	*destination;

	if (args[2])
		return (print_command_error("cd", NULL,
				"too many arguments", EXIT_FAILURE));
	if (!args || !args[1] || ft_isspace(args[1][0])
		|| args[1][0] == '\0' || ft_strncmp(args[1], "--", 3) == 0)
	{
		destination = ft_extract_environment_variable_value(data->env, "HOME");
		if (!destination || *destination == '\0' || ft_isspace(*destination))
			return (print_command_error("cd", NULL,
					"HOME not set", EXIT_FAILURE));
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		destination = ft_extract_environment_variable_value(data->env,
				"OLDPWD");
		if (!destination)
			return (print_command_error("cd", NULL,
					"OLDPWD not set", EXIT_FAILURE));
	}
	else
		destination = args[1];
	return (handle_directory_change(data, destination));
}
