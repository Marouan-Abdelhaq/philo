/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:49:46 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/14 03:52:18 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_eat(t_philosopher *philo)
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;

	if (philo->id % 2 == 0)
		usleep(1000);
	left = philo->right_fork;
	right = philo->left_fork;
	if (philo->id % 2 == 0)
	{
		left = philo->left_fork;
		right = philo->right_fork;
	}
	pthread_mutex_lock(left);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(right);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->meal_mutex);
	ft_print(philo, "is eating");
	philo->last_meal_time = ft_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_sleep(philo->data->time_to_eat, philo->last_meal_time, philo);
	pthread_mutex_unlock(left);
	pthread_mutex_unlock(right);
	usleep(1000);
}
