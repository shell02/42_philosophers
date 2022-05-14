/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:34:03 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/14 16:15:50 by shdorlin         ###   ########.fr       */
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
	unsigned long	time;

	time = get_time() - rules->time_start;
	pthread_mutex_lock(rules->writable);
	if (rules->status == ALIVE && !rules->done_meals)
	{
		printf("%lu ", time);
		if (id)
			printf("%d ", id);
		printf("%s", message);
	}
	pthread_mutex_unlock(rules->writable);
	return ;
}
