#include "../include/philosophers.h"

int	is_even(int nb)
{
	return !(nb % 2);
}

void	refresh_timestamp(t_philo *philo)
{
	struct timeval	time;
	long int		time_now;

	gettimeofday(&time, NULL);
	time_now = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	philo->data->timestamp = time_now - philo->data->timestamp_start;
}

void	*print_eat_thread(void *philo_to_cast)
{
	t_philo		*philo;
	e_actions	action;

	philo = philo_to_cast;
	action = eat;
	print_action(philo, action);
	return (NULL);
}

void	*print_sleep_thread(void *philo_to_cast)
{
	t_philo		*philo;
	e_actions	action;

	philo = philo_to_cast;
	action = sleeps;
	print_action(philo, action);
	return (NULL);
}

void	*print_think_thread(void *philo_to_cast)
{
	t_philo		*philo;
	e_actions	action;

	philo = philo_to_cast;
	action = think;
	print_action(philo, action);
	return (NULL);
}

void	*print_die_thread(void *philo_to_cast)
{
	t_philo		*philo;
	e_actions	action;

	philo = philo_to_cast;
	action = die;
	print_action(philo, action);
	return (NULL);
}