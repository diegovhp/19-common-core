/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstevens <tstevens@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:16:46 by tstevens          #+#    #+#             */
/*   Updated: 2025/08/07 16:34:04 by tstevens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Vérifie si le nombre dépasse la plage des
LONG et met à jour l'erreur en conséquence.*/
static bool	validate_numeric_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX)
		|| (neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

/*Convertit une chaîne en LONG en détectant
les erreurs de dépassement et de format.*/
static int	convert_str_to_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (validate_numeric_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

/*Analyse l'argument de sortie pour vérifier
sa validité numérique et calcule le code de sortie modulo 256.*/
static int	parse_exit_status(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_last_exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = convert_str_to_long(arg, error);
	return (i % 256);
}

/*Détermine si la commande exit est dans un pipeline
(mode silencieux) en vérifiant
la présence de commandes précédentes ou suivantes.*/
static bool	detect_silent_mode(t_data *data)
{
	t_command	*command;

	command = data->cmd;
	if (!command)
		return (false);
	if (command->next != NULL || command->prev != NULL)
		return (true);
	return (false);
}

/*Gère la commande exit en validant les arguments, affichant
un message si interactif, et terminant le shell avec le code approprié.*/
int	builtin_exit_shell(t_data *data, char **args)
{
	int		exit_code;
	bool	error;
	bool	quiet_mode;

	quiet_mode = detect_silent_mode(data);
	error = false;
	if (!quiet_mode && data->interactive)
		ft_putendl_fd("exit", 2);
	if (!args || !args[1])
		exit_code = g_last_exit_code;
	else
	{
		exit_code = parse_exit_status(args[1], &error);
		if (error)
			exit_code = print_command_error("exit", args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (print_command_error("exit", NULL, "too many arguments", 1));
	}
	terminate_shell(data, exit_code);
	return (2);
}
