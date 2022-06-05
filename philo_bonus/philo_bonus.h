/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 12:56:12 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/23 16:53:59 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "semaphore.h"
# include "pthread.h"
# include "sys/time.h"
# include "sys/wait.h"
# include <signal.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DEAD 5
# define END 6

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define PINK "\033[0;35m"
# define RES "\033[0m"
# define YLW "\033[0;33m"
# define BLD "\e[1m"

# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define MAN_INT_P1 2147483648

typedef struct s_simulation
{
	sem_t			*message;
	sem_t			*fork;
	unsigned int	begin;
	unsigned int	eating_time;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				current_meal;
	int				meals_count;
	int				*pids;
	int				is_dead;
}	t_simulation;

typedef struct s_philo
{
	t_simulation	*data;
	unsigned int	eating_time;
	unsigned int	next_meal;
	int				meals_count;
	int				current_meal;
	int				id;
	int				is_dead;
}	t_philo;

int				ft_atoi(char *str);
int				is_numeric(char *str);
int				check_eat(t_philo *philo);
int				data_initialization(char **av, t_simulation *simulation);
t_philo			*philo_init(t_simulation *simulation);
unsigned int	get_current_time(void);
void			print_message(int id, t_philo *philo);
void			display_error(void);
void			*routine(t_philo *philo);
void			*check_death(void *arg);
void			create_semaphores(t_simulation *simulation);
void			eating(t_philo *philo);
void			myusleep(int time);
void			ft_sleep(t_philo *philo);
void			print_message(int id, t_philo *philo);

#endif