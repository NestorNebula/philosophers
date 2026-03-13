/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 11:39:52 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/10 11:44:03 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include "utils.h"

int		int_from_str(const char *str, bool *err)
{
	uint64_t	nbr;
	bool		is_negative;

	if (str == NULL || err == NULL)
	{
		*err = true;
		return (0);
	}
	while (*str == ' ' || *str == '\t')
		str++;
	is_negative = *str == '-';
	if (*str == '-' || *str == '+')
		str++;
	if (!is_digit(*str))
		*err = true;
	nbr = 0;
	while (is_digit(*str) && nbr <= (uint64_t) INT_MAX - !is_negative)
		nbr = nbr * 10 + (*str++ - '0');
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str != '\0' || nbr > (uint64_t) INT_MAX - !is_negative)
		*err = true;
	if (is_negative)
		return (-nbr);
	return (nbr);
}

int	is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

long	time_now(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

void	ft_usleep(long l)
{
	long	start;
	long	time;
	long	target;

	if (l < 0)
		return ;
	start = time_now();
	time = start;
	target = start + l;
	usleep((target - time) * 90 / 100);
	time = time_now();
	while (time - start < l)
	{
		usleep(100);
		time = time_now();
	}
}
