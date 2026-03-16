/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:25:38 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/13 16:26:37 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_last_meal(t_philo *philo, long last_meal)
{
	long	diff;
	int		rc;

	if (philo == NULL)
		return (1);
	if (pthread_mutex_lock(&philo->mutex) != 0)
		return (1);
	diff = (last_meal - philo->context->start) / 1000
		- (philo->last_meal - philo->context->start) / 1000;
	rc = diff >= philo->context->time_to_die;
	if (rc == 0)
		philo->last_meal = last_meal;
	pthread_mutex_unlock(&philo->mutex);
	return (rc);
}

int	set_running(t_context *context, bool running)
{
	if (context == NULL)
		return (1);
	if (pthread_mutex_lock(&context->mutex) != 0)
		return (1);
	context->running = running;
	return (pthread_mutex_unlock(&context->mutex));
}

int	set_start(t_context *context, long start)
{
	if (context == NULL)
		return (1);
	if (pthread_mutex_lock(&context->mutex) != 0)
		return (1);
	context->start = start;
	return (pthread_mutex_unlock(&context->mutex));
}
