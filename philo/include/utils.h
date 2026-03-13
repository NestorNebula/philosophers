/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:49:21 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 11:30:23 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

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
 * Reads an integer from a string.
 *
 * @param str A pointer to a string
 * @param err A pointer to a boolean that will be set to true
 * if an error occurs
 * @return The integer read on success, an undefined integer on error
 */
int		int_from_str(const char *str, bool *err);

/**
 * Checks if an integer corresponds to an hexadecimal character.
 *
 * @param c An integer
 * @return > 0 if the given integer corresponds to an hexadecimal character,
 * 0 otherwise
 */
int		is_digit(int c);

/**
 * Gets the current number of milliseconds since Epoch.
 *
 * @return The number of milliseconds since Epoch on success, -1 on error
 */
long	time_now(void);

/**
 * Sleeps for a minimum number of microseconds.
 *
 * @param l The minimum number of microseconds to sleep
 * @return 0 on success, -1 on error
 */
int		ft_usleep(long l);

/**
 * Prints an action executed by a philo.
 *
 * @param action An action
 * @param time The time to print for the action
 * @param philo A pointer to a philo structure
 * @return 0 on success, > 0 on error
 */
int		print_action(t_action action, long time, t_philo *philo);

#endif // !UTILS_H
