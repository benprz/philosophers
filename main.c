/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:14:38 by bperez            #+#    #+#             */
/*   Updated: 2021/09/28 19:09:41 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// memset, printf, malloc, free, write
// usleep, gettimeofday
// pthread_create, pthread_detach, pthread_join
// pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

typedef struct	s_list
{
	int				index;
	pthread_t		*philosopher;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct	s_philosophers
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	*mutex;
	t_list			*current;
}	t_philosophers;

t_list	*find_philosopher(t_list *current, int index)
{
	while (current->index != index)
		current = current->next;
	return (current);
}

void	print_structure(t_philosophers *e)
{
	int i;
	t_list	*current;

	current = find_philosopher(e->current, 0);
	printf("# t_philosophers\n\t number_of_philosophers = %d\n\t time_to_die = %d\n\t time_to_eat = %d\n\t time_to_sleep = %d\n\t number_of_times_each_philosopher_must_eat = %d\n\t mutex = %p\n\t current = %p\n", e->number_of_philosophers, e->time_to_die, e->time_to_eat, e->time_to_sleep, e->number_of_times_each_philosopher_must_eat, e->mutex, e->current);
	i = 0;
	while (i++ != e->number_of_philosophers)
	{
		printf("\t p%d = %p\n\t\t current->index = %d\n\t\t current->philosopher = %p\n\t\t current->prev = %p\n\t\t current->next = %p\n", current->index, current, current->index, current->philosopher, current->prev, current->next);
		current = current->next;
	}
}

void	*thread_start(void *arg)
{
	(void)arg;
	return (arg);
}

int	add_philosopher(t_philosophers *e)
{
	t_list	*philosopher;

	philosopher = malloc(sizeof(t_list));
	if (philosopher)
	{
		bzero(philosopher, sizeof(t_list));
		if (e->current == NULL)
			e->current = philosopher;
		else
		{
			e->current = find_philosopher(e->current, e->number_of_philosophers - 1);
			philosopher->next = e->current->next;
			e->current->next = philosopher;
			philosopher->prev = e->current;
			philosopher->index = e->current->index + 1;
		}
		return (0);
	}
	return (-1);
}

void	free_philosophers(t_philosophers *e)
{
	int	i;
	t_list	*tmp;

	e->current = find_philosopher(e->current, 0);
	i = 0;
	while (i++ != e->number_of_philosophers)
	{
		tmp = e->current->next;
		free(e->current);
		e->current = tmp;
	}
}

void	philosophers(t_philosophers *e)
{
	if (!add_philosopher(e))
	{
		print_structure(e);
		free_philosophers(e);
	}
}

int	main(int argc, char **argv)
{
	t_philosophers	e;
	
	bzero(&e, sizeof(t_philosophers));
	if (argc == 2 || argc == 6)
	{
		e.number_of_philosophers = atoi(argv[1]);
		/*
		e.time_to_die = atoi(argv[2]);
		e.time_to_eat = atoi(argv[3]);
		e.time_to_sleep = atoi(argv[4]);
		if (argc == 5)
			e.number_of_times_each_philosopher_must_eat = atoi(argv[5]);
		*/
		philosophers(&e);
	}
	return (0);
}
