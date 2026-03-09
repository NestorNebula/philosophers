/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:19:27 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/09 11:44:15 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdint.h>
#include "context.h"
#include "utils.h"

#define ARGS_MIN 3
#define ARGS_MAX 4

int	init_context(t_context *context, size_t args_size, char **args)
{
	int	rc;

	if (context == NULL || args == NULL
		|| args_size < ARGS_MIN || args_size > ARGS_MAX)
		return (1);
	context->running = true;
	context->start = time_now(&context->start);
	if (int_from_str(args[0], (int *) &context->time_to_die) != 0
		|| int_from_str(args[1], (int *) &context->time_to_eat) != 0
		|| int_from_str(args[2], (int *) &context->time_to_sleep) != 0)
		return (1);
	if (context->time_to_die <= 0 || context->time_to_eat <= 0
		|| context->time_to_sleep <= 0)
		return (1);
	if (args_size == ARGS_MAX)
	{
		if (int_from_str(args[3], &context->meal_target) != 0
			|| context->meal_target <= 0)
			return (1);
	}
	else
		context->meal_target = -1;
	rc = pthread_mutex_init(&context->mutex, NULL);
	return (rc);
}

int	clear_context(t_context *context)
{
	return (pthread_mutex_destroy(&context->mutex));
}
