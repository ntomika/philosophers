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

int	init_philo(t_all *all)
{
	int	i;

	i = -1;
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->num_philo);
	if (!all->philo)
		return (0);
	while (++i <= all->num_philo - 1)
	{
		all->philo[i].pos = i + 1;
		printf("==>pos_philo = %d<==\n", i + 1);
		all->philo[i].l_fork = &(all->forks[i]);
		printf("==>philo %d -- left_fork = %d<==\n", all->philo[i].pos, i);
		all->philo[i].eat = all->num_eat;
		if (all->philo[i].pos == all->num_philo)
		{
			all->philo[i].r_fork = &(all->forks[0]);
			printf("==>philo %d -- right_fork = %d<==\n", all->philo[i].pos, 0);
		}
		else
		{
			all->philo[i].r_fork = &(all->forks[i + 1]);
			printf("==>philo %d -- right_fork = %d<==\n", all->philo[i].pos, i + 1);
		}
		all->philo[i].all = all;
	}
	return (1);
}

int	check_arguments(char **av, t_all *all)
{
	if (all->num_philo <= 0)
		printf("Bad number of philosophers.\n");
	else if (av[5] && all->num_eat < 1)
		printf("Bad number of times each philosopher must eat.\n");
	else
		return (1);
	return (0);
}

int	init_arguments(char **av, t_all *all)
{
	int	i;

	all->num_philo = ft_atoi(av[1]);
	all->time_to_die = ft_atoi(av[2]);
	all->time_to_eat = ft_atoi(av[3]);
	all->time_to_sleep = ft_atoi(av[4]);
	all->num_eat = -1;
	if (av[5])
		all->num_eat = ft_atoi(av[5]);
	all->dead = 0;
	if (!check_arguments(av, all))
		return (0);
	all->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * all->num_philo);
	pthread_mutex_init(&all->mutex, NULL);
	pthread_mutex_init(&all->print, NULL);
	i = -1;
	while (++i < all->num_philo)
	{
		if (pthread_mutex_init(&all->forks[i], NULL))
			return (0);
	}
	if (!init_philo(all))
		return (0);
	all->start = get_time();
	return (1);
}

int	main(int ac, char **av)
{
	t_all	all;
	int		i;
	
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
