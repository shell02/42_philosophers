/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:09:31 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/14 18:15:09 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_status(t_philos *philo)
{
	pthread_mutex_lock(philo->rules->forks);
	if (philo->rules->status == DEAD || philo->status == DEAD)
	{
		pthread_mutex_unlock(philo->rules->forks);
		return (DEAD);
	}
	else
	{
		pthread_mutex_unlock(philo->rules->forks);
		return (ALIVE);
	}
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned long	time_spent(unsigned long start, unsigned long present)
{
	return (present - start);
}

void	smart_sleep(unsigned long time, t_rules *rules, t_philos *philo)
{
	unsigned long	start;
	unsigned long	meal;

	start = get_time();
	if (philo)
		meal = philo->last_meal;
	while (1)
	{		
		if (time_spent(start, get_time()) >= time)
			break ;
		usleep(50);
		if (philo && (int)time_spent(meal, get_time()) > rules->tt_die)
			return ;
	}
}

int	loop_life(t_rules *rules, t_philos *philo)
{
	if (philo->num_ate == rules->num_meals)
		return (OVER);
	eat(philo);
	if (get_status(philo) == DEAD)
		return (DEAD);
	ft_log(rules, philo->id, "is sleeping\n");
	smart_sleep(rules->tt_sleep, rules, philo);
	if (get_status(philo) == DEAD)
		return (DEAD);
	ft_log(rules, philo->id, "is thinking\n");
	if (get_status(philo) == DEAD)
		return (DEAD);
	if ((int)time_spent(philo->last_meal, get_time()) >= rules->tt_die)
	{
		rules->status = DEAD;
		ft_log(rules, philo->id, "died\n");
		philo->status = DEAD;
		return (OVER);
	}
	return (ALIVE);
}
