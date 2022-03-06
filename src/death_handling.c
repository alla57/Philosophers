/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alla@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:12:00 by alla              #+#    #+#             */
/*   Updated: 2022/03/06 13:09:20 by alla             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	is_philo_dead(t_philo *philo)
{
	struct timeval	time;
	long int		time_now;
	long int		time_the_philo_dies;

	gettimeofday(&time, NULL);
	time_now = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	time_the_philo_dies = philo->time_to_die_start + philo->data->time_to_die;
	if (time_the_philo_dies <= time_now && !philo->can_eat)
	{
		philo->is_dead = 1;
		philo->data->all_philo_are_alive = 0;
		return (1);
	}
	return (0);
}

void	reset_time_to_die(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->time_to_die_start = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	*check_death_philo(void *philo_to_cast)
{
	t_philo			*philo;
	struct timeval	time;

	philo = philo_to_cast;
	gettimeofday(&time, NULL);
	philo->data->timestamp_start = ((time.tv_sec * 1000) + \
	(time.tv_usec / 1000));
	while (philo->index < philo->data->n_of_philo)
	{
		reset_time_to_die(philo);
		philo = philo->next;
	}
	reset_time_to_die(philo);
	philo = philo->next;
	while (philo->data->n_of_t_each_philo_must_eat != 0)
	{
		if (is_philo_dead(philo))
		{
			do_action(philo, die);
			break ;
		}
		philo = philo->next;
		usleep(50);
	}
	return (NULL);
}

void	start_countdown_of_death(t_philo *philo)
{
	int				thread_err;
	pthread_t		thread_id;
	struct timeval	time;

	gettimeofday(&time, NULL);
	philo->data->timestamp_start = ((time.tv_sec * 1000) + \
	(time.tv_usec / 1000));
	thread_err = pthread_create(&thread_id, NULL, check_death_philo, philo);
	if (thread_err != 0)
		return ;
	pthread_detach(thread_id);
}
