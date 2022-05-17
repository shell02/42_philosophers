/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:43:58 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/17 09:22:10 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_all_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(rules->writable);
	free(rules->writable);
	pthread_mutex_destroy(rules->forks);
	free(rules->forks);
	while (i < rules->num_philos)
	{
		pthread_mutex_destroy(&rules->philos[i].dead);
		pthread_mutex_destroy(rules->philos[i++].left_fork);
	}
}

void	free_philos(t_philos *philos)
{
	if (philos)
		free(philos);
}
