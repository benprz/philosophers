/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ben <ben@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 17:36:11 by ben               #+#    #+#             */
/*   Updated: 2021/10/31 17:43:00 by ben              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdio.h>

int main(void)
{
	sem_t	*sem;

	sem = sem_open("semsem", O_CREAT);
	return (0);
}