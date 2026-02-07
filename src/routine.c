#include "../include/philo.h"

static void	*single_philo(t_philo *philo)
{
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
		return (single_philo(philo));
	if (philo->id % 2 == 0)
		usleep(100);
	while (!check_death(philo->data))
	{
		philo_eat(philo);
		if (philo->data->must_eat_count != -1
			&& philo->eat_count >= philo->data->must_eat_count)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
