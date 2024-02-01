/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:13:51 by acosi             #+#    #+#             */
/*   Updated: 2024/02/01 18:07:55 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*	print_error :
		Prints a corresponding error message in case of invalid arguments.
*/

int	print_error(int i)
{
	if (i == 0)
		ft_putstr_fd("Error: Wrong number of arguments.", 2);
	else if (i == 1)
		ft_putstr_fd("Error: There must be at least 1 philosopher.", 2);
	else if (i == 2)
		ft_putstr_fd("Error: Invalid argument.", 2);
	else if (i == 3)
		ft_putstr_fd("No more than 200 philosophers!", 2);
	return (0);
}

/*	print_msg :
		Prints and format the output message to display in the console.
*/

void	print_msg(int death, t_philo *philo, char *msg)
{
	long long	time;
	int			id;

	id = philo->id;
	pthread_mutex_lock(&philo->data->lock_write);
	if (death == 1)
	{
		time = philo->data->dead_time - philo->data->start_time;
		id = philo->data->dead_id;
	}
	else
		time = get_time() - philo->data->start_time;
	printf("%lld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&philo->data->lock_write);
}

/*	get_time :
		Get the current time when the function is called and convert the
		result in milliseconds.
		gettimeofday() retrieves the number of seconds that passed since the Unix
		Epoch (1970) with microsecond precision, and stores it in a tv structure.
		The seconds and microseconds are converted to milliseconds, and the sum
		is casted as a long long.
*/

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec) *1000 + (long long)(tv.tv_usec) / 1000);
}

/*	ft_usleep :
		Custom usleep function for finer-grain timing.
		The original usleep() takes a numer in microseconds as parameter.
		So the initial delay of time * 900 is equivalent to 90% of the time
		to sleep, converted in milliseconds.
		A busy-wait loop is then introduced for the remaining 10%, where 
		small delays of (time / 10) are performed until the desired time
		to sleep is reached.
		This function is critical to achieve better precision when performing
		sleep operation with the philo threads and avoid lag.
*/

void	ft_usleep(long int time)
{
	time_t	start_time;

	start_time = get_time();
	usleep(time * 900);
	while ((get_time() - start_time) < time)
		usleep(time / 10);
}

/*	one_philo :
		Special case function for handling the behavior of one philosopher.
*/

int	one_philo(t_data *data)
{
	printf("%lld 1 has taken a fork\n", get_time() - data->start_time);
	ft_usleep(data->time_to_die);
	printf("%lld 1 died\n", get_time() - data->start_time);
	return (0);
}
