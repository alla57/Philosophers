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
}e_actions;

//	DATA STRUCT TO STOCK NEEDED DATA
typedef struct s_data
{
	int	n_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_of_t_each_philo_must_eat;
	int	n_of_philo_have_eaten;
	int	all_philo_are_alive;
	pthread_mutex_t	init_philo_lock;
	pthread_mutex_t begin_simulation_lock;
	pthread_mutex_t eat_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	time_death_lock;

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
	e_actions		action;
	t_data			*data;
	struct s_philo	*prev;
	struct s_philo	*next;
}t_philo;

void		add_philo_to_list(t_philo *head, t_philo *new);
t_philo		*create_new_philo(int index, t_data *data);
void		create_all_philosophers(t_philo **head, t_data *data);
void		start_all_philosophers(t_philo **head, t_data *data);
int			is_valid_number(char *num);
long long	ft_atoi(const char *s); // Pourquoi long long ?????
int			is_valid_args(int argc, char **argv, t_data *data);
void		*petit_test(void *i);
int 		main(int argc, char **argv);
int			error_handler(int err_code);
void		monitor(t_philo *head);
void		do_action(t_philo	*philo, e_actions action);
void		print_action(t_philo *philo, e_actions action);
void		wait_until_they_all_eat(t_philo *head, int round);
int			all_philo_have_eaten(t_philo *philo, int round);
void		make_philos_eat(t_philo *head, int round);
void		start_countdown_of_death(t_philo *philo);
void		*check_death_philo(void *philo_to_cast);
void		reset_time_to_die(t_philo *philo);
int			is_philo_dead(t_philo *philo);
int			is_even(int nb);
void		*print_eat_thread(void *philo_to_cast);
void		*print_sleep_thread(void *philo_to_cast);
void		*print_think_thread(void *philo_to_cast);
void		*print_die_thread(void *philo_to_cast);


#endif