#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_t		tid[5];
pthread_mutex_t mutex[5];

void	*inc(void *arg)
{
	int i = *((int *)arg);
	{
		pthread_mutex_lock(&mutex[i]);
		pthread_mutex_lock(&mutex[(i+1)%5]);
			printf("%d eating\n", i);
			sleep(3);
		pthread_mutex_unlock(&mutex[i]);
		pthread_mutex_unlock(&mutex[(i+1)%5]);
	}
	{
		printf("%d thinking\n", i);
		sleep(2);
	}
	return (NULL);
}

int	main()
{
	for (int i = 0; i < 5; i++)
		pthread_mutex_init(&mutex[i], NULL);
	for (int i = 0; i < 5; i++)
	{
		int *n = malloc(sizeof(int));
		*n = i;
		pthread_create(&tid[i], NULL, inc, (void *)(n));
	}
	for (int i = 0; i < 5; i++)
		pthread_join(tid[i], NULL);
}
