/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:11:59 by acosi             #+#    #+#             */
/*   Updated: 2024/02/01 12:48:21 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*	sleep_and_think :
		When a philosopher is done eating, it should sleep and think according 
		the values that were given as parameters. This functions checks for 
		end conditions first (a death occured or all philos are satiated), and
		usleep with a corresponding message to emulate sleeping and thinking.
		Some additionnal mutexes are here as an additionnal layer of protection 
		against data races, even if this data is only read.
*/

int	sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_data);
	if (dead(philo->data) == 1 || all_sated(philo->data) == 1)
		return (pthread_mutex_unlock(&philo->data->lock_data));
	if (is_sated(philo))
		return (pthread_mutex_unlock(&philo->data->lock_data));
	if (dead(philo->data) == 0)
		print_msg(0, philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->lock_data);
	ft_usleep(philo->data->time_to_sleep);
	if (dead(philo->data) == 1)
		return (0);
	pthread_mutex_lock(&philo->think_lock);
	if (dead(philo->data) == 1)
		return (pthread_mutex_unlock(&philo->think_lock));
	if (dead(philo->data) == 0)
		print_msg(0, philo, "is thinking");
	pthread_mutex_unlock(&philo->think_lock);
	return (1);
}

/*	eat :
		Handles the meals of the philosopher.
		First we check if there is no dead and if the philos are not satiated.
		If the calling philosopher is not done eating (sated), it will try to 
		take forks and start eating. Depending on if the philo_id is even or 
		not, the forks are taken in a different order. This is useful to avoid 
		potential deadlock warnings.
		After eating and if a max number of meal was specified, the count_meal() 
		function will increment the meal counter for this philo.
*/

int	eat(t_philo	*philo)
{
	if (dead(philo->data) == 1 || all_sated(philo->data) == 1)
		return (0);
	if (is_sated(philo))
		return (0);
	if (philo->is_even == 1)
	{
		if (even_forks(philo) == 0)
			return (0);
	}
	else if (forks(philo) == 0)
		return (0);
	if (dead(philo->data) == 0 && all_sated(philo->data) == 0)
	{
		pthread_mutex_lock(&philo->eat_lock);
		print_msg(0, philo, "is eating");
		philo->last_meal_time = get_time() - philo->data->start_time;
		pthread_mutex_unlock(&philo->eat_lock);
		count_meal(philo);
		ft_usleep(philo->data->time_to_eat);
	}
	return (1);
}

/*	routine :
		The routine is executed by each philosopher's thread until an exit
		condition is met.
		First, a small lag is introduced for every even number philo, to prevent 
		them from taking all the forks at the same time when the threads start.
		Inside the infinite loop, a new thread is created to check if the philo 
		should die, and update its status if that's the case.
		If still alive, the philo will then proceed to eat and release the forks 
		when done, before sleeping and thinking.
		Finally, all the check_death threads are ended to avoid 
		leaks and data races.
*/

void	*routine(void *philo_arg)
{
	t_philo		*philo;

	philo = (t_philo *)philo_arg;
	if (philo->id % 2 == 0)
	{
		philo->is_even = 1;
		ft_usleep(philo->data->time_to_eat / 10);
	}
	while (1)
	{
		pthread_create(&philo->tid_death, NULL, &check_death, (void *)philo);
		if (eat(philo) == 0)
			break ;
		if (philo->is_even == 1)
			unlock_even_forks(philo);
		else
			unlock_forks(philo);
		if (sleep_and_think(philo) == 0)
			break ;
		pthread_detach(philo->tid_death);
	}
	pthread_join(philo->tid_death, NULL);
	return ((void *)0);
}
