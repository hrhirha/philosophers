/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 15:48:35 by hrhirha           #+#    #+#             */
/*   Updated: 2021/07/11 12:05:49 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define DEF		"\033[0m"
# define FOR_COL	"\033[35m"
# define EAT_COL	"\033[34m"
# define THI_COL	"\033[33m"
# define SLE_COL	"\033[32m"
# define DIE_COL	"\033[31m"

# define MARGIN		1e4

typedef struct s_shared
{
	size_t			num_of;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			num_of_meals;
	size_t			cur_time;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
}t_shared;

typedef struct s_philo
{
	size_t		idx;
	size_t		start;
	size_t		end;
	int			is_eating;
	int			is_dead;
	size_t		meals_count;
	t_shared	*shared_data;
	pthread_t	thr;
}t_philo;

/* init */

void			ft_init_mutex(t_shared *data);
void			ft_init_shared(t_shared *data, int ac, char **av);
int				ft_start_sim(t_philo *philos, t_shared *data);

/* utils */

size_t			ft_strlen(char *s);
size_t			stou(char *s);
size_t			ft_mtime(void);
int				ft_usleep(useconds_t microseconds);
void			free_exit(t_shared **data, char *error);

/* routine */

void			*routine(void *arg);
void			take_forks(t_philo *philo);

/* monitor */

void			*monitor(void *arg);

#endif
