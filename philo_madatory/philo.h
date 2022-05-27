/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:28:17 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/20 16:50:56 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "pthread.h"
# include "sys/time.h"

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
	pthread_mutex_t	*fork;
	pthread_mutex_t	*message;
	pthread_t		*thread;
	unsigned int	begin;
	unsigned int	eating_time;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	int				current_meal;
	int				meals_count;
	int				is_dead;
}	t_simulation;

typedef struct s_philo
{
	pthread_mutex_t	*eat;
	t_simulation	*data;
	unsigned int	eating_time;
	unsigned int	next_meal;
	int				meals_count;
	int				current_meal;
	int				left_fork;
	int				right_fork;
	int				id;
	int				is_dead;
}	t_philo;

int				ft_atoi(char *str);
int				is_numeric(char *str);
int				data_initialization(char **av, t_simulation *simulation);
int				check_eat(t_philo *philo);
t_philo			*philo_init(t_simulation *simulation);
unsigned int	get_current_time(void);
void			print_message(int id, t_philo *philo);
void			ft_sleep(t_philo *philo);
void			eating(t_philo *philo);
void			display_error(void);
void			create_mutexes(t_simulation *simulation);
void			destroy_mutexes(t_simulation *simulation, t_philo *philo);
void			eating(t_philo *philo);
void			*routine(void *arg);
void			myusleep(int time);
void			*check_death(void *arg);

#endif