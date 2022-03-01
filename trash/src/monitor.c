#include "../include/philosophers.h"

void	print_action(t_philo *philo, e_actions action)
{
	int	time_stamp;

	time_stamp = 0;
	if (action == eat)
	{
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
}

void	do_action(t_philo	*philo, e_actions action)
{
	pthread_mutex_lock(&data->print_lock);
	print_action(philo, action);
	++philo->data->n_of_philo_have_eaten;
	pthread_mutex_unlock(&data->print_lock);
	if (action == eat)
		usleep(philo->data->time_to_eat * 100);
	else if (action == sleep)
		usleep(philo->data->time_to_sleep * 100);
	else if (action == think || action == die)
		continue;
}

void	monitor(t_philo *head)
{
	t_philo		*current_philo;

	current_philo = head;
	pthread_mutex_unlock(&head->data->monitor_lock);
	while (1)
	{
		head->data->n_of_philo_have_eaten = 0;
		while (current_philo->index != head->data->n_of_philo)
		{
			if (is_even(current_philo->index))
				current_philo->can_eat = 1;
			current_philo = current->philo->next;
		}
		while (head->data->n_of_philo_have_eaten != (head->data->n_of_philo / 2))
			continue;
		head->data->n_of_philo_have_eaten = 0;
		while (!is_even(current_philo->index))
		{
			if (!is_even(head->data->n_of_philo) && current_philo->index == head->data->n_of_philo)
				break;
			if (!is_even(current_philo->index))
				current_philo->can_eat = 1;
			current_philo = current->philo->next;
		}
		while (head->data->n_of_philo_have_eaten != (head->data->n_of_philo / 2))
			continue;
		if (!is_even(head->data->n_of_philo) && current_philo->index == head->data->n_of_philo)
				current_philo->can_eat = 1;
		while (current_philo->can_eat)
			continue;
	}
}