/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:30:10 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/15 13:10:17 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_sleep(int time, long long new_tm, t_philosopher *philo)
{
	while (ft_time() < time + new_tm)
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (philo->data->dead)
		{
			pthread_mutex_unlock(&philo->data->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
		usleep(500);
	}
}

int	check_died(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->data->all_eat)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (0);
}

int	check_time(t_data *data)
{
	if (data->time_to_eat > data->time_to_sleep)
		return (1);
	return (0);
}

int	ft_meals_onephilo(t_philosopher *philo)
{
	if (philo->data->eat_count == 0)
		return (1);
	if (philo->data->philo_count == 1)
	{
		ft_print(philo, "has taken a fork");
		ft_sleep(philo->data->time_to_die, ft_time(), philo);
		return (1);
	}
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (ft_meals_onephilo(philo) != 0)
			break ;
		ft_eat(philo);
		if (check_died(philo))
			break ;
		ft_print(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep, ft_time(), philo);
		if (check_died(philo))
			break ;
		ft_print(philo, "is thinking");
		if (philo->data->philo_count % 2 && check_time(philo->data))
			ft_sleep(philo->data->time_to_eat, ft_time(), philo);
		if (check_died(philo))
			break ;
	}
	return (NULL);
}
