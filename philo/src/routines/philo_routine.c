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

static int	grab_forks(t_philo *philo, t_fork *first_fork, t_fork *second_fork);

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		rc;
	bool	running;

	philo = arg;
	if (philo == NULL)
		return (NULL);
	wait_start(philo);
	rc = get_running(philo->context, &running);
	while (rc == 0 && running)
	{
		if (philo_eat(philo) != 0)
		{
			rc = 1;
			break ;
		}
		print_action(A_SLEEPING, time_now(), philo);
		ft_usleep(philo->context->time_to_sleep * 1000);
		print_action(A_THINKING, time_now(), philo);
		ft_usleep(1000);
		rc = get_running(philo->context, &running);
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
}

static int	philo_eat(t_philo *philo)
{
	t_fork	*first_fork;
	t_fork	*second_fork;
	long	time;
	size_t	meal_count;

	first_fork = philo->forks[0];
	second_fork = philo->forks[1];
	if ((philo->number % 2) == 0)
	{
		first_fork = philo->forks[1];
		second_fork = philo->forks[0];
	}
	if (grab_forks(philo, first_fork, second_fork) != 0)
		return (1);
	time = time_now();
	set_last_meal(philo, time);
	print_action(A_EATING, time, philo);
	ft_usleep(philo->context->time_to_eat * 1000);
	get_meal_count(philo, &meal_count);
	set_meal_count(philo, meal_count + 1);
	pthread_mutex_unlock(&first_fork->mutex);
	pthread_mutex_unlock(&second_fork->mutex);
	return (0);
}

static int	grab_forks(t_philo *philo, t_fork *first_fork, t_fork *second_fork)
{
	long	time;

	if (pthread_mutex_lock(&first_fork->mutex) != 0)
		return (1);
	time = time_now();
	print_action(A_FORK, time, philo);
	if (second_fork == first_fork
		|| pthread_mutex_lock(&second_fork->mutex) != 0)
	{
		pthread_mutex_unlock(&first_fork->mutex);
		return (1);
	}
	time = time_now();
	print_action(A_FORK, time, philo);
	return (0);
}
