/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_life.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:59:26 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/01 21:03:29 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*live_philosopher_life(void *philosopher_data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher_data;
	if (philo ->id % 2 == 0)
		usleep(philo->config->eat_duration * 500);
	while (simulation_should_continue(philo->dining_room))
	{
		if (!attempt_fork_acquisition(philo))
			break ;
		if (!consume_meal(philo))
			break ;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (!rest_peacefully(philo))
			break ;
		if (!contemplate_existence(philo))
			break ;
	}
	return (NULL);
}

int	attempt_fork_acquisition(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (!simulation_should_continue(philo->dining_room))
		return (0);
	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	display_status(philo, "has taken a fork 🍴" );
	if (!simulation_should_continue(philo->dining_room))
	{
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	pthread_mutex_lock(second_fork);
	display_status(philo, "has taken a fork 🍴");
	return (1);
}

void	precise_usleep(long duration_ms)
{
	long	start_time;
	long	current_time;

	start_time = get_current_time();
	while (1)
	{
		current_time = get_current_time();
		if (current_time - start_time >= duration_ms)
			break ;
		usleep(500);
	}
}

int	consume_meal(t_philosopher *philo)
{
	if (!simulation_should_continue(philo->dining_room))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	display_status(philo, "is eating 🍝");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_consumed++;
	pthread_mutex_unlock(&philo->meal_mutex);
	precise_usleep(philo->config->eat_duration);
	return (1);
}
