/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:40:26 by bperez            #+#    #+#             */
/*   Updated: 2021/10/15 18:27:59 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

int	ft_isspace(const int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_isdigit(const int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atol(const char *str)
{
	long	val;
	int		neg;

	val = 0;
	neg = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		neg = 1;
	if (neg || *str == '+')
		str++;
	while (ft_isdigit(*str))
		val = val * 10 + (*str++ - '0');
	if (neg)
		return (-val);
	return (val);
}

int	ft_is_number(char *digits)
{
	int		i;
	long	number;

	i = 0;
	while (digits[i])
	{
		if (!ft_isdigit(digits[i]))
			return (0);
		i++;
	}
	number = ft_atol(digits);
	if (number > INT_MAX)
		return (0);
	return (1);
}
