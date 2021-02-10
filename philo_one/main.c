/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:20:40 by gsmets            #+#    #+#             */
/*   Updated: 2021/02/10 19:17:33 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void tester(args_t rules)
{
	printf("Test of arguments:\n");
	printf("nb_philo = %i\n", rules.nb_philo);
	printf("time_death = %i\n", rules.time_death);
	printf("time_eat = %i\n", rules.time_eat);
	printf("time_sleep = %i\n", rules.time_sleep);
	printf("nb_eat = %i\n", rules.nb_eat);
}

int	main(int argc, char **argv)
{
	args_t *rules;

	if (argc != 5 && argc != 6)
		return (write_error("Wrong amount of arguments"));
	rules = ft_calloc(1, sizeof(args_t));
	if (init_rules(rules, argv))
		return (write_error("At least one wrong argument"));
	tester(*rules);
	return (0);
}