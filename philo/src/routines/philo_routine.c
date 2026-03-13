/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 08:42:03 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 13:44:24 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"
#include "utils.h"

static void	wait_start(t_philo *philo);

static int	philo_eat(t_philo *philo);

static int	grab_forks(t_philo *philo);

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo == NULL)
		return (NULL);
	wait_start(philo);
	while (philo_eat(philo) == 0)
	{
		ft_usleep(philo->context->time_to_sleep * 1000);
		if (print_action(A_THINKING, philo) != 0)
			break ;
		ft_usleep(1000);
	}
	return (NULL);
}

static void	wait_start(t_philo *philo)
{
	long	time;
	long	start;

	time = time_now();
	get_start(philo->context, &start);
	while (time < start)
	{
		ft_usleep(500);
		time = time_now();
		get_start(philo->context, &start);
	}
	set_last_meal(philo, start);
	print_action(A_THINKING, philo);
	if ((philo->number % 2) == 0)
	{
		ft_usleep(philo->context->time_to_eat * 1000);
	}
}

static int	philo_eat(t_philo *philo)
{
	int	rc;

	rc = 0;
	if (grab_forks(philo) != 0)
		return (1);
	increase_meal_count(philo);
	if (print_action(A_EATING, philo) != 0)
		rc = 1;
	ft_usleep(philo->context->time_to_eat * 1000);
	if (print_action(A_SLEEPING, philo) != 0)
		rc = 1;
	pthread_mutex_unlock(&philo->forks[0]->mutex);
	pthread_mutex_unlock(&philo->forks[1]->mutex);
	return (rc);
}

static int	grab_forks(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->forks[0]->mutex) != 0)
		return (1);
	if (print_action(A_FORK, philo) != 0
		|| &philo->forks[1]->mutex == &philo->forks[0]->mutex 
		|| pthread_mutex_lock(&philo->forks[1]->mutex) != 0)
	{
		pthread_mutex_unlock(&philo->forks[0]->mutex);
		return (1);
	}
	print_action(A_FORK, philo);
	return (0);
}
