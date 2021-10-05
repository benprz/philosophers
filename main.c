/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:14:38 by bperez            #+#    #+#             */
/*   Updated: 2021/10/05 12:29:22 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#include "libft.h"

// memset, printf, malloc, free, write
// usleep, gettimeofday
// pthread_create, pthread_detach, pthread_join
// pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

typedef struct	s_philosopher
{
	int						id;
	pthread_t				thread;
	int						forks;
	int						is_eating;
	int						is_sleeping;
	int						is_thinking;
	int						number_of_times_he_ate;
	struct s_philosopher	*prev;
	struct s_philosopher	*next;
}	t_philosopher;

typedef struct	s_philosophers
{
	t_philosopher	*current;
	unsigned long	starting_timestamp;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_philosophers_that_ate;
	int				did_a_philosopher_die;
}	t_philosophers;

unsigned long	get_current_timestamp(void)
{
	static struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

t_philosopher	*find_philosopher(t_philosopher *current, int id)
{
	if (current)
		while (current->id != id)
			current = current->next;
	return (current);
}

void	print_structure(t_philosophers *e)
{
	int i;
	t_philosopher	*current;

	current = find_philosopher(e->current, 1);
	printf("# t_philosophers\n\t number_of_philosophers = %d\n\t time_to_die = %d\n\t time_to_eat = %d\n\t time_to_sleep = %d\n\t number_of_times_each_philosopher_must_eat = %d\n\t current = %p\n", e->number_of_philosophers, e->time_to_die, e->time_to_eat, e->time_to_sleep, e->number_of_times_each_philosopher_must_eat, e->current);
	i = 0;
	while (i != 1)
	{
		printf("\t p%d = %p\n\t\t current->id = %d\n\t\t current->thread = %p\n\t\t current->prev = %p\n\t\t current->next = %p\n", current->id, current, current->id, current->thread, current->prev, current->next);
		current = current->next;
		if (current->id == 1)
			i = 1;
	}
}

void	print_status(t_philosophers *e, t_philosopher *philosopher, char *status)
{
	printf("%lu\t%d %s\n", get_current_timestamp() - e->starting_timestamp, philosopher->id, status);
}

void	philosopher_take_forks(t_philosophers *e, t_philosopher *philosopher)
{
	while (philosopher->forks != 2)
	{
		if (philosopher->forks != 2)
		{
			if (philosopher->prev->is_eating == 0 && philosopher->prev->forks > 0)
			{
				print_status(e, philosopher, "has taken a fork");
				philosopher->prev->forks--;
				philosopher->forks++;
			}
		}
		if (philosopher->forks != 2)
		{
			if (philosopher->next->is_eating == 0 && philosopher->next->forks > 0)
			{
				print_status(e, philosopher, "has taken a fork");
				philosopher->next->forks--;
				philosopher->forks++;
			}
		}
	}
}

void	philosopher_eat(t_philosophers *e, t_philosopher *philosopher)
{
	//philosopher_take_forks(e, philosopher);
	print_status(e, philosopher, "is eating");
	philosopher->is_eating = 1;
	usleep(e->time_to_eat);
	philosopher->is_eating = 0;
	if (++philosopher->number_of_times_he_ate == e->number_of_times_each_philosopher_must_eat)
		e->number_of_philosophers_that_ate++;
	printf("for the %dth times\n", philo->number_of_times_he_ate);
}

void	philosopher_sleep(t_philosophers *e, t_philosopher *philosopher)
{
	print_status(e, philosopher, "is sleeping");
	philosopher->is_sleeping = 1;
	usleep(e->time_to_sleep);
	philosopher->is_sleeping = 0;
	print_status(e, philosopher, "is thinking");
}

void	*thread_start(void *arg)
{
	t_philosophers	*e;
	t_philosopher	*philosopher;

	e = (t_philosophers *)arg;
	philosopher = e->current;
	while (e->did_a_philosopher_die != 1 ||\
			e->number_of_philosophers_that_ate != e->number_of_philosophers)
	{
		philosopher_eat(e, philosopher);
		philosopher_sleep(e, philosopher);
	}
	return (arg);
}

int	add_philosopher(t_philosophers *e)
{
	t_philosopher	*philosopher;

	philosopher = malloc(sizeof(t_philosopher));
	if (philosopher)
	{
		bzero(philosopher, sizeof(t_philosopher));
		if (e->current == NULL)
		{
			e->current = philosopher;
			e->current->id = 1;
			e->current->next = e->current;
		}
		else
		{
			philosopher->id = e->current->id + 1;
			philosopher->next = e->current->next;
			philosopher->prev = e->current;
			e->current->next = philosopher;
			philosopher->next->prev = philosopher;
		}
		philosopher->forks = 1;
		e->current = philosopher;
		if (!pthread_create(&philosopher->thread, NULL, thread_start, e))
			return (0);
	}
	return (-1);
}

void	free_philosophers(t_philosophers *e)
{
	int	i;
	t_philosopher	*tmp;

	e->current = find_philosopher(e->current, 1);
	i = 0;
	if (e->current)
	{
		while (i++ != e->number_of_philosophers)
		{
			tmp = e->current->next;
			free(e->current);
			e->current = tmp;
		}
	}
}

void	join_philosophers(t_philosophers *e)
{
	int	i;

	e->current = find_philosopher(e->current, 1);
	i = 0;
	while (i++ != e->number_of_philosophers)
		pthread_join(e->current->thread, NULL);
}

int	init_philosophers(t_philosophers *e)
{
	int	i;

	i = 0;
	while (i++ < e->number_of_philosophers)
	{
		if (add_philosopher(e) == -1)
			return (-1);
		usleep(100);
	}
	//print_structure(e);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philosophers	e;
	
	bzero(&e, sizeof(t_philosophers));
	if (argc == 5 || argc == 6)
	{
		e.starting_timestamp = get_current_timestamp();
		e.number_of_philosophers = atoi(argv[1]);
		e.time_to_die = atoi(argv[2]) * 1000;
		e.time_to_eat = atoi(argv[3]) * 1000;
		e.time_to_sleep = atoi(argv[4]) * 1000;
		if (argc == 6)
			e.number_of_times_each_philosopher_must_eat = atoi(argv[5]);
		if (init_philosophers(&e) == -1)
			printf("Error\n");
		join_philosophers(&e);
		free_philosophers(&e);
	}
	return (0);
}
