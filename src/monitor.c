#include "../include/philosophers.h"

void	*countdown(void *philo_to_cast)
{
	t_philo 	*philo;
	long int	start_time;

	philo = philo_to_cast;
	while ()
}

void	start_countdown(t_philo *philo)
{
	pthread_t	countdown_thread;
	int			thread_err;

	thread_err = pthread_create(&countdown_thread, NULL, countdown, philo);
	if (thread_err != 0)
		return ; //////return erreur
}

int	special_round(t_philo *philo, int round)
{
	if (!is_even(head->n_of_philo) && (round % 3) == 0)
	{
		philo->can_eat = 1;
		return (1);
	}
	return (0);
}

int	all_philo_have_eaten(t_philo *philo)
{
	if (philo->data->n_of_philo_have_eaten != (philo->data->n_of_philo / 2))
		return (1);
	else if (philo->index == philo->data->n_of_philo)
		return (1);
	return (0);
}

void	wait_until_they_all_eat(t_philo *head)
{
	pthread_mutex_lock(&head->data->eat_lock);
	head->data->n_of_philo_have_eaten = 0;
	pthread_mutex_unlock(&head->data->eat_lock);
}

void	print_action(t_philo *philo, e_actions action)
{
	int	time_stamp;

	time_stamp = 0;
	pthread_mutex_lock(&data->print_lock);
	if (action == eat)
	{
		++philo->data->n_of_philo_have_eaten;
		printf(WHT "%.6d" BLU "  %.3d" YEL "  has taken a fork\n", time_stamp, philo->index);
		printf(WHT "%.6d" BLU "  %.3d" YEL "  has taken a fork\n", time_stamp, philo->index);
		printf(WHT "%.6d" BLU "  %.3d" GRN "  is eating\n", time_stamp, philo->index);
	}
	else if (action == sleep)
	{
		printf(WHT "%.6d" BLU "  %.3d" CYN "  is sleeping\n", time_stamp, philo->index);
	}
	else if (action == think)
	{
		printf(WHT "%.6d" BLU "  %.3d" BLK "  is thinking\n", time_stamp, philo->index);
	}
	else if (action == die)
		printf(WHT "%.6d" BLU "  %.3d" RED "  died\n", time_stamp, philo->index);
	pthread_mutex_unlock(&data->print_lock);
}

void	do_action(t_philo	*philo, e_actions action)
{
	print_action(philo, action);
	if (action == eat)
	{
		usleep(philo->data->time_to_eat * 1000);
		if (all_philo_have_eaten(philo))
			pthread_mutex_unlock(&philo->data->eat_lock);
	}
	else if (action == sleep)
		usleep(philo->data->time_to_sleep * 1000);
	else if (action == think || action == die)
		continue;
}

void	monitor(t_philo *head)
{
	t_philo	*current_philo;
	int		round;

	current_philo = head; // on peut mettre current_philo dans le proto de la func direct
	round = 1;
	pthread_mutex_unlock(&head->data->monitor_lock);
	start_coutdown(head);
	while (1)
	{
		pthread_mutex_lock(&head->data->eat_lock);
		while (current_philo != head)
		{
			if (special_round(current_philo, round))
				break;
			if (is_even(current_philo->index) && is_even(round))
				current_philo->can_eat = 1;
			else if (!is_even(current_philo->index) && !is_even(round) && current_philo != head->prev)
				current_philo->can_eat = 1;
			current_philo = current_philo->next;
		}
		wait_until_they_all_eat(head);
		++round;
	}
}