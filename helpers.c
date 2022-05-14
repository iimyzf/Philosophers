/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yagnaou <yagnaou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 09:48:11 by yagnaou           #+#    #+#             */
/*   Updated: 2022/05/14 10:58:38 by yagnaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_current_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_sleep(t_philo *philo)
{
	usleep(10);
	print_message(SLEEP, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	print_message(int id, t_philo *philo)
{
	unsigned int	time;

	pthread_mutex_lock(philo->data->message);
	time = get_current_time() - philo->data->begin;
	if (id == FORK)
		printf("%u\t%d has taken a fork\n", time, philo->id + 1);
	else if (id == EAT)
		printf("%u\t%d is eating\n", time, philo->id + 1);
	else if (id == SLEEP)
		printf("%u\t%d is sleeping\n", time, philo->id + 1);
	else if (id == THINK)
		printf("%u\t%d is thinking\n", time, philo->id + 1);
	else if (id == DEAD)
		printf("%u\t%d is dead\n", time, philo->id + 1);
	else if (id == END)
		printf("--->>> Simulation Has Ended <<<---\n");
	else if (id != DEAD && id != END)
		pthread_mutex_unlock(philo->data->message);
}

int	ft_atoi(char *str)
{
	long long		res;
	int				sign;
	int				i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i++] - 48);
		if ((sign > 0 && res > MAX_INT) || (sign < 0 && res > MAN_INT_P1))
			return (0);
	}
	return (res * sign);
}

int	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}