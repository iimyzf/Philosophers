/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_inits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:46:04 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/23 16:46:57 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	data_init2(t_simulation *simulation, int num, int i)
{
	if (i == 5)
	{
		if (num < 0)
		{
			simulation->meals_count = -1;
			simulation->current_meal = -1;
			simulation->max_meals = -1;
		}
		else
		{
			simulation->meals_count = num;
			simulation->current_meal = 0;
			simulation->max_meals = num;
		}
	}
	return (0);
}

int	data_init(t_simulation *simulation, int num, int i)
{
	if (i == 1)
	{
		if (num < 0)
			display_error();
		else
			simulation->num_of_philos = num;
	}
	else if (i == 2)
		simulation->time_to_die = num;
	else if (i == 3)
		simulation->time_to_eat = num;
	else if (i == 4)
		simulation->time_to_sleep = num;
	else
		data_init2(simulation, num, i);
	return (0);
}

int	data_initialization(char **av, t_simulation *simulation)
{
	int	i;
	int	num;

	i = 1;
	while (av[i])
	{
		num = ft_atoi(av[i]);
		if ((i == 1 && num < 0) || !is_numeric(av[i]))
			display_error();
		if (data_init(simulation, num, i))
			return (1);
		i++;
	}
	if (i == 5)
	{
		simulation->meals_count = -1;
		simulation->current_meal = -1;
		simulation->max_meals = -1;
	}
	simulation->is_dead = 0;
	return (0);
}
