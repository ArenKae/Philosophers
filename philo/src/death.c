/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:38:41 by acosi             #+#    #+#             */
/*   Updated: 2024/02/01 12:39:25 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*	check_death :
		This function is executed by a recurrent thread launched by 
		each philo. Its job is to determine if the philo that launched 
		it should live or die. To achieve that, we emulate the passing of 
		time for this philo with a usleep of the time_to_die specified as 
		argument (+ 1 to make sure we start after this value).
		The current time is then compared to the lifetime of a philosopher.
		If it is greater than this value, the philo is considered dead, and 
		the event is signaled to the data structure, storing the id and 
		time of death for later printing.
*/

void	*check_death(void *philo_arg)
{
	t_philo		*philo;
	long long	time;

	philo = (t_philo *)philo_arg;
	ft_usleep(philo->data->time_to_die + 1);
	pthread_mutex_lock(&philo->eat_lock);
	time = get_time() - philo->data->start_time;
	if (time > (philo->last_meal_time) + philo->data->time_to_die)
	{
		if (dead(philo->data) == 0)
		{
			pthread_mutex_lock(&philo->data->lock_dead);
			philo->data->dead = 1;
			philo->data->dead_time = get_time();
			philo->data->dead_id = philo->id;
			pthread_mutex_unlock(&philo->data->lock_dead);
		}
		pthread_mutex_unlock(&philo->eat_lock);
		return ((void *)1);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return ((void *)0);
}

/*	dead :
		Checks if a philosopher has died by acessing the data->dead
		value that is kept updated by the check_death thread for each philo.
		It is thus critical to protect this value with a mutex.
*/

int	dead(t_data *data)
{
	pthread_mutex_lock(&data->lock_dead);
	if (data->dead == 0)
	{
		pthread_mutex_unlock(&data->lock_dead);
		return (0);
	}
	pthread_mutex_unlock(&data->lock_dead);
	return (1);
}
