/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:19:20 by acosi             #+#    #+#             */
/*   Updated: 2024/02/01 13:10:55 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*	init_thread :
		Creates the thread for each philosophers using the routine() function.
		Before exiting, the program waits for all threads to terminate with
		pthread_join(). If an error happens at some point, and error status is
		returned, ending the program.
*/

int	init_thread(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < data->philo_num)
		if (pthread_create(&data->philo[i].tid, NULL,
				&routine, &data->philo[i]))
			status = 1;
	i = -1;
	while (++i < data->philo_num)
		if (pthread_join(data->philo[i].tid, NULL))
			status = 1;
	return (status);
}

/*	init_mutex :
		Initializes all the mutexes used in the program, starting with
		thoses that are shared across the data structure, then thoses
		specific to each philosophers. In particular, the forks are created 
		here : each philo has a right fork of its own, and the left fork 
		corresponds to a pointer to the fork of the next philosopher.
*/

void	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->lock_data, NULL);
	pthread_mutex_init(&data->lock_dead, NULL);
	pthread_mutex_init(&data->lock_write, NULL);
	pthread_mutex_init(&data->loop_data, NULL);
	while (++i < data->philo_num)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		pthread_mutex_init(&data->philo[i].r_fork, NULL);
		data->philo[i].l_fork = &data->philo[(i + 1)
			% (data->philo_num)].r_fork;
		pthread_mutex_init(&data->philo[i].eat_lock, NULL);
		pthread_mutex_init(&data->philo[i].think_lock, NULL);
		pthread_mutex_init(&data->philo[i].loop, NULL);
		data->philo[i].meal_count = 0;
		data->philo[i].last_meal_time = 0;
		data->philo[i].is_even = 0;
	}
}

/*	fill_data :
		Copy the values passed as argument in the data structure 
		and initializes the other values. Also allocates memory for the
		structures holding informations for each philosophers.
*/

void	fill_data(int ac, char **av, t_data *data)
{
	data->philo_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->loop_nbr = 0;
	data->dead = 0;
	data->satiated = 0;
	if (ac == 6)
		data->loop_nbr = ft_atoi(av[5]);
	data->philo = malloc(sizeof(t_philo) * (data->philo_num));
	if (!data->philo)
		return ;
	data->start_time = get_time();
	init_mutex(data);
}

/*
	The program begins by checking the validity of the arguments. If there are 
	no errors, the arguments are stored in the data structure, where the philo
	substructures and the mutexes are also initialized.
	If there is only one philosopher, it is handled as a special case.
	Else, a thread is created for each philosophers and the program waits for 
	each one to terminate before exiting.
	If a 5th argument was entered (number of meals) and all philosophers are
	satiated, the program stops there. If not, then it means one philosophers 
	died and its ID is printed along with a message.
*/

int	main(int ac, char **av)
{
	t_data	data;

	if (!arg_check(ac, av))
		return (1);
	fill_data(ac, av, &data);
	if (data.philo_num == 1)
	{
		free(data.philo);
		return (one_philo(&data));
	}
	if (init_thread(&data))
		return (1);
	if (data.satiated == data.philo_num)
	{
		free(data.philo);
		return (0);
	}
	else if (data.dead == 1)
		print_msg(1, data.philo, "died");
	free(data.philo);
	return (0);
}
