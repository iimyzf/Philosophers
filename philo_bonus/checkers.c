/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:25:52 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/23 16:31:19 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (i < philo->data->num_of_philos)
	{
		if (philo->next_meal < get_current_time())
		{
			philo->data->is_dead = 1;
			print_message(DEAD, philo);
			if (philo->data->num_of_philos == 1)
				sem_post(philo->data->fork);
			exit(1);
		}
		i++;
		if (i == philo->data->num_of_philos)
			i = 0;
		usleep(100);
		if (!check_eat(philo))
			exit(0);
	}
	return (NULL);
}

int	check_eat(t_philo *philo)
{
	if ((philo->meals_count != -1)
		&& (philo->data->current_meal >= philo->data->max_meals))
	{
		philo->data->is_dead = 1;
		return (0);
	}
	return (1);
}

void	*routine(t_philo *philo)
{
	pthread_t	death;

	philo->next_meal = get_current_time()
		+ (unsigned int)philo->data->time_to_die;
	pthread_create(&death, NULL, check_death, philo);
	while (1)
	{
		if (philo->data->is_dead)
			exit(EXIT_FAILURE);
		eating(philo);
		ft_sleep(philo);
		print_message(THINK, philo);
	}
	return (NULL);
}
