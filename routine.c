/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 20:25:11 by hrhirha           #+#    #+#             */
/*   Updated: 2021/06/27 20:31:19 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	take_forks(t_philo *philo)
{
	t_shared	*data;

	data = philo->shared_data;
	pthread_mutex_lock(&data->forks[LFORK]);
	{
		pthread_mutex_lock(&data->mutex);
		printf("%s%ld %ld has taken a fork\033[0m\n", FOR_COL,
			ft_mtime() - data->cur_time, philo->idx + 1);
		pthread_mutex_unlock(&data->mutex);
	}
	pthread_mutex_lock(&data->forks[RFORK]);
	{
		pthread_mutex_lock(&data->mutex);	
		printf("%s%ld %ld has taken a fork\033[0m\n", FOR_COL,
			ft_mtime() - data->cur_time, philo->idx + 1);
		pthread_mutex_unlock(&data->mutex);
	}
}

void	eat(t_philo *philo)
{
	t_shared	*data;

	data = philo->shared_data;	
	{
		philo->start = ft_mtime();
		philo->end = philo->start + philo->shared_data->time_to_die;
		philo->meals_count++;
		philo->is_eating = 1;
		{
			pthread_mutex_lock(&data->mutex);
			printf("%s%ld %ld is eating\033[0m\n", EAT_COL,
				ft_mtime() - data->cur_time, philo->idx + 1);
			pthread_mutex_unlock(&data->mutex);
		}
		usleep(data->time_to_eat * 1e3);
		pthread_mutex_unlock(&data->forks[LFORK]);
		pthread_mutex_unlock(&data->forks[RFORK]);
		philo->is_eating = 0;
	}
}

void	psleep(t_philo *philo)
{
	t_shared	*data;

	data = philo->shared_data;
	{
		pthread_mutex_lock(&data->mutex);
		printf("%s%ld %ld is sleeping\033[0m\n", SLE_COL,
			ft_mtime() - data->cur_time, philo->idx + 1);
		pthread_mutex_unlock(&data->mutex);
	}
	usleep(philo->shared_data->time_to_sleep * 1e3);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_shared	*data;

	philo = (t_philo *)arg;
	data = philo->shared_data;		
	while (1)
	{
		take_forks(philo);
		eat(philo);
		psleep(philo);
		{
			pthread_mutex_lock(&data->mutex);
			printf("%s%ld %ld is thinking\033[0m\n", THI_COL,
				ft_mtime() - data->cur_time, philo->idx + 1);
			pthread_mutex_unlock(&data->mutex);
		}
	}
}
