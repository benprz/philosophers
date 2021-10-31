/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:26:17 by bperez            #+#    #+#             */
/*   Updated: 2021/10/16 15:27:07 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	wait_delay(uint64_t delay)
{
	uint64_t	start_timestamp;
	uint64_t	current_timestamp;

	start_timestamp = get_current_timestamp();
	current_timestamp = start_timestamp;
	while (current_timestamp - start_timestamp < delay)
	{
		current_timestamp = get_current_timestamp();
		usleep(10);
	}
}

uint64_t	get_current_timestamp(void)
{
	static struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

int	check_arguments(int argc, char **argv)
{
	if (ft_is_number(argv[1]) && \
		ft_is_number(argv[2]) && \
		ft_is_number(argv[3]) && \
		ft_is_number(argv[4]))
	{
		if (argc == 5 || (argc == 6 && ft_is_number(argv[5])))
			return (1);
	}
	return (0);
}

t_philosopher	*find_philosopher(t_philosopher *current, int id)
{
	if (current)
		while (current->id != id)
			current = current->next;
	return (current);
}

void	print_status(t_philosophers *e, t_philosopher *p, char *status)
{
	printf("%llu\t%d %s\n", \
		get_current_timestamp() - e->starting_timestamp, p->id, status);
}
