/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 17:18:26 by acosi             #+#    #+#             */
/*   Updated: 2024/02/01 18:11:04 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	isneg;
	int	i;

	num = 0;
	isneg = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isneg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * isneg);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char const *str, int fd)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != '\0')
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	write(1, "\n", 1);
}

int	ft_strlen(char *arg)
{
	int	i;

	i = 0;
	while (arg && arg[i] != '\0')
		i++;
	return (i);
}
