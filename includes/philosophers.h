/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperez <bperez@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 15:27:24 by bperez            #+#    #+#             */
/*   Updated: 2021/10/11 16:29:26 by bperez           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <string.h>

typedef struct s_philosopher
{
	int						id;
	pthread_t				thread;
	pthread_mutex_t			fork;
	unsigned long			last_eat_timestamp;
	int						number_of_times_he_ate;
	struct s_philosopher	*prev;
	struct s_philosopher	*next;
}	t_philosopher;

typedef struct s_philosophers
{
	t_philosopher	*current;
	unsigned long	starting_timestamp;
	int				number_of_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_philosophers_that_ate;
	int				who_died;
}	t_philosophers;

void			ft_bzero(void *s, size_t n);
int				ft_atoi(const char *str);
unsigned long	get_current_timestamp(void);
t_philosopher	*find_philosopher(t_philosopher *current, int id);
void			print_status(t_philosophers *e, t_philosopher *p, char *s);
void			*thread_start(void *arg);

#endif
