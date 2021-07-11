/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 11:39:09 by hrhirha           #+#    #+#             */
/*   Updated: 2021/07/11 12:14:44 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	num_of_meals_exceeded(t_philo *philo, int i)
{
	static size_t	all_done = 0;

	if (philo[i].shared_data->num_of_meals > 0
		&& philo[i].meals_count > philo[i].shared_data->num_of_meals)
	{
		all_done++;
	}
	if (all_done == philo[i].shared_data->num_of)
	{
		pthread_mutex_lock(&philo[i].shared_data->mutex);
		printf("Simulation has ended.\n");
		free(philo[i].shared_data->forks);
		free(philo[i].shared_data);
		free(philo);
		exit(1);
	}
}

void	*monitor(void *arg)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)arg;
	i = 0;
	while (1)
	{
		if (!philo[i].is_eating && ft_mtime() > philo[i].end)
		{
			pthread_mutex_lock(&philo[i].shared_data->mutex);
			printf("%s%ld %ld died\033[0m\n", DIE_COL,
				ft_mtime() - philo[i].shared_data->cur_time, philo[i].idx + 1);
			free(philo[i].shared_data->forks);
			free(philo[i].shared_data);
			free(philo);
			exit(1);
		}
		num_of_meals_exceeded(philo, i);
		i = (i + 1) % philo[i].shared_data->num_of;
		usleep(1e3);
	}
	return (NULL);
}
