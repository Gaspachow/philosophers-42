/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:30:58 by gsmets            #+#    #+#             */
/*   Updated: 2021/02/15 14:39:25 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct 		s_args t_args;

typedef	struct		s_philosopher
{
	int				id;
	int				x_ate;
	int				left_fork_id;
	int				right_fork_id;
	long long		t_last_meal;
	t_args			*rules;
	pthread_t		thread_id;
}					t_philosopher;

typedef struct		s_args
{
	int				nb_philo;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	pthread_mutex_t	forks[250];
	pthread_mutex_t writing;
	t_philosopher	philosophers[250];
}					t_args;

/*
** ----- error_manager.c -----
*/

int					write_error(char *str);
int					error_manager(int error);

/*
** ----- init.c -----
*/

int					init_all(t_args *rules, char **argv);

/*
** ----- utils.c -----
*/

void				*ft_calloc(size_t n, size_t size);
int					ft_atoi(const char *str);
void				action_print(t_args *rules, int id, char *string);

/*
** ----- launcher.c -----
*/

int					launcher(t_args *rules);

#endif
