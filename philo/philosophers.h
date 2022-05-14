/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shdorlin <shdorlin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 18:36:15 by shdorlin          #+#    #+#             */
/*   Updated: 2022/05/14 18:09:10 by shdorlin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>

# define DEAD 0
# define ALIVE 1
# define SLEEP 2
# define EAT 3
# define THINK 4
# define FORK 5
# define OVER 6

struct	s_philos;

typedef struct s_rules
{
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				num_philos;
	int				num_meals;
	int				done_meals;
	int				status;
	unsigned long	time_start;
	pthread_mutex_t	*writable;
	pthread_mutex_t	*forks;
	struct s_philos	*philos;
}	t_rules;

typedef struct s_philos
{
	int					id;
	int					status;
	int					num_ate;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		dead;
	unsigned long		last_meal;
	unsigned long		time_limit;
	pthread_t			philo_t;
	t_rules				*rules;
}	t_philos;

/* --- init --- */

int				init(t_rules *rules, char **argv);

/* --- routine --- */

void			ft_life_philos(t_rules *rules);
void			check_dead(t_rules *rules, t_philos *philo);
void			end_life(t_rules *rules, t_philos *philo);
int				loop_life(t_rules *rules, t_philos *philo);
void			eat(t_philos *philo);
void			ft_one_life(t_rules *rules);
void			*routine(void *v_philos);

/* --- time management --- */

unsigned long	get_time(void);
void			smart_sleep(unsigned long ms, t_rules *rules, t_philos *philo);
unsigned long	time_spent(unsigned long start, unsigned long present);

/* --- utils --- */

int				ft_isint(char *str);
int				ft_atoi(char *nptr);
int				ft_error(char *str);
int				ft_strlen(char *str);
int				check_argv(char **argv);
void			ft_log(t_rules *rules, int id, char *message);
int				get_status(t_philos *philo);

/* --- Clear --- */

void			destroy_all_mutex(t_rules *rules);
void			free_philos(t_philos *philos);

#endif
