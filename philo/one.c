/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 01:53:41 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/14 16:08:52 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_one_life(t_rules *rules)
{
	rules->time_start = get_time();
	ft_log(rules, 1, "has taken a fork\n");
	while ((int)time_spent(rules->time_start, get_time()) < rules->tt_die)
		usleep(1000);
	ft_log(rules, 1, "died\n");
	destroy_all_mutex(rules);
	free(rules->philos);
	return ;
}
