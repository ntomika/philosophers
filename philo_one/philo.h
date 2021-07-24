#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <string.h>

# define FORK	1
# define EAT	2
# define SLEEP	3
# define THINK	4
# define DIE	5

typedef struct s_philo
{
	int				pos;
	int				eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	uint64_t		present_time;
	pthread_t		*thread;
	pthread_t		check;
	struct s_all	*all;
}				t_philo;

typedef struct s_all
{
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_eat;
	int				dead;
	uint64_t		start;
	t_philo			*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
}					t_all;

int			init_philo(t_all *all);
int			check_arguments(char **av, t_all *all);
int			init_arguments(char **av, t_all *all);
int			init_mutex(t_all *all);

int			init_threads(t_all *all);
void		*action(void *p);
int			eat_and_sleep(t_philo *ph);
void		*check_die(void *p);
int			report(t_philo *ph, int msg);

int			ft_atoi(const char *str);
uint64_t	get_time(void);
void		my_sleep(uint64_t ms);
void		ft_putstr_fd(char *s, int fd);

#endif