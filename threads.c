#include "philo.h"

int	report(t_philo *ph, int msg)
{
	if (ph->all->dead == 1 || ph->eat == 0)
		return (0);
	pthread_mutex_lock(&ph->all->print);
	if (ph->all->dead == 0)
	{
		printf("%llums %d ", (get_time() - ph->all->start), ph->pos);
		if (msg == 1)
			printf("has taken a fork\n");
		else if (msg == 2)
			printf("is eating\n");
		else if (msg == 3)
			printf("is sleeping\n");
		else if (msg == 4)
			printf("is thinking\n");
		else if (msg == 5)
			printf("is died\n");
	}
	pthread_mutex_unlock(&ph->all->print);
	return (1);
}

int	eat_and_sleep(t_philo *ph)
{
	if (ph->all->dead == 1 || ph->eat == 0)
		return (0);
	pthread_mutex_lock(ph->l_fork);
	report(ph, FORK);
	pthread_mutex_lock(ph->r_fork);
	report(ph, FORK);
	ph->tm = get_time();
	report(ph, EAT);
	ph->eat -= 1;
	my_sleep(ph->all->time_to_eat);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
	report(ph, SLEEP);
	my_sleep(ph->all->time_to_sleep);
	return (1);
}

void	*check(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;
	ph->tm = get_time();
	my_sleep(5);
	while (ph->eat)
	{
		pthread_mutex_lock(&ph->all->mutex);
		if (((int)(get_time() - ph->tm) > ph->all->time_to_die)
			&& ph->all->dead == 0)
		{
			report(ph, DIE);
			ph->all->dead = 1;
			pthread_mutex_unlock(ph->l_fork);
			pthread_mutex_unlock(&ph->all->mutex);
			break ;
		}
		pthread_mutex_unlock(&ph->all->mutex);
		my_sleep(1);
	}
	return (NULL);
}

void	*action(void *p)
{
	t_philo	*ph;

	ph = (t_philo *)p;

	if (pthread_create(&ph->check, NULL, &check, p))
		return ((void *)1);
	if ((ph->pos) % 2 == 0)
		my_sleep(ph->all->time_to_eat);
	while (ph->eat)
	{
		if (!eat_and_sleep(ph))
			break ;
		report(ph, THINK);
	}
	return (NULL);
}

int	init_threads(t_all *all)
{
	pthread_t	*thread;
	int			i;

	thread = (pthread_t *)malloc(sizeof(pthread_t) * all->num_philo);
	if (!thread)
		return (0);
	i = -1;
	while (++i < all->num_philo)
	{
		if (pthread_create(&(thread[i]), NULL, action,
			(void *)(&all->philo[i])))
			return (0);
		all->philo[i].thread = &(thread[i]);
	}
	i = -1;
	while (++i < all->num_philo)
		pthread_join(thread[i], NULL);
	free(thread);
	return (1);
}