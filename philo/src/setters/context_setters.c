/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:32:39 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 09:33:48 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

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
