/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:07:16 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/05 23:44:56 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	struct timeval	now;
	int				time;

	pthread_mutex_lock(&philo->data->print_mutex);
	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1000 + now.tv_usec / 1000) - (philo->data->start.tv_sec
			* 1000 + philo->data->start.tv_usec / 1000);
	printf("%d %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_init_data(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->nb_meals = (ac == 6) ? ft_atoi(av[5]) : -1;
	if (data->nb_philo < 2 || data->nb_philo > 200 || (ac == 6
			&& data->nb_meals < 1))
		ft_print_error("Invalid arguments");
	data->forks = malloc(sizeof(int) * data->nb_philo);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->forks_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->meals_mutex, NULL);
	gettimeofday(&data->start, NULL);
	while (i < data->nb_philo)
	{
		data->forks[i] = 1;
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->nb_philo;
		data->philo[i].meals = 0;
		data->philo[i].data = data;
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		i++;
	}
	ft_print(data->philo, "Simulation started");
}

void	ft_usleep(int time)
{
	struct timeval	start;
	struct timeval	now;
	int				diff;

	gettimeofday(&start, NULL);
	while (1)
	{
		gettimeofday(&now, NULL);
		diff = (now.tv_sec * 1000 + now.tv_usec / 1000) - (start.tv_sec * 1000
				+ start.tv_usec / 1000);
		if (diff >= time)
			break ;
		usleep(100);
	}
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->forks_mutex[philo->left_fork]);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks_mutex[philo->right_fork]);
		ft_print(philo, "has taken a fork");
		ft_print(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->forks_mutex[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks_mutex[philo->right_fork]);
		ft_print(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		ft_print_error("Invalid arguments");
	ft_init_data(&data, ac, av);
	while (i < data.nb_philo)
	{
		pthread_create(&data.philo[i].thread, NULL, ft_philo, &data.philo[i]);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	return (0);
}
