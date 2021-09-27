/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:14:38 by bperez            #+#    #+#             */
/*   Updated: 2021/09/27 20:56:15 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// memset, printf, malloc, free, write
// usleep, gettimeofday
// pthread_create, pthread_detach, pthread_join
// pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

typedef struct	s_list
{
	pthread_t		*philosopher;
	int				index;
	struct s_list	*prev;
	struct s_list	*next;
}

typedef struct	s_philosophers
{
	pthread_mutex_t	mutex;
	t_list			*current;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}	t_philosophers;

void	*thread_start(void *arg)
{
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
			e->current = find_philosopher(e->number_of_philosophers - 1);
			philosopher.next = e->current.next;
			e->current.next = philosopher;
			philosopher->prev = e->current;
			philosopher.index = e->current.index + 1;
		}
		return (0);
	}
	return (-1);

void	philosophers(t_philosophers *e)
{
	add_philosopher(e);
}

int	main(int argc, char **argv)
{
	t_philosophers	e;
	
	bzero(&e, sizeof(t_philosophers));
	if (argc == 5 || argc == 6)
	{
		e.number_of_philosophers = atoi(argv[1]);
		e.time_to_die = atoi(argv[2]);
		e.time_to_eat = atoi(argv[3]);
		e.time_to_sleep = atoi(argv[4]);
		if (argc == 5)
			e.number_of_times_each_philosopher_must_eat = atoi(argv[5]);
		philosophers(&e);
	}
	return (0);
}
