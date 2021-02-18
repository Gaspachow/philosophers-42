/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:19:34 by gsmets            #+#    #+#             */
/*   Updated: 2021/02/18 20:46:14 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eats(t_philosopher *philo)
{
	t_rules *rules;

	rules = philo->rules;
	sem_wait(rules->forks);
	action_print(rules, philo->id, "has taken a fork");
	sem_wait(rules->forks);
	action_print(rules, philo->id, "has taken a fork");
	sem_wait(rules->meal_check);
	action_print(rules, philo->id, "is eating");
	philo->t_last_meal = timestamp();
	sem_post(rules->meal_check);
	(philo->x_ate)++;
	smart_sleep(rules->time_eat, rules);
	sem_post(rules->forks);
	sem_post(rules->forks);
}

void	*death_checker(void *void_philosopher)
{
	t_philosopher	*philo;
	t_rules			*r;

	philo = (t_philosopher *)void_philosopher;
	r = philo->rules;
	while (42)
	{
		sem_wait(r->meal_check);
		if (time_diff(philo->t_last_meal, timestamp()) > r->time_death)
		{
			action_print(r, philo->id, "died");
			r->dieded = 1;
		}
		sem_post(r->meal_check);
		if (r->dieded)
			break ;
		usleep(1000);
		if (philo->x_ate >= r->nb_eat)
			break ;
	}
	return (NULL);
}

void	p_process(void *void_philosopher)
{
	int				i;
	t_philosopher	*philo;
	t_rules			*rules;

	i = 0;
	philo = (t_philosopher *)void_philosopher;
	rules = philo->rules;
	philo->t_last_meal = timestamp();
	pthread_create(&(philo->death_check), NULL, death_checker, void_philosopher);
	if (philo->id % 2)
		usleep(15000);
	while (!(rules->dieded))
	{
		if (i >= rules->nb_eat && rules->nb_eat != -1)
			break ;
		philo_eats(philo);
		action_print(rules, philo->id, "is sleeping");
		smart_sleep(rules->time_sleep, rules);
		action_print(rules, philo->id, "is thinking");
		i++;
	}
	exit(0);
}

void	exit_launcher(t_rules *rules)
{
	int i;

	i = -1;
	sem_close(rules->forks);
	sem_close(rules->writing);
	sem_close(rules->meal_check);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_write");
	sem_unlink("/philo_mealcheck");
}

int		launcher(t_rules *rules)
{
	int				i;
	t_philosopher	*phi;

	i = -1;
	phi = rules->philosophers;
	rules->first_timestamp = timestamp();
	while (++i < rules->nb_philo)
	{
		phi[i].proc_id = fork();
		if (phi[i].proc_id < 0)
			return (1);
		if (phi[i].proc_id == 0)
			p_process(&(phi[i]));
		usleep(100);
	}
	usleep(5000000);
	exit_launcher(rules);
	return (0);
}
