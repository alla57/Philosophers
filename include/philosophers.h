/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alla <alla@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 13:11:43 by alla              #+#    #+#             */
/*   Updated: 2022/03/06 13:20:44 by alla             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

//	LIBRARIES
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

//	ANSI COLORS
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RST_CLR "\e[0m"

//	PHILO ACTIONS
typedef enum e_actions
{
	eat,
	sleeps,
	think,
	die
}t_actions;

//	DATA STRUCT TO STOCK NEEDED DATA
typedef struct s_data
{
	int				n_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_t_each_philo_must_eat;
	int				n_of_philo_have_eaten;
	int				all_philo_are_alive;
	long int		timestamp_start;
	long int		timestamp;
	pthread_mutex_t	print_lock;
}t_data;

//	PHILO STRUCT TO STOCK EACH PHILOS WITH THEIR INFOS
typedef struct s_philo
{
	pthread_t		id;
	int				index;
	int				is_eating;
	int				can_eat;
	int				is_dead;
	long int		time_to_die_start;
	t_actions		action;
	t_data			*data;
	struct s_philo	*prev;
	struct s_philo	*next;
}t_philo;

//	create_philo.c functions
void		add_philo_to_list(t_philo *head, t_philo *new);
t_philo		*create_new_philo(int index, t_data *data);
void		create_all_philosophers(t_philo **head, t_data *data);
void		start_all_philosophers(t_philo **head, t_data *data);

//	utils.c functions functions
int			is_valid_number(char *num);
int			ft_atoi(const char *s);
int			is_even(int nb);
int			is_bigger_than_intmax(char *num);

//	philos.c functions
void		*philosopher(void *i);
void		do_action(t_philo	*philo, t_actions action);
void		print_action(t_philo *philo, t_actions action);
int			one_philo(t_data *data);
void		refresh_timestamp(t_philo *philo);

//	main.c functions
int			main(int argc, char **argv);
int			is_valid_args(int argc, char **argv, t_data *data);
void		free_philosophers(t_philo *head, t_data *data);
int			error_handler(int err_code, t_data *data);

//	monitor.c functions
void		monitor(t_philo *head);
void		wait_until_they_all_eat(t_philo *head, int round);
int			all_philo_have_eaten(t_philo *philo, int round);
void		make_philos_eat(t_philo *head, int round);

//	death_handling.c functions
void		start_countdown_of_death(t_philo *philo);
void		*check_death_philo(void *philo_to_cast);
void		reset_time_to_die(t_philo *philo);
int			is_philo_dead(t_philo *philo);

#endif