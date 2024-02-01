/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 00:50:50 by acosi             #+#    #+#             */
/*   Updated: 2024/02/01 12:36:56 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*	count_meal :
		Handles the number of meals for each philosophers and make
		them stop eating when the max number of meals is reached, thus
		ending the simulation.
		Every call of this function will increment the meal_count until 
		it reaches the max meal value that was given as argument (loop_nbr).
		When this value is reached, another counter in the data structure is 
		incremented to signal that a philosopher is done eating.
		When this counter becomes equal to the total number of philos, it means 
		they are all done eating, and the simulation stops.
*/

int	count_meal(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->loop_data);
	if (philo->data->loop_nbr == 0)
		return (pthread_mutex_unlock(&philo->data->loop_data));
	pthread_mutex_lock(&philo->loop);
	if (philo->meal_count < philo->data->loop_nbr)
		philo->meal_count++;
	if (philo->meal_count == philo->data->loop_nbr
		&& philo->data->satiated < philo->data->philo_num)
		philo->data->satiated++;
	pthread_mutex_unlock(&philo->loop);
	return (pthread_mutex_unlock(&philo->data->loop_data));
}

/*	sated :
		Checks if a particular philosopher is done eating.
*/

int	is_sated(t_philo	*philo)
{
	pthread_mutex_lock(&philo->loop);
	if (philo->data->loop_nbr != 0
		&& philo->meal_count == philo->data->loop_nbr)
	{
		pthread_mutex_unlock(&philo->loop);
		return (1);
	}
	pthread_mutex_unlock(&philo->loop);
	return (0);
}

/*	all_sated :
		Checks if all philosophers are done eating.
*/

int	all_sated(t_data	*data)
{
	pthread_mutex_lock(&data->loop_data);
	if (data->satiated == data->philo_num)
	{
		pthread_mutex_unlock(&data->loop_data);
		return (1);
	}
	pthread_mutex_unlock(&data->loop_data);
	return (0);
}
