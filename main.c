/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:03:56 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/15 11:52:26 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	args_sign(int argc, char **argv)
{
	int	i;

	(void)argc;
	i = 1;
	while (i < 5)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	free(data->forks);
	free(data->philosophers);
}

void	ft_error(int n)
{
	if (n == 1)
		printf("Erreur : nombre d'arguments incorrect.\n");
	else if (n == 2)
		printf("Détection des valeurs non entières.\n");
	else if (n == 3)
		printf("Détection des valeurs incorrect.\n");
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		ft_error(1);
		return (1);
	}
	if (invalid_args(argc, argv) != 0)
	{
		ft_error(2);
		return (1);
	}
	if (args_sign(argc, argv) != 0)
	{
		ft_error(3);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) != 0)
		return (1);
	if (!init_data(&data, argv))
	{
		if (!init_philo(&data))
		{
			creat_thread(&data);
			ft_clean(&data);
		}
		else
			return (1);
	}
	else
		return (1);
	return (0);
}
