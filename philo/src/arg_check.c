/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:10:39 by acosi             #+#    #+#             */
/*   Updated: 2024/02/01 18:13:42 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

/*	is_nbr :
		Checks if the arguments are only numbers.
*/

int	is_nbr(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (0);
	return (1);
}

/*	check_arg_size :
		Checks if the arguments are too big to prevent a crash or overflow.
*/

int	check_arg_size(int ac, char **av)
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_nbr;

	philo_num = ft_atoi(av[1]);
	time_to_die = ft_atoi(av[2]);
	time_to_eat = ft_atoi(av[3]);
	time_to_sleep = ft_atoi(av[4]);
	meal_nbr = 0;
	if (ac == 6)
		meal_nbr = ft_atoi(av[5]);
	if (ft_strlen(av[1]) > 10 || ft_strlen(av[2]) > 10 || ft_strlen(av[3]) > 10
		|| ft_strlen(av[4]) > 10 || ft_strlen(av[5]) > 10)
		return (0);
	if ((ft_strlen(av[1]) == 10 && philo_num < 0) || (ft_strlen(av[2])
			&& time_to_die < 0) || (ft_strlen(av[3]) && time_to_eat < 0)
		|| (ft_strlen(av[4]) && time_to_sleep < 0)
		|| (ft_strlen(av[5]) && meal_nbr < 0))
		return (0);
	return (1);
}

/*	arg_check :
		Checks the validity of the program's argument.
		There should be 5 or 6 numeric arguments, none of which should be 
		less or equal than 0. No more than 200 philos should be tested, and the
		arguments have a max size of 10 digits to prevent INT_MAX overflows.
*/

int	arg_check(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (print_error(0));
	while (++i < 6 && av[i])
		if (!is_nbr(av[i]))
			return (print_error(2));
	if (ft_atoi(av[1]) < 1 && ft_strlen(av[1]) < 10)
		return (print_error(1));
	else if (ft_atoi(av[1]) < 1 && ft_strlen(av[1]) >= 10)
		return (print_error(3));
	if (ft_atoi(av[1]) > 200)
		return (print_error(3));
	if (ft_atoi(av[2]) == 0 || ft_atoi(av[3]) == 0 || ft_atoi(av[4]) == 0)
		return (print_error(2));
	if (check_arg_size(ac, av) == 0)
		return (print_error(2));
	if (av[5] && ft_atoi(av[5]) == 0)
		return (print_error(2));
	return (1);
}
