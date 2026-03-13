/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:59:36 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/13 10:01:08 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include "action.h"
#include "utils.h"

static void	set_action_msg(t_action action, char **msg);

int		act(t_action action, t_philo *philo)
{
	int		rc;
	char	*msg;
	long	time;

	if (philo == NULL)
		return (1);
	msg = NULL;
	set_action_msg(action, &msg);
	if (pthread_mutex_lock(&philo->context->mutex) != 0)
		return (1);
	time = time_now();
	if (action == A_EATING)
		set_last_meal(philo, time);
	if (msg && philo->context->running)
		printf("%ld %d %s\n", (time - philo->context->start) / 1000,
			philo->number, msg);
	if (action == A_DIED)
		philo->context->running = false;
	rc = philo->context->running == false;
	pthread_mutex_unlock(&philo->context->mutex);
	return (rc);
}

static void	set_action_msg(t_action action, char **msg)
{
	if (action == A_FORK)
		*msg = "has taken a fork";
	else if (action == A_EATING)
		*msg = "is eating";
	else if (action == A_SLEEPING)
		*msg = "is sleeping";
	else if (action == A_THINKING)
		*msg = "is thinking";
	else if (action == A_DIED)
		*msg = "died";
}
