/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 19:11:33 by hrhirha           #+#    #+#             */
/*   Updated: 2021/06/27 20:30:23 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	ft_init_mutex(t_shared *data)
{
	size_t	i;

	if (pthread_mutex_init(&data->mutex, NULL) != 0)
	{
		free(data);
		printf("pthread_mutex_init failed\n");
		exit(1);
	}
	data->forks = malloc(data->num_of * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		free(data);
		printf("Malloc failure\n");
		exit(1);
	}
	i = 0;
	while(i < data->num_of)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			free(data->forks);
			free(data);
			printf("pthread_mutex_init failed\n");
			exit(1);
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
			printf("Invalid optional argument.\n");
			free(data);
			data = NULL;
			exit(1);	
		}
	}
	if (!data->num_of || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_eat)
	{
		printf("Out of bound argument\n");
		free(data);
		data = NULL;
		exit(1);
	}
	data->cur_time = ft_mtime();
	ft_init_mutex(data);
}

void	*monitor(void *arg)
{
	t_philo		*philo;
	int			i;
	size_t		all_done;

	philo = (t_philo *)arg;
	i = 0;
	all_done = 0;
	while (1)
	{
		if (!philo[i].is_eating && ft_mtime() > philo[i].end)
		{
			pthread_mutex_lock(&philo[i].shared_data->mutex);
			printf("%s%ld %ld died\n", DIE_COL,
				ft_mtime() - philo[i].shared_data->cur_time, philo[i].idx + 1);
			exit(1);
		}
		if (philo[i].shared_data->num_of_meals > 0
			&& philo[i].meals_count > philo[i].shared_data->num_of_meals)
		{
			all_done++;
		}
		if (all_done == philo[i].shared_data->num_of)
		{
			pthread_mutex_lock(&philo[i].shared_data->mutex);
			printf("Simulation has ended.\n");
			exit(1);
		}
		i = (i + 1) % philo[i].shared_data->num_of;
		usleep(1e3);
	}
	return (NULL);
}

int	ft_start_sim(t_philo *philos, t_shared *data)
{
	size_t		i;
	pthread_t	moni;

	i = 0;
	while (i < data->num_of)
	{
		philos[i].idx = i;
		philos[i].is_eating = 0;
		philos[i].is_dead = 0;
		philos[i].meals_count = 0;
		philos[i].shared_data = data;
		philos[i].start = ft_mtime();
		philos[i].end = philos[i].start + philos[i].shared_data->time_to_die;
		pthread_create(&philos[i].thr, NULL, &routine, (void *)&philos[i]);
		i++;
		usleep(1e2);
	}
	pthread_create(&moni, NULL, &monitor, (void *)philos);
	i = 0;
	while (i < data->num_of)
	{
		pthread_join(philos[i].thr, NULL);
		i++;
	}
	return (0);
}
