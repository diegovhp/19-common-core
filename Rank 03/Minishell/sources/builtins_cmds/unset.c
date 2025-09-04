/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:57 by tstevens          #+#    #+#             */
/*   Updated: 2025/08/07 16:36:08 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Supprime les variables d'environnement valides
passées en arguments, affiche une erreur pour les identifiants invalides.*/
int	builtin_remove_variable(t_data *data, char **args)
{
	int	i;
	int	idx;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!ft_validate_environment_variable_key(args[i])
			|| ft_strchr(args[i], '=') != NULL)
		{
			print_command_error("unset", args[i],
				"not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else
		{
			idx = ft_find_environment_variable_index(data->env, args[i]);
			if (idx != -1)
				ft_remove_environment_variable(data, idx);
		}
		i++;
	}
	return (ret);
}
