/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alla@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:10:31 by alla              #+#    #+#             */
/*   Updated: 2022/02/28 23:27:06 by alla             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	error_handler(int err_code)
{
	if (err_code == 1)
		printf("Malloc failed !\n");
	if (err_code == 2)
		printf("Arguments error !\n");
	return (err_code);
}

int	is_valid_number(char *num)
{
	int	i;

	i = 0;
	while (num[i] && num[i] >= '0' && num[i] <= '9')
		++i;
	if (i && !num[i])
		return (1);
	return (0);
}

long long	ft_atoi(const char *s)
{
	long long	n;

	n = 0;
	while (*s && *s >= '0' && *s <= '9')
	{
		n = 10 * n + (*s - '0');
		s++;
	}
	return (n);
}

int	is_valid_args(int argc, char **argv, t_data *data)
{
	int			i;

	i = 1;
	if (argc != 6)
		return (0);
	if (is_valid_number(argv[i]))
		data->n_of_philo = ft_atoi(argv[i++]);
	if (is_valid_number(argv[i]))
		data->time_to_die = ft_atoi(argv[i++]);
	if (is_valid_number(argv[i]))
		data->time_to_eat = ft_atoi(argv[i++]);
	if (is_valid_number(argv[i]))
		data->time_to_sleep = ft_atoi(argv[i++]);
	if (is_valid_number(argv[i]))
		data->n_of_t_each_philo_must_eat = ft_atoi(argv[i++]);
	if (i != 6)
		return (0);
	return (1);
}

void	*petit_test(void *philo_to_cast)
{
	t_philo		*me;

	me = philo_to_cast;
	pthread_mutex_unlock(&me->data->init_philo_lock);
	while(me->data->all_philo_are_alive)
	{
		if (me->can_eat)
		{
			reset_time_to_die(me);
			do_action(me, eat);
			reset_time_to_die(me);
			do_action(me, sleep);
			do_action(me, think);
			me->can_eat = 0;
		}
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo	*head;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (error_handler(1));
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->init_philo_lock, NULL);
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&philo->data->time_death_lock, NULL);
	if (!is_valid_args(argc, argv, data))
		return (error_handler(2));
	start_all_philosophers(&head, data);
	monitor(head);
	usleep(1000);
	pthread_mutex_destroy(&data->init_philo_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&philo->data->time_death_lock);
	return (0);
}