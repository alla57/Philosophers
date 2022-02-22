#include "../include/philosophers.h"

void	add_philo_to_list(t_philo *head, t_philo *new)
{
	t_philo	*first;
	t_philo	*last;

	first = head->next;
	last = head->prev;
	last->next = new;
	new->prev = last;
	new->next = first;
	first->prev = new;
	head->prev = new;
}

t_philo	*create_new_philo(int index, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->index = index;
	philo->is_eating = 0;
	philo->data = data;
	philo->prev = NULL;
	philo->next = NULL;
	return (philo);
}

void	create_all_philosophers(t_philo **head, t_data *data)
{
	int		index;
	t_philo	*philo;

	index = 1;
	*head = create_new_philo(index, data);
	while (++index <= data->n_of_philo)
	{
		philo = create_new_philo(index, data);
		add_philo_to_list(*head, philo);
	}
}

void	start_all_philosophers(t_philo **head, t_data *data)
{
	t_philo	*philo;
	int		thread_err;
	int		i;

	create_all_philosophers(head, data);
	i = 0;
	thread_err = 0;
	philo = *head;
	while (!thread_err && ++i <= data->n_of_philo)
	{
		pthread_mutex_lock(&data->init_philo_lock);
		thread_err = pthread_create(&philo->id, NULL, petit_test, philo);
		pthread_mutex_lock(&data->init_philo_lock);
		pthread_mutex_unlock(&data->init_philo_lock);
		philo = philo->next;
	}
	pthread_mutex_lock(&data->begin_simulation_lock);
	pthread_mutex_unlock(&data->begin_simulation_lock);
}
// printf("number of philo : %d\n", arg_data->n_of_philo);
// while (!thread_err && ++i <= arg_data->n_of_philo)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		thread_err = pthread_create(&philo->id, NULL, petit_test, &i);
// 		pthread_mutex_lock(&mutex);
// 		pthread_mutex_unlock(&mutex);
// 		// pthread_join(philo->id, NULL);
// 	}