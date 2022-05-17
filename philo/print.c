/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:34:03 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/17 09:42:14 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (1);
}

void	ft_log(t_rules *rules, int id, char *message)
{
	pthread_mutex_lock(rules->writable);
	pthread_mutex_lock(rules->forks);
	if (ft_strcmp(message, "died\n") && rules->status == DEAD)
	{
		pthread_mutex_unlock(rules->writable);
		pthread_mutex_unlock(rules->forks);
		return ;
	}
	pthread_mutex_unlock(rules->forks);
	printf("%lu ", get_time() - rules->time_start);
	if (id)
		printf("%d ", id);
	printf("%s", message);
	pthread_mutex_unlock(rules->writable);
	if (ft_strcmp(message, "died\n") == 0
		|| ft_strcmp(message, "All meals eaten\n") == 0)
		usleep(100000);
	return ;
}
