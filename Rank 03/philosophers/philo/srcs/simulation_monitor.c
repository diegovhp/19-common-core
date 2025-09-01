/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_monitor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:59:33 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/01 20:51:14 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	announce_death(t_philosopher *philo)
{
	long	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&philo->dining_room->output_mutex);
	if (*(philo->dining_room->simulation_end) == 0)
	{
		*(philo->dining_room->simulation_end) = 1;
		printf("%ld %d died ☠️\n", current_time
			- philo->dining_room->start_timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->dining_room->output_mutex);
}

int	check_philosopher_vitals(t_philosopher *philo, long current_time)
{
	long	time_since_last_meal;

	if (!simulation_should_continue(philo->dining_room))
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	time_since_last_meal = current_time - philo->last_meal_time;
	if (time_since_last_meal >= philo->config->death_time)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		announce_death(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

int	verify_meal_completion(t_philosopher *philos, t_config *config)
{
	int	i;
	int	all_satisfied;
	int	meals_count;

	if (config->required_meals <= 0)
		return (0);
	all_satisfied = 1;
	i = 0;
	while (i < config->total_philos)
	{
		pthread_mutex_lock(&philos[i].meal_mutex);
		meals_count = philos[i].meals_consumed;
		pthread_mutex_unlock(&philos[i].meal_mutex);
		if (meals_count < config->required_meals)
			all_satisfied = 0;
		i++;
	}
	if (all_satisfied)
	{
		pthread_mutex_lock(&philos[0].dining_room->output_mutex);
		*(philos[0].dining_room->simulation_end) = 1;
		pthread_mutex_unlock(&philos[0].dining_room->output_mutex);
		return (1);
	}
	return (0);
}

void	observe_simulation(t_philosopher *philos)
{
	int		i;
	long	current_time;

	usleep(500);
	while (simulation_should_continue(philos[0].dining_room))
	{
		i = 0;
		current_time = get_current_time();
		while (i < philos[0].config->total_philos)
		{
			if (check_philosopher_vitals(&philos[i], current_time))
				return ;
			i++;
		}
		if (verify_meal_completion(philos, philos[0].config))
			return ;
		usleep(500);
	}
}
