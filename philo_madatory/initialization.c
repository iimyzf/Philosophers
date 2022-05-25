/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:46:33 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/21 14:45:31 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_mutexes(t_simulation *simulation)
{
	int	i;

	i = 0;
	pthread_mutex_init(simulation->message, NULL);
	while (i < simulation->num_of_philos)
		pthread_mutex_init(simulation->fork + i++, NULL);
}

t_philo	*philo_init(t_simulation *simulation)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * simulation->num_of_philos);
	simulation->message = malloc(sizeof(pthread_mutex_t));
	while (++i < simulation->num_of_philos)
	{
		philo[i].id = i;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % simulation->num_of_philos;
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
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	print_message(FORK, philo);
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	print_message(FORK, philo);
	print_message(EAT, philo);
	if (philo->data->meals_count != -1)
		philo->data->current_meal++;
	philo->eating_time = get_current_time();
	philo->next_meal = philo->eating_time
		+ (unsigned int)philo->data->time_to_die;
	myusleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
}
