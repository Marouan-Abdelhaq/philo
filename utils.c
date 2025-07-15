/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:50:30 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/15 09:26:25 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	conv_int(const char *str, int *i)
{
	long	result;

	result = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + (str[*i] - '0');
		(*i)++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = conv_int(str, &i);
	result *= sign;
	if (result < -2147483648 || result > 2147483647)
		return (-1);
	return ((int)result);
}

void	ft_print(t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->dead)
		printf("%lld %d %s\n", ft_time() - philo->data->start_time, philo->id,
			str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] != '+' && str[i] != '-'))
			return (1);
		i++;
	}
	return (0);
}

int	invalid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_num(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
