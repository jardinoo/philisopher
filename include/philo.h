/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkliazni <jkliazni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:32:07 by jkliazni          #+#    #+#             */
/*   Updated: 2026/02/10 15:32:08 by jkliazni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				someone_died;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_philo			*philos;
}	t_data;

int			parse_args(int argc, char **argv, t_data *data);
int			init_data(t_data *data);
int			start_simulation(t_data *data);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
long long	get_time(void);
long long	time_diff(long long start, long long end);
void		ft_usleep(long long time);
void		print_status(t_philo *philo, char *status);
int			check_death(t_data *data);
void		set_death(t_data *data);
void		cleanup(t_data *data);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(const char *s);

#endif
