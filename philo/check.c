/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:11:44 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/14 01:48:15 by shdorlin         ###   ########.fr       */
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

	if (rules->status == DEAD)
		return (1);
	i = 0;
	while (rules->num_meals != -1 && i < rules->num_philos
		&& philo[i].num_ate >= rules->num_meals)
		i++;
	if (i == rules->num_philos)
	{
		ft_log(rules, 0, "All meals eaten\n");
		rules->done_meals = 1;
		return (1);
	}
	usleep(100);
	return (0);
}

void	check_dead(t_rules *rules, t_philos *philo)
{
	int				i;
	unsigned long	tt_die;

	tt_die = rules->tt_die;
	while (!rules->done_meals)
	{
		i = -1;
		while (++i < rules->num_philos && rules->status != DEAD)
		{
			pthread_mutex_lock(rules->forks);
			if (philo[i].status == DEAD)
				rules->status = DEAD;
			else if ((philo[i].last_meal && time_spent(philo[i].last_meal,
						get_time()) > tt_die) || (!philo[i].last_meal
					&& time_spent(rules->time_start, get_time()) > tt_die))
			{
				ft_log(rules, philo[i].id, "died\n");
				rules->status = DEAD;
			}
			pthread_mutex_unlock(rules->forks);
		}
		if (check_over(rules, philo))
			break ;
	}
	return ;
}
