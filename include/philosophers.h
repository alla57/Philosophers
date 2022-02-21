#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_data
{
	int	n_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_of_t_each_philo_must_eat;
	pthread_mutex_t	init_philo_lock;

}t_data;

typedef struct s_philo
{
	pthread_t		id;
	int				index;
	int				is_eating;
	t_data			*data;
	struct s_philo	*prev;
	struct s_philo	*next;
}t_philo;

void	add_philo_to_list(t_philo *head, t_philo *new);
t_philo	*create_new_philo(int index, t_data *data);
void	create_all_philosophers(t_philo **head, t_data *data);
void	start_all_philosophers(t_philo **head, t_data *data);
int	is_valid_number(char *num);
long long	ft_atoi(const char *s);
int	is_valid_args(int argc, char **argv, t_data *data);
void	*petit_test(void *i);
int main(int argc, char **argv);


#endif