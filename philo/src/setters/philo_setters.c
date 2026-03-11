/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:03:43 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 09:09:09 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		set_last_meal(t_philo *philo, long last_meal)
{
	if (philo == NULL)
		return (1);
	if (pthread_mutex_lock(&philo->mutex) != 0)
		return (1);
	philo->last_meal = last_meal;
	return (pthread_mutex_unlock(&philo->mutex));
}

int		set_meal_count(t_philo *philo, size_t meal_count)
{
	if (philo == NULL)
		return (1);
	if (pthread_mutex_lock(&philo->mutex) != 0)
		return (1);
	philo->meal_count = meal_count;
	return (pthread_mutex_unlock(&philo->mutex));
}
