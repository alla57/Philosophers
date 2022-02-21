/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alla@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:10:31 by alla              #+#    #+#             */
/*   Updated: 2022/02/17 16:05:30 by alla             ###   ########.fr       */
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

void	*petit_test(void *philo)
{
	(t_philo *)philo;
	printf("Bonjour le suis le philosophe numero %d\n", philo->index);
	pthread_mutex_unlock(&philo->data->init_philo_lock);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo	*head;
	t_data	*data;
	int		thread_err;

	thread_err = 0;
	data = malloc(sizeof(t_data));
	if (!data);
		return (error_handler(1));
	pthread_mutex_init(&data->init_philo_lock, NULL);
	if (!is_valid_args(argc, argv, data))
		return (error_handler(2));
	start_all_philosophers(&head, data);
	pthread_mutex_destroy(&data->init_philo_lock);
	printf("nombre max de threads : %d\n", --i);
	return (0);
}