/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:20:40 by gsmets            #+#    #+#             */
/*   Updated: 2021/02/12 17:47:36 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tester(t_args rules)
{
	int i;

	printf("Test of arguments:\n");
	printf("nb_philo = %i\n", rules.nb_philo);
	printf("time_death = %i\n", rules.time_death);
	printf("time_eat = %i\n", rules.time_eat);
	printf("time_sleep = %i\n", rules.time_sleep);
	printf("nb_eat = %i\n", rules.nb_eat);
	printf("\n\n ------ test of each philosopher ---- \n\n");
	i = -1;
	while (++i < rules.nb_philo)
	{
		printf("\n- Test of philo number %i -\n", i);
		printf("ID = %i\n", rules.philosophers[i].id);
		printf("x_ate = %i\n", rules.philosophers[i].x_ate);
		printf("left_fork_id = %i\n", rules.philosophers[i].left_fork_id);
		printf("right_fork_id = %i\n", rules.philosophers[i].right_fork_id);
		printf("t_last_meal = %lli\n", rules.philosophers[i].t_last_meal);
	}
}

int		main(int argc, char **argv)
{
	t_args	rules;
	int		ret;

	if (argc != 5 && argc != 6)
		return (write_error("Wrong amount of arguments"));
	if ((ret = init_all(&rules, argv)))
		return (error_manager(ret));
	if (launcher(&rules))
		return (write_error("There was an error creating the threads"));
	return (0);
}
