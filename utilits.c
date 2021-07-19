#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned long	r;
	int				z;

	r = 0;
	z = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			z = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	return (r * z);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / (uint64_t)1000));
}

void	my_sleep(uint64_t ms)
{
	uint64_t	i;

	i = get_time();
	while (get_time() - i < ms)
		usleep(500);
}
