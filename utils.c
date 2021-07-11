/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrhirha <hrhirha@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 19:20:22 by hrhirha           #+#    #+#             */
/*   Updated: 2021/07/11 09:55:05 by hrhirha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	stou(char *s)
{
	int		i;
	size_t	res;

	i = 0;
	while (s[i] == ' ' || s[i] == '\f' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\t' || s[i] == '\v')
		i++;
	if (s[i] == '+')
		i++;
	res = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		res = res * 10 + (s[i] - 48);
		i++;
	}
	return (res);
}

size_t	ft_mtime(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1e3 + tp.tv_usec / 1e3);
}

int	ft_usleep(useconds_t microseconds)
{
	int		ret;
	size_t	end_sleep;

	end_sleep = ft_mtime() + microseconds / 1e3;
	ret = usleep(microseconds - MARGIN);
	while (ft_mtime() < end_sleep)
		;
	return (ret);
}

void	free_exit(t_shared **data, char *error)
{
	printf("%s\n", error);
	free(*data);
	*data = NULL;
	exit(1);
}
