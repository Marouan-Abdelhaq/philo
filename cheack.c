/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:47:17 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/02 22:09:38 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	philo_died(t_data *data, int i)
{
	if (ft_time() - data->philosophers[i].last_meal_time >= data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		pthread_mutex_lock(&data->dead_mutex);
		data->dead = 1;
		pthread_mutex_unlock(&data->dead_mutex);
		printf("%lld %d died\n", ft_time() - data->start_time,
			data->philosophers[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->meal_mutex);
		return (1);
	}
	return (0);
}

void	ft_check(t_data *data)
{
	int	i;

	while (!data->all_eat && !data->dead)
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (philo_died(data, i))
				return ;
			pthread_mutex_unlock(&data->meal_mutex);
			i++;
		}
		i = 0;
		pthread_mutex_lock(&data->meal_mutex);
		while (i < data->philo_count && data->eat_count != -1
			&& data->philosophers[i].meals_eaten >= data->eat_count)
			i++;
		if (i == data->philo_count)
			data->all_eat = 1;
		pthread_mutex_unlock(&data->meal_mutex);
		usleep(100);
	}
}
