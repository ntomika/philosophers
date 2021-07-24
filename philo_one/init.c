#include "philo.h"

int	check_arguments(char **av, t_all *all)
{
	if (all->num_philo <= 0)
		ft_putstr_fd("Bad number of philosophers.\n", 2);
	else if (av[5] && all->num_eat < 1)
		ft_putstr_fd("Nobody eats. Enter a number greater than 0.\n", 2);
	else if (all->num_philo > 200)
		ft_putstr_fd("Enter less than 200 philosophers.\n", 2);
	else if (all->time_to_die < 60 || all->time_to_eat < 60
		|| all->time_to_sleep < 60)
		ft_putstr_fd("time_to_die, time_to_eat or time_to_sleep less than 60 ms.\n", 2);
	else
		return (1);
	return (0);
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
		all->philo[i].l_fork = &(all->forks[i]);
		all->philo[i].eat = all->num_eat;
		if (all->philo[i].pos == all->num_philo)
			all->philo[i].r_fork = &(all->forks[0]);
		else
			all->philo[i].r_fork = &(all->forks[i + 1]);
		all->philo[i].all = all;
	}
	return (1);
}

int	init_mutex(t_all *all)
{
	int	i;

	all->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * all->num_philo);
	if (!all->forks)
		return (0);
	pthread_mutex_init(&all->mutex, NULL);
	pthread_mutex_init(&all->print, NULL);
	i = -1;
	while (++i < all->num_philo)
	{
		if (pthread_mutex_init(&all->forks[i], NULL))
			return (0);
	}
	return (1);
}

int	init_arguments(char **av, t_all *all)
{
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
	if (!init_mutex(all))
		return (0);
	if (!init_philo(all))
		return (0);
	all->start = get_time();
	return (1);
}
