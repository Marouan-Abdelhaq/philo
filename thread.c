/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:48:25 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/15 13:10:12 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	creat_thread(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->start_mutex);
	data->start_time = ft_time();
	while (i < data->philo_count)
	{
		pthread_create(&data->philosophers[i].thread, NULL, ft_routine,
			&data->philosophers[i]);
		i++;
	}
	pthread_mutex_unlock(&data->start_mutex);
	ft_check(data);
}
