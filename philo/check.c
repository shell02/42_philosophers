/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:11:44 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/16 08:36:31 by shdorlin         ###   ########.fr       */
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

int	check_over(t_rules *rules, t_philos *philo)
{
	int	i;

	if (get_status(philo) == DEAD)
		return (1);
	i = 0;
	pthread_mutex_lock(rules->forks);
	while (rules->num_meals != -1 && i < rules->num_philos
		&& philo[i].num_ate >= rules->num_meals)
		i++;
	pthread_mutex_unlock(rules->forks);
	if (i == rules->num_philos)
	{
		ft_log(rules, 0, "All meals eaten\n");
		rules->done_meals = 1;
		return (1);
	}
	usleep(7000);
	return (0);
}

int	check_philo(t_rules *r, t_philos philo)
{
	if ((philo.last_meal && (int)time_spent(philo.last_meal,
			get_time()) > r->tt_die) || (!philo.last_meal
		&& (int)time_spent(r->time_start, get_time()) > r->tt_die))
	{
		ft_log(r, philo.id, "died\n");
		pthread_mutex_lock(r->forks);
		philo.status = DEAD;
		r->status = DEAD;
		pthread_mutex_unlock(r->forks);
		return (DEAD);
	}
	return (ALIVE);
}

void	check_dead(t_rules *r, t_philos *philo)
{
	int				i;

	while (!r->done_meals)
	{
		i = -1;
		while (++i < r->num_philos)
		{
			if (check_philo(r, philo[i]) == DEAD)
				break ;
			if (get_status(&philo[i]) == DEAD)
				break ;
		}
		if (check_over(r, philo))
			break ;
	}
}
