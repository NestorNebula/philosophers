/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:18:24 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/13 09:40:02 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

# include "philo.h"

typedef enum e_action
{
	A_FORK,
	A_EATING,
	A_SLEEPING,
	A_THINKING,
	A_DIED,
}	t_action;

/**
 * Executes the given action for a philo.
 * Prints the action's associated message and updates
 * the given philo's structure accordingly.
 *
 * @param action An action
 * @param philo A pointer to a philo structure
 * @return 0 on success, > 0 on error
 */
int		act(t_action action, t_philo *philo);

#endif // !ACTION_H
