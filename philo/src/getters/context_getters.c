/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:30:51 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 09:32:31 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"

int	get_running(t_context *context, bool *running)
{
	if (context == NULL || running == NULL)
		return (1);
	if (pthread_mutex_lock(&context->mutex) != 0)
		return (1);
	*running = context->running;
	return (pthread_mutex_unlock(&context->mutex));
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
