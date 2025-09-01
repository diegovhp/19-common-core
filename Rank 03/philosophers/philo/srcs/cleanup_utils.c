/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:44:21 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/01 20:52:14 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	join_philosopher_threads(t_philosopher *philos, int count)
{
	int	i;
	int	join_result;

	i = 0;
	while (i < count)
	{
		join_result = pthread_join(philos[i].life_thread, NULL);
		if (join_result != 0)
		{
			usleep(1000);
			pthread_join(philos[i].life_thread, NULL);
		}
		i++;
	}
}

void	destroy_philosopher_mutexes(t_philosopher *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&philos[i].meal_mutex);
		i++;
	}
}

void	destroy_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	cleanup_simulation(t_philosopher *philos, t_dining_room *room)
{
	int	philosopher_count;

	philosopher_count = philos[0].config->total_philos;
	join_philosopher_threads(philos, philosopher_count);
	destroy_philosopher_mutexes(philos, philosopher_count);
	destroy_forks(room->forks, philosopher_count);
	pthread_mutex_destroy(&room->output_mutex);
	free(philos);
}
