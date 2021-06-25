#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct	s_data
{
	int				num_of;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				num_philo_must_eat;
	int				*idx;
	pthread_t		*tid;
	pthread_mutex_t	*forks;
}				t_data;

void	*routine(void *arg)
{
	t_data	*data;
	int		*idx;
	
	data = *((t_data **)arg);
	idx = data->idx;
	{
		pthread_mutex_lock(&data->forks[*idx]);
		pthread_mutex_lock(&data->forks[(*idx+1)%data->num_of]);
		{
			printf("%d is eating\n", *idx+1);
			usleep(data->time_to_eat);
		}
		pthread_mutex_unlock(&data->forks[*idx]);
		pthread_mutex_unlock(&data->forks[(*idx+1)%data->num_of]);
		printf("%d is thinking\n", *idx+1);
		printf("%d is sleeping\n", *idx+1);
		usleep(data->time_to_sleep);
	}
	free(idx);
	return (NULL);
}

unsigned int ft_atou(char *s)
{
	int				i;
	unsigned int	res;

	i = 0;
	if (s[i] == '-')
		return (0);
	if (s[i] == '+')
		i++;
	res = 0;
	while (s[i])
	{
		if (s[i] < '0' && s[i] > '9')
			return (0);
		res = res * 10 + (s[i] - 48);
		i++;
	}
	return (res);
}

void	ft_init(t_data *data, char **av, int opt)
{
	int	i;

	data->num_of = ft_atou(av[1]);
	data->time_to_die = ft_atou(av[2]);
	data->time_to_eat = ft_atou(av[3]);
	data->time_to_sleep = ft_atou(av[4]);
	if (opt == 6)
		data->num_philo_must_eat = ft_atou(av[5]);
	else
		data->num_philo_must_eat = -1;
	data->forks = malloc(data->num_of * sizeof(pthread_mutex_t));
	i = -1;
	while (++i < data->num_of)
		pthread_mutex_init(&data->forks[i], NULL);
}

void	ft_exit(t_data **data, char *error)
{
	int i;

	i = -1;
	free((*data)->forks);
	free((*data)->tid);
	free((*data));
	if (!*error)
		exit(0);
	else
	{
		printf("%s\n", error);
		exit(1);
	}
}

void	ft_wrong_args(t_data **data)
{
	if ((*data)->num_of == 0 || (*data)->time_to_die == 0
		|| (*data)->time_to_eat == 0 || (*data)->time_to_sleep == 0
		|| (*data)->num_philo_must_eat == 0)
		ft_exit(data, "Invalid argument.");
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	if (ac != 5 && ac != 6)
	{
		printf("Argument count Error.\n");
		exit (1);
	}
	data = malloc(sizeof(t_data));
	ft_init(data, av, ac);
	ft_wrong_args(&data);
	data->tid = malloc(data->num_of * sizeof(pthread_t));
	i = -1;
	while (++i < data->num_of)
	{
		data->idx = malloc(sizeof(int));
		*data->idx = i;
		pthread_create(&data->tid[i], NULL, &routine, (void *)&data);
		usleep(10);
	}
	i = -1;
	while (++i < data->num_of)
		pthread_join(data->tid[i], NULL);
}
