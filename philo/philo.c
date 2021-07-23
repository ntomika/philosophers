#include "philo.h"

void	free_all(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->num_philo - 1)
		pthread_mutex_destroy(&all->forks[i]);
	pthread_mutex_destroy(&all->print);
	pthread_mutex_destroy(&all->mutex);
	if (all->forks)
		free(all->forks);
	if (all->philo)
		free(all->philo);
}

int	main(int ac, char **av)
{
	t_all	all;

	if (ac >= 5 && ac <= 6)
	{
		if (init_arguments(av, &all))
		{
			if (!init_threads(&all))
				return (0);
			free_all(&all);
		}
	}
	else
		printf("Wrong number of arguments. Try again.\n");
	return (0);
}
