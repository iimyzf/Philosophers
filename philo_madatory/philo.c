/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:46:36 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/23 15:38:06 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			simulation->max_meals = num * simulation->num_of_philos;
		}
	}
	return (0);
}

int	data_init(t_simulation *simulation, int num, int i)
{
	if (i == 1)
	{
		if (num < 0)
		{
			display_error();
			return (1);
		}
		else
		{
			simulation->num_of_philos = num;
			simulation->fork = malloc(sizeof(pthread_mutex_t) * num);
			simulation->thread = malloc(sizeof(pthread_t) * num);
		}
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
		{
			display_error();
			return (1);
		}
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

void	thread_join(t_simulation simulation, int i)
{
	i = 0;
	while (i < simulation.num_of_philos)
	{
		pthread_join(simulation.thread[i], NULL);
		usleep(100);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_simulation	simulation;
	t_philo			*philo;
	int				i;
	pthread_t		death;

	i = -1;
	if (ac == 5 || ac == 6)
	{
		if (data_initialization(av, &simulation))
			return (0);
		philo = philo_init(&simulation);
		simulation.begin = get_current_time();
		create_mutexes(&simulation);
		while (++i < simulation.num_of_philos)
		{
			pthread_create(simulation.thread + i, NULL, routine, philo + i);
			usleep(100);
		}
		pthread_create(&death, NULL, check_death, philo);
		thread_join(simulation, i);
	}
	else
		display_error();
	return (0);
}
