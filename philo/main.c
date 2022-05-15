/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:05:25 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/15 21:19:43 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philos *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	ft_log(philo->rules, philo->id, "has taken a fork\n");
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(&philo->right_fork);
	ft_log(philo->rules, philo->id, "has taken a fork\n");
	ft_log(philo->rules, philo->id, "is eating\n");
	pthread_mutex_lock(philo->rules->forks);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->rules->forks);
	smart_sleep(philo->rules->tt_eat, philo->rules, philo);
	pthread_mutex_lock(philo->rules->forks);
	(philo->num_ate)++;
	pthread_mutex_unlock(philo->rules->forks);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *v_philos)
{
	t_philos	*philo;
	int			status;

	philo = (t_philos *)v_philos;
	while (get_status(philo) == ALIVE)
	{
		status = loop_life(philo->rules, philo);
		if (status == DEAD || status == OVER)
			return (NULL);
		usleep(6000);
	}
	return (NULL);
}

void	ft_life_philos(t_rules *rules)
{
	int			i;
	t_philos	*philo;

	philo = rules->philos;
	i = -1;
	rules->time_start = get_time();
	while (++i < rules->num_philos)
	{
		if (i % 2 == 0)
			if (pthread_create(&(philo[i].philo_t), NULL, routine, &philo[i])
				!= 0)
				return ;
	}
	smart_sleep(10, rules, NULL);
	i = -1;
	while (++i < rules->num_philos)
	{
		if (i % 2 == 1)
			if (pthread_create(&(philo[i].philo_t), NULL, routine, &philo[i])
				!= 0)
				return ;
	}
	check_dead(rules, philo);
	end_life(rules, philo);
}

void	end_life(t_rules *rules, t_philos *philo)
{
	int	i;

	i = 0;
	while (i < rules->num_philos)
		pthread_join(philo[i++].philo_t, NULL);
	destroy_all_mutex(rules);
	free_philos(philo);
}

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc != 5 && argc != 6)
		return (ft_error("Error: number of arguments"));
	if (check_argv(argv))
		return (ft_error("Error: arguments"));
	if (init(&rules, argv))
		return (ft_error("Error: init failed"));
	if (rules.num_philos == 1)
		ft_one_life(&rules);
	else
		ft_life_philos(&rules);
	return (0);
}
