/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:31:23 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 10:57:50 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "philo.h"

int	init_philo(t_philo *philo, unsigned int number, t_master *philo_master)
{
	int	rc;

	if (philo == NULL || philo_master == NULL || number == 0)
		return (1);
	philo->state = IS_THINKING;
	philo->number = number;
	philo->last_meal = philo_master->context.start;
	philo->meal_count = 0;
	philo->forks[0] = &philo_master->forks[number - 1];
	if (number == philo_master->philos_size)
		philo->forks[1] = &philo_master->forks[0];
	else
		philo->forks[1] = &philo_master->forks[number];
	philo->context = &philo_master->context;
	if (pthread_mutex_lock(&philo->context->mutex) != 0)
		return (1);
	rc = 0;
	if (pthread_mutex_init(&philo->mutex, NULL) != 0)
		rc = 1;
	else if (pthread_create(&philo->thread, NULL, philo_routine, philo) != 0)
		rc = 1;
	if (rc == 1)
		philo->context->running = 0;
	pthread_mutex_unlock(&philo->context->mutex);
	return (rc);
}

int	clear_philo(t_philo *philo)
{
	pthread_join(philo->thread, NULL);
	pthread_mutex_destroy(&philo->mutex);
	return (0);
}
