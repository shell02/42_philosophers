/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:40:57 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/14 00:50:44 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *nptr)
{
	int	i;
	int	x;
	int	signe;

	i = 0;
	x = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			signe *= -1;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		x = x * 10 + (nptr[i] - 48);
		i++;
	}
	return (x * signe);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strcmp(char *s1, char *s2)
{
	long unsigned int	i;
	unsigned char		*s1_new;
	unsigned char		*s2_new;

	i = 0;
	s1_new = (unsigned char *)s1;
	s2_new = (unsigned char *)s2;
	while (s1_new[i] && s2_new[i] && s1_new[i] == s2_new[i])
		i++;
	return (s1_new[i] - s2_new[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_isint(char *num)
{
	int	i;
	int	len;

	i = 0;
	if (num[0] == '-' || num[0] == '+')
		i++;
	len = i;
	while (ft_isdigit(num[len]))
		len++;
	if (len < ft_strlen(&num[i]))
		return (0);
	while (num[i] == '0')
		i++;
	len = ft_strlen(&num[i]);
	if (len == 10)
	{
		if (num[0] == '-' && ft_strcmp(&num[i], "2147483648") > 0)
			return (0);
		if (num[0] != '-' && ft_strcmp(&num[i], "2147483647") > 0)
			return (0);
	}
	if (len > 10)
		return (0);
	return (1);
}
