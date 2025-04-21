/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-11 19:30:10 by mabdelha          #+#    #+#             */
/*   Updated: 2025-04-11 19:30:10 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

void	*ft_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		// if (philo->data->philo_count == 1)
		// {
		// 	ft_print(philo, "has taken a fork");
		// 	usleep(philo->data->time_to_die * 1000);
		// 	break ;
		// }
		if (check_died(philo))
			break ;
		ft_eat(philo);
		if (check_died(philo))
			break ;
		ft_print(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		if (check_died(philo))
			break ;
		ft_print(philo, "is thinking");
		if (philo->data->philo_count % 2 && philo->data->time_to_eat > philo->data->time_to_sleep)
			usleep(philo->data->time_to_eat * 1000);
	}
	return (NULL);
}
