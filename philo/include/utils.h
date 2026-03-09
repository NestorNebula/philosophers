/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 10:49:21 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/09 11:44:09 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/**
 * Reads an integer from a string.
 *
 * @param A pointer to a string
 * @param A pointer to an integer where the integer read can be stored
 * @return 0 on success, > 0 on error
 */
int	int_from_str(const char *str, int *int_ptr);

/**
 * Checks if an integer corresponds to an hexadecimal character.
 *
 * @param c An integer
 * @return > 0 if the given integer corresponds to an hexadecimal character,
 * 0 otherwise
 */
int	is_digit(int c);

/**
 * Gets the current number of milliseconds since Epoch.
 *
 * @param time_ptr A pointer to a variable where the time can be stored
 * @return 0 on success, > 0 on error
 */
int	time_now(long *time_ptr);

#endif // !UTILS_H
