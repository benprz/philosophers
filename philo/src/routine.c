/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:25:46 by bperez            #+#    #+#             */
/*   Updated: 2021/10/16 13:44:33 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <pthread.h>
#include <unistd.h>

void	philosopher_eat(t_philosophers *e, t_philosopher *philosopher)
{
	if (e->death == 0)
	{
		pthread_mutex_lock(&philosopher->fork);
		print_status(e, philosopher, "has taken a fork");
		pthread_mutex_lock(&philosopher->next->fork);
		print_status(e, philosopher, "has taken a fork");
		if (e->death == 0)
		{
			print_status(e, philosopher, "is eating");
			wait_delay(e->time_to_eat);
		}
		pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(&philosopher->next->fork);
		philosopher->last_eat_timestamp = get_current_timestamp();
		if (++philosopher->number_of_times_he_ate == \
				e->number_of_times_each_philosopher_must_eat)
			e->number_of_philosophers_that_ate++;
	}
}

void	philosopher_sleep(t_philosophers *e, t_philosopher *philosopher)
{
	if (e->death == 0)
	{
		print_status(e, philosopher, "is sleeping");
		wait_delay(e->time_to_sleep);
		print_status(e, philosopher, "is thinking");
	}
}

void	*thread_start(void *arg)
{
	t_philosophers	*e;
	t_philosopher	*philosopher;

	e = (t_philosophers *)arg;
	philosopher = e->current;
	philosopher->last_eat_timestamp = get_current_timestamp();
	while (e->death == 0)
	{
		philosopher_eat(e, philosopher);
		philosopher_sleep(e, philosopher);
	}
	return (arg);
}
