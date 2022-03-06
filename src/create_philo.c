/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alla@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:11:49 by alla              #+#    #+#             */
/*   Updated: 2022/03/06 12:11:50 by alla             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	add_philo_to_list(t_philo *head, t_philo *new)
{
	t_philo	*last;

	last = head->prev;
	last->next = new;
	new->prev = last;
	new->next = head;
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
	philo->can_eat = 0;
	philo->is_dead = 0;
	philo->data = data;
	philo->prev = philo;
	philo->next = philo;
	return (philo);
}

void	create_all_philosophers(t_philo **head, t_data *data)
{
	int		index;
	t_philo	*philo;

	index = 1;
	philo = create_new_philo(index, data);
	data->all_philo_are_alive = 1;
	*head = philo;
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
		thread_err = pthread_create(&philo->id, NULL, philosopher, philo);
		philo = philo->next;
	}
}
