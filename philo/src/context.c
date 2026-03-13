/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:19:27 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 13:35:30 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "context.h"
#include "utils.h"

#define ARGS_MIN 3
#define ARGS_MAX 4
#define ERR_MSG "Invalid arguments\n"
#define ERR_MSG_LEN 18

static int	init_from_args(t_context *context, size_t args_size, char **args);

int	init_context(t_context *context, size_t args_size, char **args)
{
	if (context == NULL || args == NULL
		|| args_size < ARGS_MIN || args_size > ARGS_MAX)
		return (1);
	memset(context, 0, sizeof(t_context));
	if (init_from_args(context, args_size, args) != 0)
	{
		write(STDERR_FILENO, ERR_MSG, ERR_MSG_LEN);
		return (1);
	}
	context->running = true;
	context->start = time_now() + 100000000;
	return (pthread_mutex_init(&context->mutex, NULL));
}

int	get_start(t_context *context, long *start)
{
	if (context == NULL || start == NULL)
		return (1);
	if (pthread_mutex_lock(&context->mutex) != 0)
		return (1);
	*start = context->start;
	return (pthread_mutex_unlock(&context->mutex));
}

int	clear_context(t_context *context)
{
	return (pthread_mutex_destroy(&context->mutex));
}

static int	init_from_args(t_context *context, size_t args_size, char **args)
{
	bool	err;
	
	err = false;
	context->time_to_die = int_from_str(args[0], &err);
	context->time_to_eat = int_from_str(args[1], &err);
	context->time_to_sleep = int_from_str(args[2], &err);
	if (err || context->time_to_die <= 0 || context->time_to_eat <= 0
		|| context->time_to_sleep <= 0)
		return (1);
	if (args_size == ARGS_MAX)
	{
		context->meal_target = int_from_str(args[3], &err);
		if (err || context->meal_target <= 0)
			return (1);
	}
	else
		context->meal_target = -1;
	return (0);
}
