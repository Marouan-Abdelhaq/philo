/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:06:01 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/15 09:05:48 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philosopher) * data->philo_count);
	if (!data->philosophers)
	{
		free(data->forks);
		printf("Error: malloc failed\n");
		return (1);
	}
	while (i < data->philo_count)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].last_meal_time = data->start_time;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1)
			% data->philo_count];
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].data = data;
		i++;
	}
	return (0);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
}

int	init_data(t_data *data, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->eat_count = ft_atoi(argv[5]);
	else
		data->eat_count = -1;
	data->dead = 0;
	data->start_time = ft_time();
	data->all_eat = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
	{
		printf("Error: malloc failed\n");
		return (1);
	}
	init_mutex(data);
	return (0);
}
