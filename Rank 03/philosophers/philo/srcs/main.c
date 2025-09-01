/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:59:17 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/01 21:03:20 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*single_philosopher_life(void *philosopher_data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher_data;
	pthread_mutex_lock(philo->left_fork);
	display_status(philo, "has taken a fork 🍴");
	while (simulation_should_continue(philo->dining_room))
		usleep(100);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

static int	create_philosopher_threads(t_philosopher *philos, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->total_philos)
	{
		if (pthread_create(&(philos[i].life_thread), NULL,
				live_philosopher_life, &philos[i]) != 0)
		{
			*(philos[0].dining_room->simulation_end) = 1;
			printf("Thread creation failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static void	launch_simulation(t_philosopher *philos, t_config *config)
{
	int		i;
	long	simulation_start;

	simulation_start = get_current_time();
	philos->dining_room->start_timestamp = simulation_start;
	i = 0;
	while (i < config->total_philos)
	{
		philos[i].last_meal_time = simulation_start;
		i++;
	}
	if (config->total_philos == 1)
	{
		if (pthread_create(&(philos[0].life_thread), NULL,
				single_philosopher_life, &philos[0]) != 0)
		{
			*(philos[0].dining_room->simulation_end) = 1;
			printf("Thread creation failed\n");
		}
		return ;
	}
	create_philosopher_threads(philos, config);
}

int	main(int ac, char **av)
{
	t_config		config;
	t_dining_room	dining_room;
	t_philosopher	*philosophers;
	int				end_flag;

	end_flag = 0;
	dining_room.simulation_end = &end_flag;
	if (validate_arguments(&config, ac, av) != 0)
		return (1);
	if (setup_dining_room(&config, &dining_room, &philosophers) != 0)
		return (1);
	launch_simulation(philosophers, &config);
	observe_simulation(philosophers);
	cleanup_simulation(philosophers, &dining_room);
	return (0);
}
