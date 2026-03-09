/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhoussie <nhoussie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 08:19:27 by nhoussie          #+#    #+#             */
/*   Updated: 2026/03/09 08:20:12 by nhoussie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdint.h>
#include "context.h"

#define ARGS_MIN 3
#define ARGS_MAX 4

static int	int_from_str(const char *str, int *int_ptr);

static int	is_digit(char c);

int	init_context(t_context *context, size_t args_size, char **args)
{
	if (context == NULL || args == NULL
		|| args_size < ARGS_MIN || args_size > ARGS_MAX)
		return (1);
	context->running = true;
	if (int_from_str(args[0], (int *) &context->time_to_die) != 0
		|| int_from_str(args[1], (int *) &context->time_to_eat) != 0
		|| int_from_str(args[2], (int *) &context->time_to_sleep) != 0)
		return (1);
	if (args_size == ARGS_MAX)
	{
		if (int_from_str(args[3], &context->meal_target) != 0)
			return (1);
	}
	else
		context->meal_target = -1;
	return (0);
}

int	clear_context(t_context *context)
{
	(void) context;
	return (0);
}

static int	int_from_str(const char *str, int *int_ptr)
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
	while (is_digit(*str) && nbr <= INT_MAX - !is_negative)
		nbr = nbr * 10 + (*str++ - '0');
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str != '\0' || nbr > INT_MAX - !is_negative)
		return (1);
	if (int_ptr != NULL && is_negative)
		*int_ptr = -nbr;
	else if (int_ptr != NULL)
		*int_ptr = nbr;
	return (0);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
