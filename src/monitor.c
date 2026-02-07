#include "../include/philo.h"

int	check_death(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}

void	set_death(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->someone_died = 1;
	pthread_mutex_unlock(&data->death_mutex);
}

static int	check_all_eaten(t_data *data)
{
	int	i;
	int	all_done;

	if (data->must_eat_count == -1)
		return (0);
	all_done = 1;
	i = 0;
	while (i < data->philo_count)
	{
		if (data->philos[i].eat_count < data->must_eat_count)
		{
			all_done = 0;
			break ;
		}
		i++;
	}
	return (all_done);
}

static int	check_philo_death(t_data *data, int i)
{
	long long	time;

	time = get_time();
	if (time_diff(data->philos[i].last_meal, time) > data->time_to_die)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d died\n", time - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		set_death(data);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!check_death(data))
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		if (check_all_eaten(data))
		{
			set_death(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
