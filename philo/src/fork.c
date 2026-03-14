/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:29:21 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/09 08:30:06 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

int	init_fork(t_fork *fork)
{
	if (fork == NULL)
		return (1);
	return (pthread_mutex_init(&fork->mutex, NULL));
}

int	clear_fork(t_fork *fork)
{
	return (pthread_mutex_destroy(&fork->mutex));
}
