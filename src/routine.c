/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkliazni <jkliazni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:31:47 by jkliazni          #+#    #+#             */
/*   Updated: 2026/02/10 15:31:48 by jkliazni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		count;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
		return (single_philo(philo));
	if (philo->id % 2 == 0)
		usleep(100);
	while (!check_death(philo->data))
	{
		philo_eat(philo);
		pthread_mutex_lock(&philo->meal_mutex);
		count = philo->eat_count;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (philo->data->must_eat_count != -1
			&& count >= philo->data->must_eat_count)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
