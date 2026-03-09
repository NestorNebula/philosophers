/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:39:52 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/09 11:44:11 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "utils.h"

int	int_from_str(const char *str, int *int_ptr)
{
	uint64_t	nbr;
	bool		is_negative;

	if (str == NULL)
		return (1);
	while (*str == ' ' || *str == '\t')
		str++;
	is_negative = *str == '-';
	if (*str == '-' || *str == '+')
		str++;
	if (!is_digit(*str))
		return (1);
	nbr = 0;
	while (is_digit(*str) && nbr <= (uint64_t) INT_MAX - !is_negative)
		nbr = nbr * 10 + (*str++ - '0');
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str != '\0' || nbr > (uint64_t) INT_MAX - !is_negative)
		return (1);
	if (int_ptr != NULL && is_negative)
		*int_ptr = -nbr;
	else if (int_ptr != NULL)
		*int_ptr = nbr;
	return (0);
}

int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	time_now(long *time_ptr)
{
	long			now;
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if (time_ptr != NULL)
		*time_ptr = now;
	return (0);
}
