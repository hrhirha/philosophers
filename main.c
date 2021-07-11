/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 17:17:50 by hrhirha           #+#    #+#             */
/*   Updated: 2021/07/11 16:59:01 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_shared	*data;
	t_philo		*philos;

	if (ac != 5 && ac != 6)
	{
		printf("invalid argument count\n");
		return (1);
	}
	data = malloc(sizeof(t_shared));
	if (!data)
	{
		printf("Malloc failure\n");
		return (1);
	}
	if (!ft_init_shared(data, ac, av))
		return (1);
	philos = malloc(data->num_of * sizeof(t_philo));
	if (!philos)
	{
		free(data->forks);
		free(data);
		printf("Malloc failure\n");
		return (1);
	}
	return (ft_start_sim(philos, data));
}
