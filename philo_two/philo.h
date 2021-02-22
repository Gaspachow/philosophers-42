/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:30:58 by gsmets            #+#    #+#             */
/*   Updated: 2021/02/22 10:33:07 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

struct s_rules;

typedef	struct			s_philosopher
{
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct			s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	int					dieded;
	int					all_ate;
	long long			first_timestamp;
	sem_t				*meal_check;
	sem_t				*forks;
	sem_t				*writing;
	t_philosopher		philosophers[250];
}						t_rules;

/*
** ----- error_manager.c -----
*/

int						write_error(char *str);
int						error_manager(int error);

/*
** ----- init.c -----
*/

int						init_all(t_rules *rules, char **argv);

/*
** ----- utils.c -----
*/

int						ft_atoi(const char *str);
void					action_print(t_rules *rules, int id, char *string);
long long				timestamp(void);
long long				time_diff(long long past, long long pres);
void					smart_sleep(long long time, t_rules *rules);

/*
** ----- launcher.c -----
*/

int						launcher(t_rules *rules);
void					exit_launcher(t_rules *rules, t_philosopher *philos);

#endif
