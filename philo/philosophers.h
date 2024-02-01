/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:51:59 by acosi             #+#    #+#             */
/*   Updated: 2024/02/01 17:45:46 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <time.h>
# include <stdint.h>
# include <errno.h>

/* STRUCTURES */

struct	s_data;

typedef struct s_philo
{
	pthread_t		tid;
	pthread_t		tid_death;
	int				id;
	int				meal_count;
	long long		last_meal_time;
	int				is_even;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	think_lock;
	pthread_mutex_t	loop;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	long long		dead_time;
	int				dead_id;
	long long		start_time;
	int				loop_nbr;
	int				satiated;
	pthread_mutex_t	lock_data;
	pthread_mutex_t	lock_dead;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	loop_data;
}	t_data;

/* FUNCTIONS */

// Argument checking
int			arg_check(int ac, char **av);

// Routine
void		*routine(void *data_arg);

//	Forks
int			forks(t_philo *philo);
int			even_forks(t_philo *philo);
void		unlock_forks(t_philo *philo);
void		unlock_even_forks(t_philo *philo);

//	Death
void		*check_death(void *philo_arg);
int			dead(t_data *data);

//	Meal loops
int			count_meal(t_philo	*philo);
int			is_sated(t_philo	*philo);
int			all_sated(t_data *data);

// Utils
int			print_error(int i);
void		print_msg(int death, t_philo *philo, char *msg);
long long	get_time(void);
void		ft_usleep(long int time);
int			one_philo(t_data *data);

// Libft
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_putstr_fd(char const *str, int fd);
void		ft_putchar_fd(char c, int fd);
int			ft_strlen(char *arg);

#endif