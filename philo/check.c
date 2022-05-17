/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:11:44 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/17 09:31:06 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_argv(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0 || ft_isint(argv[i++]) == 0)
			return (1);
	}
	return (0);
}

int	check_philo(t_rules *r, t_philos philo)
{
	if ((philo.last_meal && (int)time_spent(philo.last_meal,
				get_time()) > r->tt_die) || (!philo.last_meal
			&& (int)time_spent(r->time_start, get_time()) > r->tt_die))
	{
		r->status = DEAD;
		pthread_mutex_unlock(r->forks);
		pthread_mutex_lock(&philo.dead);
		ft_log(r, philo.id, "died\n");
		philo.status = DEAD;
		pthread_mutex_unlock(&philo.dead);
		return (DEAD);
	}
	return (ALIVE);
}

void	check_dead(t_rules *r, t_philos *philo)
{
	int	i;
	int	count;

	while (1)
	{
		i = -1;
		count = 0;
		while (++i < r->num_philos)
		{
			pthread_mutex_lock(r->forks);
			if (philo[i].num_ate == r->num_meals)
				count++;
			if (count == r->num_philos)
			{
				if (check_philo(r, philo[i]) == DEAD)
					return ;
				pthread_mutex_unlock(r->forks);
				return ;
			}
			if (check_philo(r, philo[i]) == DEAD)
				return ;
			pthread_mutex_unlock(r->forks);
		}
		usleep(6000);
	}
}
