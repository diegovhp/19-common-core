/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 19:48:52 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/01 21:02:36 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// int	simulation_should_continue(t_dining_room *room)
// {
// 	return (!*(room->simulation_end));
// }

int	simulation_should_continue(t_dining_room *room)
{
	int	should_continue;

	pthread_mutex_lock(&room->output_mutex);
	should_continue = !*(room->simulation_end);
	pthread_mutex_unlock(&room->output_mutex);
	return (should_continue);
}

int	rest_peacefully(t_philosopher *philo)
{
	if (!simulation_should_continue(philo->dining_room))
		return (0);
	display_status(philo, "is sleeping 💤");
	precise_usleep(philo->config->sleep_duration);
	return (1);
}

int	contemplate_existence(t_philosopher *philo)
{
	if (!simulation_should_continue(philo->dining_room))
		return (0);
	display_status(philo, "is thinking 💭");
	usleep(500);
	return (1);
}
