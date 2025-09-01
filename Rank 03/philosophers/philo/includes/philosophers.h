/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-hem <dvan-hem@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:58:32 by dvan-hem          #+#    #+#             */
/*   Updated: 2025/09/01 20:52:24 by dvan-hem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/types.h>

typedef struct s_config
{
	int					total_philos;
	int					death_time;
	int					eat_duration;
	int					sleep_duration;
	int					required_meals;
}						t_config;

typedef struct s_dining_room
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		output_mutex;
	int					*simulation_end;
	long				start_timestamp;
}						t_dining_room;

typedef struct s_philosopher
{
	int					id;
	int					meals_consumed;
	long				last_meal_time;
	pthread_t			life_thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_mutex;
	t_config			*config;
	t_dining_room		*dining_room;
}						t_philosopher;

//cleanup utils
long	get_current_time(void);
void	join_philosopher_threads(t_philosopher *philos, int count);
void	destroy_philosopher_mutexes(t_philosopher *philos, int count);
void	destroy_forks(pthread_mutex_t *forks, int count);
void	cleanup_simulation(t_philosopher *philos, t_dining_room *room);

//config parser
int		ft_string_to_int(const char *str);
int		validate_arguments(t_config *config, int ac, char **av);
int		configure_simulation(t_config *config, int ac, char **av);
void	display_status(t_philosopher *philo, char *action);

//dining setup
int		initialize_forks(t_dining_room *room, int count);
void	assign_forks(t_philosopher *philo, pthread_mutex_t *forks,
			int id, int total);
int		setup_philosopher_mutexes(t_philosopher *philos, int count);
int		initialize_philosophers(t_philosopher **philos, t_config *config,
			t_dining_room *room);
int		setup_dining_room(t_config *config, t_dining_room *room,
			t_philosopher **philos);

//main
int		main(int ac, char **av);

//philosopher life
void	*live_philosopher_life(void *philosopher_data);
int		attempt_fork_acquisition(t_philosopher *philo);
int		consume_meal(t_philosopher *philo);
int		rest_peacefully(t_philosopher *philo);
int		contemplate_existence(t_philosopher *philo);
void	precise_usleep(long duration_ms);

//simulation monitor
int		simulation_should_continue(t_dining_room *room);
void	announce_death(t_philosopher *philo);
int		check_philosopher_vitals(t_philosopher *philo, long current_time);
int		verify_meal_completion(t_philosopher *philos, t_config *config);
void	observe_simulation(t_philosopher *philos);

#endif