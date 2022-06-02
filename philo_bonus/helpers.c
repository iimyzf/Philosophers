/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:55:53 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/23 16:36:09 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	myusleep(int time)
{
	unsigned int	tiimee;

	tiimee = get_current_time();
	while (get_current_time() < tiimee + time)
		usleep(400);
}

void	ft_sleep(t_philo *philo)
{
	print_message(SLEEP, philo);
	myusleep(philo->data->time_to_sleep);
}

void	print_message(int id, t_philo *philo)
{
	unsigned int	time;

	sem_wait(philo->data->message);
	time = get_current_time() - philo->data->begin;
	if (id == FORK && !philo->data->is_dead)
		printf(PINK"%u\t"RES"%d has taken a fork\n", time, philo->id + 1);
	else if (id == EAT && !philo->data->is_dead)
		printf(PINK"%u\t"RES"%d is eating\n", time, philo->id + 1);
	else if (id == SLEEP && !philo->data->is_dead)
		printf(PINK"%u\t"RES"%d is sleeping\n", time, philo->id + 1);
	else if (id == THINK && !philo->data->is_dead)
		printf(PINK"%u\t"RES"%d is thinking\n", time, philo->id + 1);
	else if (id == DEAD)
		printf(RED"%u\t%d is dead\n", time, philo->id + 1);
	else if (id == END)
		printf(BLUE BLD"\n>>> All The Philosophers Has Eaten %d Times. <<<\n\n",
			philo->data->meals_count);
	if (id != DEAD)
		sem_post(philo->data->message);
}
