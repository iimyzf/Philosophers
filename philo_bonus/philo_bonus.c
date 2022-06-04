/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:24:39 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/23 16:48:06 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_them(t_simulation simulation, t_philo *philo)
{
	int	i;
	int	status;

	i = -1;
	while (++i < simulation.num_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 0)
		{
			if (i == simulation.num_of_philos - 1)
				print_message(END, philo);
			continue ;
		}
		else
		{
			i = 0;
			while (i < simulation.num_of_philos)
			{
				kill(simulation.pids[i], SIGKILL);
				i++;
			}
			exit(0);
		}
	}
}

void	forking(t_simulation simulation, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < simulation.num_of_philos)
	{
		philo->id = i;
		simulation.pids[i] = fork();
		if (simulation.pids[i] < 0)
			perror("****\n");
		else if (simulation.pids[i] == 0)
			routine(philo);
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	t_simulation	simulation;
	t_philo			*philo;

	if (ac == 5 || ac == 6)
	{
		if (data_initialization(av, &simulation))
			return (0);
		philo = philo_init(&simulation);
		create_semaphores(&simulation);
		simulation.pids = malloc(sizeof(int) * simulation.num_of_philos);
		simulation.begin = get_current_time();
		forking(simulation, philo);
		kill_them(simulation, philo);
	}
	else
		display_error();
	return (0);
}
