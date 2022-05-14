/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:58:55 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/14 18:11:26 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_rules *rules)
{
	rules->writable = malloc(sizeof(pthread_mutex_t));
	if (!rules->writable)
		return (1);
	rules->forks = malloc(sizeof(pthread_mutex_t));
	if (!rules->forks)
		return (1);
	pthread_mutex_init(rules->writable, NULL);
	pthread_mutex_init(rules->forks, NULL);
	return (0);
}

int	init_philos(t_rules *rules)
{
	int	i;

	i = rules->num_philos;
	rules->philos = (t_philos *)malloc(sizeof(t_philos) * i);
	if (!rules->philos)
		return (1);
	while (--i >= 0)
	{
		rules->philos[i].rules = rules;
		rules->philos[i].id = i + 1;
		rules->philos[i].last_meal = 0;
		rules->philos[i].num_ate = 0;
		rules->philos[i].status = ALIVE;
		pthread_mutex_init(&(rules->philos[i].right_fork), NULL);
		rules->philos[(i + 1) % rules->num_philos].left_fork
			= &(rules->philos[i].right_fork);
		pthread_mutex_init(&(rules->philos[i].dead), NULL);
	}
	return (0);
}

int	init(t_rules *rules, char **argv)
{
	rules->num_philos = ft_atoi(argv[1]);
	rules->tt_die = ft_atoi(argv[2]);
	rules->tt_eat = ft_atoi(argv[3]);
	rules->tt_sleep = ft_atoi(argv[4]);
	rules->done_meals = 0;
	if (argv[5])
		rules->num_meals = ft_atoi(argv[5]);
	else
		rules->num_meals = -1;
	rules->status = ALIVE;
	if (init_mutex(rules))
		return (1);
	if (init_philos(rules))
		return (1);
	return (0);
}
