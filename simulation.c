/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 19:11:33 by hrhirha           #+#    #+#             */
/*   Updated: 2021/07/11 12:13:56 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_init_mutex(t_shared *data)
{
	size_t	i;

	if (pthread_mutex_init(&data->mutex, NULL) != 0)
	{
		free_exit(&data, "pthread_mutex_init failed");
	}
	data->forks = malloc(data->num_of * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		free_exit(&data, "Malloc failure\n");
	}
	i = 0;
	while (i < data->num_of)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			free(data->forks);
			free_exit(&data, "pthread_mutex_init failed\n");
		}
		i++;
	}
}

void	ft_init_shared(t_shared *data, int ac, char **av)
{
	data->num_of = stou(av[1]);
	data->time_to_die = stou(av[2]);
	data->time_to_eat = stou(av[3]);
	data->time_to_sleep = stou(av[4]);
	data->num_of_meals = 0;
	if (ac == 6)
	{
		data->num_of_meals = stou(av[5]);
		if (data->num_of_meals <= 0)
		{
			free_exit(&data, "Invalid optional argument.\n");
		}
	}
	if (!data->num_of || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_eat)
	{
		free_exit(&data, "Out of bound argument\n");
	}
	data->cur_time = ft_mtime();
	ft_init_mutex(data);
}

void	ft_init_philo(t_philo *philos, int i, t_shared *data)
{
	philos[i].idx = i;
	philos[i].is_eating = 0;
	philos[i].is_dead = 0;
	philos[i].meals_count = 0;
	philos[i].shared_data = data;
	philos[i].start = ft_mtime();
	philos[i].end = philos[i].start + philos[i].shared_data->time_to_die;
}

int	ft_start_sim(t_philo *philos, t_shared *data)
{
	size_t		i;
	pthread_t	moni;

	i = 0;
	while (i < data->num_of)
	{
		ft_init_philo(philos, i, data);
		pthread_create(&philos[i].thr, NULL, &routine, (void *)&philos[i]);
		i++;
		usleep(1e3);
	}
	pthread_create(&moni, NULL, &monitor, (void *)philos);
	i = 0;
	while (i < data->num_of)
	{
		pthread_join(philos[i].thr, NULL);
		i++;
	}
	free(data->forks);
	free(data);
	free(philos);
	return (0);
}
