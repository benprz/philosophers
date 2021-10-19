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

uint64_t	get_current_timestamp(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	custom_usleep(int delay)
{
	usleep(delay);
}
/*
void	custom_usleep(int delay)
{
	uint64_t	i;
	uint64_t	j;

	i = get_current_timestamp();
	j = 0;
	while (j < (uint64_t)delay)
	{
		usleep(10);
		j = get_current_timestamp();
		j = j - i;
	}
}
*/

/*
unsigned long	get_current_timestamp(void)
{
	static struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}
*/

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

/*
void	print_structure(t_philosophers *e)
{
	int				i;
	t_philosopher	*current;

	current = find_philosopher(e->current, 1);
	printf("# t_philosophers\n\t number_of_philosophers = %d\n\t time_to_die = %lu\n\t time_to_eat = %lu\n\t time_to_sleep = %lu\n\t number_of_times_each_philosopher_must_eat = %d\n\t current = %p\n", e->number_of_philosophers, e->time_to_die, e->time_to_eat, e->time_to_sleep, e->number_of_times_each_philosopher_must_eat, e->current);
	i = 0;
	while (i != 1)
	{
		printf("\t p%d = %p\n\t\t current->id = %d\n\t\t current->thread = %p\n\t\t current->prev = %p\n\t\t current->next = %p\n", current->id, current, current->id, current->thread, current->prev, current->next);
		current = current->next;
		if (current->id == 1)
			i = 1;
	}
}
*/

void	print_status(t_philosophers *e, t_philosopher *p, char *status)
{
	printf("%llu\t%d %s\n", \
		get_current_timestamp() - e->starting_timestamp, p->id, status);
}
