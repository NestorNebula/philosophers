/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:03:08 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 09:07:26 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		get_last_meal(t_philo *philo, long *last_meal)
{
	if (philo == NULL || last_meal == NULL)
		return (1);
	if (pthread_mutex_lock(&philo->mutex) != 0)
		return (1);
	*last_meal = philo->last_meal;
	return (pthread_mutex_unlock(&philo->mutex));
}

int		get_meal_count(t_philo *philo, size_t *meal_count)
{
	if (philo == NULL || meal_count == NULL)
		return (1);
	if (pthread_mutex_lock(&philo->mutex) != 0)
		return (1);
	*meal_count = philo->meal_count;
	return (pthread_mutex_unlock(&philo->mutex));
}
