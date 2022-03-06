/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alla@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:11:57 by alla              #+#    #+#             */
/*   Updated: 2022/03/06 13:16:52 by alla             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	one_philo(t_data *data)
{
	if (data->n_of_philo != 1)
		return (0);
	printf(WHT "%.6d" BLU "  %.3d" YEL "  has taken a fork\n", 0, 1);
	usleep(data->time_to_die * 1000);
	printf(WHT "%.6d" BLU "  %.3d" RED "  died\n", data->time_to_die, 1);
	free(data);
	return (1);
}

void	refresh_timestamp(t_philo *philo)
{
	struct timeval	time;
	long int		time_now;

	gettimeofday(&time, NULL);
	time_now = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	philo->data->timestamp = time_now - philo->data->timestamp_start;
}

void	print_action(t_philo *philo, t_actions action)
{
	pthread_mutex_lock(&philo->data->print_lock);
	refresh_timestamp(philo);
	if (action == eat)
	{
		printf(WHT "%.6ld" BLU "  %.3d" YEL "  has taken a fork\n" \
		WHT "%.6ld" BLU "  %.3d" YEL "  has taken a fork\n" \
		WHT "%.6ld" BLU "  %.3d" GRN "  is eating\n", philo->data->timestamp, \
		philo->index, philo->data->timestamp, philo->index, \
		philo->data->timestamp, philo->index);
	}
	else if (action == sleeps)
	{
		printf(WHT "%.6ld" BLU "  %.3d" CYN "  is sleeping\n", \
		philo->data->timestamp, philo->index);
		++philo->data->n_of_philo_have_eaten;
	}
	else if (action == think)
		printf(WHT "%.6ld" BLU "  %.3d" MAG "  is thinking\n", \
		philo->data->timestamp, philo->index);
	else if (action == die)
		printf(WHT "%.6ld" BLU "  %.3d" RED "  died\n", \
		philo->data->timestamp, philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	do_action(t_philo	*philo, t_actions action)
{
	if (action == eat)
	{
		print_action(philo, action);
		usleep(philo->data->time_to_eat * 1000);
	}
	else if (action == sleeps)
	{
		print_action(philo, action);
		usleep(philo->data->time_to_sleep * 1000);
	}
	else if (action == think)
		print_action(philo, action);
	else if (action == die)
		print_action(philo, action);
}

void	*philosopher(void *philo_to_cast)
{
	t_philo		*me;

	me = philo_to_cast;
	while (me->data->all_philo_are_alive && \
	me->data->n_of_t_each_philo_must_eat != 0)
	{
		if (me->can_eat)
		{
			do_action(me, eat);
			if (!me->data->all_philo_are_alive)
				break ;
			reset_time_to_die(me);
			me->can_eat = 0;
			do_action(me, sleeps);
			if (!me->data->all_philo_are_alive)
				break ;
			do_action(me, think);
		}
		else
			usleep(100);
	}
	return (NULL);
}
