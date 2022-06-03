/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:23:23 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/23 16:38:16 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_semaphores(t_simulation *simulation)
{
	sem_unlink("fork");
	simulation->fork = sem_open("fork", O_CREAT, 0777,
			simulation->num_of_philos);
	sem_unlink("message");
	simulation->message = sem_open("message", O_CREAT, 0777, 1);
}

t_philo	*philo_init(t_simulation *simulation)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * simulation->num_of_philos);
	while (++i < simulation->num_of_philos)
	{
		philo[i].id = i;
		philo[i].data = simulation;
		if (simulation->meals_count == -1)
			philo[i].meals_count = -1;
		else
			philo[i].meals_count = simulation->meals_count;
	}
	return (philo);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->data->fork);
	print_message(FORK, philo);
	sem_wait(philo->data->fork);
	print_message(FORK, philo);
	print_message(EAT, philo);
	philo->eating_time = get_current_time();
	philo->next_meal = philo->eating_time
		+ (unsigned int)philo->data->time_to_die;
	myusleep(philo->data->time_to_eat);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	if (philo->data->meals_count != -1)
		philo->data->current_meal++;
}
