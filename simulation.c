/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 19:11:33 by hrhirha           #+#    #+#             */
/*   Updated: 2021/07/11 16:58:26 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_init_mutex(t_shared *data)
{
	size_t	i;

	if (pthread_mutex_init(&data->mutex, NULL) != 0)
	{
		free_data(&data, "pthread_mutex_init failed");
		return (0);
	}
	data->forks = malloc(data->num_of * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		free_data(&data, "Malloc failure\n");
		return (0);
	}
	i = 0;
	while (i < data->num_of)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			free(data->forks);
			free_data(&data, "pthread_mutex_init failed\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_init_shared(t_shared *data, int ac, char **av)
{
	data->num_of = stou(av[1]);
	data->time_to_die = stou(av[2]);
	data->time_to_eat = stou(av[3]);
	data->time_to_sleep = stou(av[4]);
	data->num_of_meals = 0;
	if (ac == 6)
	{
		data->num_of_meals = stou(av[5]);
		if (data->num_of_meals == 0)
		{
			free_data(&data, "Invalid optional argument.");
			return (0);
		}
	}
	if (data->num_of == 0 || data->time_to_die < 40
		|| data->time_to_eat < 40 || data->time_to_sleep < 40)
	{
		free_data(&data, "Invalid argument.");
		return (0);
	}
	data->cur_time = ft_mtime();
	if (!ft_init_mutex(data))
		return (0);
	return (1);
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
		usleep(1e2);
	}
	pthread_create(&moni, NULL, &monitor, (void *)philos);
	pthread_join(moni, NULL);
	free(philos);
	free(data->forks);
	free(data);
	return (0);
}
