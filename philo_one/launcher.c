/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:19:34 by gsmets            #+#    #+#             */
/*   Updated: 2021/02/12 18:00:50 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philosopher *philo)
{
	t_args *rules;

	rules = philo->rules;
	pthread_mutex_lock(&(rules->forks[philo->left_fork_id]));
	printf("Philosopher %i takes his left fork! (id: %i) -- FORK_L --\n", philo->id, philo->left_fork_id);
	pthread_mutex_lock(&(rules->forks[philo->right_fork_id]));
	printf("Philosopher %i takes his right fork! (id: %i) -- FORK_R --\n", philo->id, philo->right_fork_id);
	printf("Philosopher %i eats -- EATING --\n", philo->id);
	usleep(rules->time_eat * 1000);
	pthread_mutex_unlock(&(rules->forks[philo->left_fork_id]));
	printf("Philosopher %i drops his left fork! (id: %i) -- UFORK_L --\n", philo->id, philo->left_fork_id);
	pthread_mutex_unlock(&(rules->forks[philo->right_fork_id]));
	printf("Philosopher %i drops his right fork! (id: %i) -- UFORK_R --\n", philo->id, philo->right_fork_id);
}

void	*philo_thread(void *void_philosopher)
{
	int i;

	i = 0;
	t_philosopher *philo = (t_philosopher *)void_philosopher;
	while(i < philo->rules->nb_eat || philo->rules->nb_eat == -1)
	{
		philo_eats(philo);
		printf("Philosopher %i takes a nice nap... zZzZ\n", philo->id);
		usleep(philo->rules->time_sleep * 1000);
		printf("Philosopher %i wakes up and think... (⇀‸↼)\n", philo->id);
		i++;
	}
}

void	exit_launcher(t_args *rules, t_philosopher *philos)
{
	int i;

	i = -1;
	while (++i < rules->nb_philo)
	{
		pthread_join(philos[i].thread_id, NULL);
		pthread_mutex_destroy(&(rules->forks[i]));
	}
}

int		launcher(t_args *rules)
{
	int i;
	t_philosopher *philos;

	i = 0;
	philos = rules->philosophers;
	while (i < rules->nb_philo)
	{
		while (i < rules->nb_philo)
		{
			if (pthread_create(&(philos[i].thread_id), NULL, philo_thread, &(philos[i])))
				return (1);
			i += 2;
		}
		if (!(i % 2))
		{
			usleep(2000);
			i = 1;
		}
	}
	i = 0;
	exit_launcher(rules, philos);
	return (0);
}