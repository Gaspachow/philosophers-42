/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 18:30:58 by gsmets            #+#    #+#             */
/*   Updated: 2021/02/10 19:20:01 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct	args_s
{
	int nb_philo;
	int	time_death;
	int	time_eat;
	int	time_sleep;
	int	nb_eat;

} 				args_t;

/*
** ----- error_manager.c -----
*/

int		write_error(char *str);

/*
** ----- init.c -----
*/

int		init_rules(args_t *rules, char **argv);

/*
** ----- utils.c -----
*/

void	*ft_calloc(size_t n, size_t size);
int		ft_atoi(const char *str);

#endif