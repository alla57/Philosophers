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
	t_philo	*philo;

	philo = philo_to_cast;
	while (philo->index < philo->data->n_of_philo)
	{
		reset_time_to_die(philo);
		philo = philo->next;
	}
	reset_time_to_die(philo);
	philo = philo->next;
	while (1)
	{
		if (is_philo_dead(philo))
		{
			do_action(philo, die);
			break;
		}
		else
			philo = philo->next;
		usleep(50);// a voir si ça fonctionne pas changer la valeur ou faire un thread qui check la mort pour chaque
	}
	return (NULL);
}

void	start_countdown_of_death(t_philo *philo)
{
	int			thread_err;
	pthread_t	thread_id;

	thread_err = pthread_create(&thread_id, NULL, check_death_philo, philo);
	if (thread_err != 0)
		return ; //gerer le retour d'erreur
	pthread_detach(thread_id);
}

void	make_philos_eat(t_philo *head, int round)
{
	t_philo *current_philo;
	int		is_round_finish;

	current_philo = head;
	is_round_finish = 0;
	while (!is_round_finish)
	{
		if (!is_even(head->data->n_of_philo) && round == 3)
		{
			head->prev->can_eat = 1;
			is_round_finish = 1;
		}
		else if (is_even(current_philo->index) && is_even(round))
			current_philo->can_eat = 1;
		else if (!is_even(current_philo->index) && !is_even(round) && current_philo != head->prev)
			current_philo->can_eat = 1;
		current_philo = current_philo->next;
		if (current_philo == head)
			is_round_finish = 1;
	}
}

int	all_philo_have_eaten(t_philo *philo, int round)
{
	if (philo->data->n_of_philo_have_eaten == (philo->data->n_of_philo / 2))
		return (1);
	else if (!is_even(philo->data->n_of_philo) && round == 3 && philo->data->n_of_philo_have_eaten == 1)
		return (1);
	return (0);
}

void	wait_until_they_all_eat(t_philo *head, int round)
{
	while (head->data->all_philo_are_alive && !all_philo_have_eaten(head, round))
		usleep(100);
	head->data->n_of_philo_have_eaten = 0;
}

void	print_action(t_philo *philo, e_actions action)
{
	int	time_stamp;

	time_stamp = 0;
	pthread_mutex_lock(&philo->data->print_lock);
	if (action == eat)
	{
		printf(	WHT "%.6d" BLU "  %.3d" YEL "  has taken a fork\n" \
				WHT "%.6d" BLU "  %.3d" YEL "  has taken a fork\n" \
				WHT "%.6d" BLU "  %.3d" GRN "  is eating\n", time_stamp, philo->index, time_stamp, philo->index, time_stamp, philo->index);
	}
	else if (action == sleeps)
	{
		printf(WHT "%.6d" BLU "  %.3d" CYN "  is sleeping\n", time_stamp, philo->index);
		++philo->data->n_of_philo_have_eaten;
	}
	else if (action == think)
		printf(WHT "%.6d" BLU "  %.3d" MAG "  is thinking\n", time_stamp, philo->index);
	else if (action == die)
		printf(WHT "%.6d" BLU "  %.3d" RED "  died\n", time_stamp, philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	do_action(t_philo	*philo, e_actions action)
{
	// int			thread_err;
	// pthread_t	thread_id;

	// print_action(philo, action);
	//philo->action = action;
	// thread_err = pthread_create(&thread_id, NULL, print_thread, philo);
	// if (thread_err != 0)
	// 	return; //gérer l'erreur
	if (action == eat)
	{
		print_action(philo, action);//thread_err = pthread_create(&thread_id, NULL, print_eat_thread, philo);
		usleep(philo->data->time_to_eat * 1000);
	}
	else if (action == sleeps)
	{
		print_action(philo, action);//thread_err = pthread_create(&thread_id, NULL, print_sleep_thread, philo);
		usleep(philo->data->time_to_sleep * 1000);
	}
	else if (action == think)// || action == die)
		print_action(philo, action);//thread_err = pthread_create(&thread_id, NULL, print_think_thread, philo);
	else if (action == die)
		print_action(philo, action);//thread_err = pthread_create(&thread_id, NULL, print_die_thread, philo);
	// if (thread_err != 0)
		// return ;
}

void	monitor(t_philo *head)
{
	int		round;

	round = 1;
	start_countdown_of_death(head);
	while (head->data->all_philo_are_alive)
	{
		if (is_even(head->data->n_of_philo) && round == 3)
			round = 1;
		else if (!is_even(head->data->n_of_philo) && round == 4)
			round = 1;
		make_philos_eat(head, round);
		wait_until_they_all_eat(head, round);
		++round;
	}
}