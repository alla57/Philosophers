/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alla@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:10:31 by alla              #+#    #+#             */
/*   Updated: 2022/03/06 13:19:54 by alla             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_philosophers(t_philo *head, t_data *data)
{
	t_philo	*tmp;
	t_philo	*tmp2;
	void	*return_value;

	tmp = head->next;
	tmp2 = tmp->next;
	while (head->index != data->n_of_philo)
	{
		pthread_join(head->id, &return_value);
		head = head->next;
	}
	pthread_join(head->id, return_value);
	head = head->next;
	free(data);
	while (tmp2 != head)
	{
		free(tmp);
		tmp = tmp2;
		tmp2 = tmp2->next;
	}
	free(tmp);
	if (tmp != tmp2)
		free(tmp2);
}

int	error_handler(int err_code, t_data *data)
{
	if (err_code == 1)
		printf("Malloc failed !\n");
	if (err_code == 2)
		printf("Arguments error !\n");
	if (err_code == 3)
		printf("Pthread failed !\n");
	if (data)
		free(data);
	return (err_code);
}

int	is_valid_args(int argc, char **argv, t_data *data)
{
	int			i;

	i = 1;
	if (argc != 6 && argc != 5)
		return (0);
	if (is_valid_number(argv[i]))
		data->n_of_philo = ft_atoi(argv[i++]);
	if (is_valid_number(argv[i]))
		data->time_to_die = ft_atoi(argv[i++]);
	if (is_valid_number(argv[i]))
		data->time_to_eat = ft_atoi(argv[i++]);
	if (is_valid_number(argv[i]))
		data->time_to_sleep = ft_atoi(argv[i++]);
	if (argc == 6 && is_valid_number(argv[i]))
		data->n_of_t_each_philo_must_eat = ft_atoi(argv[i++]);
	else if (argc == 5 && ++i)
		data->n_of_t_each_philo_must_eat = -(i / i);
	if (i != 6 || !data->n_of_philo || !data->time_to_die || \
	!data->n_of_t_each_philo_must_eat)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	*head;
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (error_handler(1, data));
	pthread_mutex_init(&data->print_lock, NULL);
	if (!is_valid_args(argc, argv, data))
		return (error_handler(2, data));
	if (one_philo(data))
		return (0);
	start_all_philosophers(&head, data);
	monitor(head);
	pthread_mutex_destroy(&data->print_lock);
	free_philosophers(head, data);
	return (0);
}
