/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:06:55 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/20 20:04:48 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	while (i < philo->data->num_of_philos)
	{
		if (philo[i].next_meal < get_current_time())
		{
			philo->data->is_dead = 1;
			print_message(DEAD, philo);
			if (philo->data->num_of_philos == 1)
				pthread_mutex_unlock(&philo->data->fork[0]);
			break ;
		}
		i++;
		if (i == philo->data->num_of_philos)
			i = 0;
		usleep(100);
		if (!check_eat(philo))
			break ;
	}
	return (NULL);
}

int	check_eat(t_philo *philo)
{
	if ((philo->meals_count != -1)
		&& (philo->data->current_meal >= philo->data->max_meals))
	{
		philo->data->is_dead = 1;
		print_message(END, philo);
		return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = arg;
	philo->next_meal = get_current_time()
		+ (unsigned int)philo->data->time_to_die;
	while (1)
	{
		if (philo->data->is_dead)
			break ;
		eating(philo);
		ft_sleep(philo);
		print_message(THINK, philo);
	}
	return (NULL);
}
