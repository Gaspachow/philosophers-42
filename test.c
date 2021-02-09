/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmets <gsmets@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 18:25:02 by gsmets            #+#    #+#             */
/*   Updated: 2021/02/09 19:55:18 by gsmets           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// This is a test file to try and learn about phthread and mutex.
// The goal here is to have four philosophers share one fork to eat and digest.
// Digestion time is shorter than eating time, to force each philospher to wait his turn to eat.

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t myfork;
pthread_t 		id[10];

int		eat(int id)
{
	printf("Philospher %i takes fork and eats...\n", id);
	sleep(2);
	printf("Philosopher %i drops fork and is digesting...\n", id);
	return (id);
}

void*	takemyfork(void *arg)
{
	int i = 0;
	int digestor_id;
	int id = *((int *)arg);
	while (i < 2)
	{
		pthread_mutex_lock(&myfork);
		int id = *(int *)arg;
		digestor_id = eat(id);
		pthread_mutex_unlock(&myfork);
		 sleep(1);
		printf("Philosopher %i is done digesting and waiting for the fork...\n", digestor_id);
		i++;
	}

	return NULL;
}

int	main()
{
	int i = 0;
	int ok[10];

	if ((pthread_mutex_init(&myfork, NULL)))
	{
		write(2, "no\n", 3);
	}
	while (i < 4)
	{
		ok[i] = i;
		if ((pthread_create(&(id[i]), NULL, &takemyfork, &ok[i])))
			write(2, "nah\n", 4);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(id[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&myfork);
	return (0);
}