/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:59:00 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/01 20:52:02 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_string_to_int(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	validate_arguments(t_config *config, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid argument count\n");
		return (1);
	}
	if (ft_string_to_int(av[1]) < 1)
	{
		printf("Error: Need at least one philosopher\n");
		return (1);
	}
	if (ft_string_to_int(av[2]) < 60 || ft_string_to_int(av[3]) < 60
		|| ft_string_to_int(av[4]) < 60)
	{
		printf("Error: Time values must be at least 60ms\n");
		return (1);
	}
	if (ac == 6 && ft_string_to_int(av[5]) < 1)
	{
		printf("Error: Meal count must be positive\n");
		return (1);
	}
	return (configure_simulation(config, ac, av));
}

int	configure_simulation(t_config *config, int ac, char **av)
{
	config->total_philos = ft_string_to_int(av[1]);
	config->death_time = ft_string_to_int(av[2]);
	config->eat_duration = ft_string_to_int(av[3]);
	config->sleep_duration = ft_string_to_int(av[4]);
	if (ac == 6)
		config->required_meals = ft_string_to_int(av[5]);
	else
		config->required_meals = -1;
	return (0);
}

void	display_status(t_philosopher *philo, char *action)
{
	int		should_continue;
	long	current_time;

	pthread_mutex_lock(&philo->dining_room->output_mutex);
	should_continue = !*(philo->dining_room->simulation_end);
	if (should_continue)
	{
		current_time = get_current_time() - philo->dining_room->start_timestamp;
		printf("%ld %d %s\n", current_time, philo->id, action);
	}
	pthread_mutex_unlock(&philo->dining_room->output_mutex);
}
