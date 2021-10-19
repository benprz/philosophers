/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:21:07 by bperez            #+#    #+#             */
/*   Updated: 2021/10/16 19:07:18 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	monitor_philosophers(t_philosophers *e)
{
	int				i;
	unsigned long	current_time;

	while (1)
	{
		i = 0;
		while (i++ < e->number_of_philosophers)
		{
			current_time = get_current_timestamp();
			if (current_time - e->current->last_eat_timestamp >= \
				e->time_to_die)
			{
				print_status(e, e->current, "has died");
				return (0);
			}
			e->current = e->current->next;
		}
		printf("%d %d\n", e->number_of_philosophers_that_ate, e->number_of_philosophers);
		if (e->number_of_philosophers_that_ate == e->number_of_philosophers)
			return (0);
		e->current = e->current->next;
		usleep(50);
	}
}

int	add_philosopher(t_philosophers *e)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (philosopher)
	{
		ft_bzero(philosopher, sizeof(t_philosopher));
		if (e->current == NULL)
		{
			philosopher->id = 1;
			philosopher->next = philosopher;
		}
		else
		{
			philosopher->id = e->current->id + 1;
			philosopher->next = e->current->next;
			philosopher->prev = e->current;
			e->current->next = philosopher;
			philosopher->next->prev = philosopher;
		}
		e->current = philosopher;
		if (!pthread_mutex_init(&philosopher->fork, NULL))
			return (0);
	}
	return (-1);
}

void	free_philosophers(t_philosophers *e)
{
	int				i;
	t_philosopher	*tmp;

	e->current = find_philosopher(e->current, 1);
	i = 0;
	if (e->current)
	{
		while (i++ != e->number_of_philosophers)
		{
			tmp = e->current->next;
			pthread_mutex_destroy(&e->current->fork);
			pthread_detach(e->current->thread);
			free(e->current);
			e->current = tmp;
		}
	}
}

int	init_philosophers(t_philosophers *e)
{
	int	i;

	i = 0;
	while (i++ < e->number_of_philosophers)
	{
		if (add_philosopher(e) == -1)
			return (-1);
	}
	i = 0;
	e->current = e->current->next;
	e->starting_timestamp = get_current_timestamp();
	while (i++ < e->number_of_philosophers)
	{
		if (pthread_create(&e->current->thread, NULL, thread_start, e))
			return (-1);
		usleep(50);
		e->current = e->current->next;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philosophers	e;

	ft_bzero(&e, sizeof(t_philosophers));
	if (argc == 5 || argc == 6)
	{
		if (check_arguments(argc, argv) == 1)
		{
			e.number_of_philosophers = ft_atol(argv[1]);
			e.time_to_die = ft_atol(argv[2]);
			e.time_to_eat = ft_atol(argv[3]) * 1000;
			e.time_to_sleep = ft_atol(argv[4]) * 1000;
			if (argc == 6)
				e.number_of_times_each_philosopher_must_eat = ft_atol(argv[5]);
			if (init_philosophers(&e) == 0)
			{
				monitor_philosophers(&e);
				free_philosophers(&e);
				return (0);
			}
		}
	}
	printf("Error\nusage: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	return (-1);
}
