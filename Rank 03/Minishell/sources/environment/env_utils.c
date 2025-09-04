/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:03:42 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/08/07 16:26:57 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Crée une chaîne "variable_name="
utilisée pour rechercher une variable d'environnement.*/
char	*ft_create_search_pattern(char *variable_name)
{
	char	*search_pattern;

	search_pattern = ft_strjoin(variable_name, "=");
	if (!search_pattern)
		return (NULL);
	return (search_pattern);
}

/*Vérifie que le premier caractère d'une clé
d'environnement est une lettre ou un underscore.*/
static bool	ft_validate_env_key_start(char first_char)
{
	if (ft_isalpha(first_char) == 0 && first_char != '_')
		return (false);
	return (true);
}

/*Vérifie que tous les caractères de la clé, sauf le premier,
sont alphanumériques ou underscore jusqu'au signe '='.*/
static bool	ft_validate_env_key_chars(char *variable_name)
{
	int	char_index;

	char_index = 1;
	while (variable_name[char_index] && variable_name[char_index] != '=')
	{
		if (ft_isalnum(variable_name[char_index]) == 0
			&& variable_name[char_index] != '_')
			return (false);
		char_index++;
	}
	return (true);
}

/*Valide que la clé d'une variable
d'environnement respecte les règles de syntaxe.*/
bool	ft_validate_environment_variable_key(char *variable_name)
{
	if (!ft_validate_env_key_start(variable_name[0]))
		return (false);
	if (!ft_validate_env_key_chars(variable_name))
		return (false);
	return (true);
}

/*Compte le nombre de variables d'environnement dans un tableau de chaînes.*/
int	ft_count_environment_variables(char **environment_array)
{
	int	variable_count;

	variable_count = 0;
	while (environment_array && environment_array[variable_count])
		variable_count++;
	return (variable_count);
}
