/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alla@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:11:53 by alla              #+#    #+#             */
/*   Updated: 2022/03/06 12:11:55 by alla             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
		usleep(10);
	head->data->n_of_philo_have_eaten = 0;
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

void	monitor(t_philo *head)
{
	int		round;

	round = 1;
	start_countdown_of_death(head);
	head->data->n_of_philo_have_eaten = 0;
	while (head->data->all_philo_are_alive && head->data->n_of_t_each_philo_must_eat != 0)
	{
		if (is_even(head->data->n_of_philo) && round == 3)
			round = 1;
		else if (!is_even(head->data->n_of_philo) && round == 4)
			round = 1;
		make_philos_eat(head, round);
		wait_until_they_all_eat(head, round);
		++round;
		if (((is_even(head->data->n_of_philo) && round == 3) || (!is_even(head->data->n_of_philo) && round == 4)) && head->data->n_of_t_each_philo_must_eat > 0)
			--head->data->n_of_t_each_philo_must_eat;
	}
}
