/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:36:12 by acosi             #+#    #+#             */
/*   Updated: 2024/02/01 12:43:36 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*	forks :
		Allows a philosopher to take forks in order to eat.
		First, another series of checks for dead philos are performed.
		The forks are effectively mutexes, so both forks will be locked here 
		and unlocked later after eating is done (or if a philo dies).
*/

int	forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	if (dead(philo->data) == 1)
		return (pthread_mutex_unlock(&philo->r_fork));
	if (dead(philo->data) == 0)
		print_msg(0, philo, "has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	if (dead(philo->data) == 1)
	{
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (0);
	}
	if (dead(philo->data) == 0)
		print_msg(0, philo, "has taken a fork");
	return (1);
}

/*	even_forks :
		Identical to the fork function, but with mutexes in the
		opposite order when the philo_id is an even number.
		This is useful to avoid potential dealock warnings.
*/

int	even_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (dead(philo->data) == 1)
		return (pthread_mutex_unlock(philo->l_fork));
	if (dead(philo->data) == 0)
		print_msg(0, philo, "has taken a fork");
	pthread_mutex_lock(&philo->r_fork);
	if (dead(philo->data) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
		return (0);
	}
	if (dead(philo->data) == 0)
		print_msg(0, philo, "has taken a fork");
	return (1);
}

/*	unlock_forks / unlock_even_forks :
		Util functions to unlock both forks in one call at the end of
		the philo thread. The order of unlock depends on the philo_id
		(even or not).
*/

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	unlock_even_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}
