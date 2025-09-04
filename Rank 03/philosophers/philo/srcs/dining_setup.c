/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:59:10 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/02 18:36:57 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	initialize_forks(t_dining_room *room, int count)
{
	int	i;

	room->forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!room->forks)
		return (1);
	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&(room->forks[i]), NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&(room->forks[i]));
			}
			free(room->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

void	assign_forks(t_philosopher *philo, pthread_mutex_t *forks, int id,
		int total)
{
	philo->left_fork = &forks[id];
	philo->right_fork = &forks[(id + 1) % total];
}

int	setup_philosopher_mutexes(t_philosopher *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&(philos[i].meal_mutex), NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&(philos[i].meal_mutex));
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	initialize_philosophers(t_philosopher **philos, t_config *config,
		t_dining_room *room)
{
	int	i;

	*philos = malloc(sizeof(t_philosopher) * config->total_philos);
	if (!*philos)
		return (1);
	i = 0;
	while (i < config->total_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].meals_consumed = 0;
		(*philos)[i].last_meal_time = get_current_time();
		assign_forks(&(*philos)[i], room->forks, i, config->total_philos);
		(*philos)[i].config = config;
		(*philos)[i].dining_room = room;
		i++;
	}
	return (setup_philosopher_mutexes(*philos, config->total_philos));
}

int	setup_dining_room(t_config *config, t_dining_room *room,
		t_philosopher **philos)
{
	if (initialize_forks(room, config->total_philos) != 0)
		return (1);
	if (pthread_mutex_init(&room->output_mutex, NULL) != 0)
	{
		destroy_forks(room->forks, config->total_philos);
		return (1);
	}
	if (initialize_philosophers(philos, config, room) != 0)
	{
		pthread_mutex_destroy(&room->output_mutex);
		destroy_forks(room->forks, config->total_philos);
		free(*philos);
		return (1);
	}
	return (0);
}
