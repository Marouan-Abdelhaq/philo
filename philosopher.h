/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelha <mabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:12:50 by mabdelha          #+#    #+#             */
/*   Updated: 2025/07/15 13:10:36 by mabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philosopher
{
	int					id;
	pthread_t			thread;
	int					meals_eaten;
	long long			last_meal_time;
	t_data				*data;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}						t_philosopher;

typedef struct s_data
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					eat_count;
	long long			start_time;
	int					dead;
	int					all_eat;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		start_mutex;
	t_philosopher		*philosophers;
}						t_data;

int						ft_atoi(const char *str);
long long				ft_time(void);
void					ft_print(t_philosopher *philo, char *str);
int						init_data(t_data *data, char **argv);
int						init_philo(t_data *data);
void					creat_thread(t_data *data);
void					*ft_routine(void *arg);
void					ft_eat(t_philosopher *philo);
void					ft_check(t_data *data);
int						check_died(t_philosopher *philo);
int						invalid_args(int argc, char **argv);
int						is_num(char *str);
void					ft_sleep(int time, long long new_tm,
							t_philosopher *philo);

#endif