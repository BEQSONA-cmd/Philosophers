/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:07:16 by btvildia          #+#    #+#             */
/*   Updated: 2024/05/23 13:04:54 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	get_time(struct timeval time)
{
	struct timeval	now;
	int				diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec * 1000 + now.tv_usec / 1000) - (time.tv_sec * 1000
			+ time.tv_usec / 1000);
	return (diff);
}

void	ft_init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->philo[i].fork, NULL);
		data->philo[i].id = i;
		data->philo[i].last_meal = get_time(data->time);
		if (data->nb_philo == i + 1)
			data->philo[i].id_next = 0;
		else
			data->philo[i].id_next = i + 1;
		data->philo[i].food = 0;
		data->philo[i].data = data;
		i++;
	}
}

int	ft_init_data(int ac, char **av, t_data *data)
{
	if (ft_strlen(av[1]) == 0 || ft_strlen(av[2]) == 0 || ft_strlen(av[3]) == 0
		|| ft_strlen(av[4]) == 0)
		return (ft_error("Invalid arguments"));
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (data->time_die < 60 || data->time_eat < 60 || data->time_sleep < 60)
		return (ft_error("Invalid arguments"));
	data->nb_food = 0;
	if (ac == 6)
		data->nb_food = ft_atoi(av[5]);
	if (data->nb_philo < 1 || data->nb_philo > 200 || (ac == 6
			&& data->nb_food < 1))
		return (ft_error("Invalid arguments"));
	data->philo = ft_malloc(sizeof(t_philo) * data->nb_philo);
	data->dead = 0;
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->ate, NULL);
	gettimeofday(&data->time, NULL);
	ft_init_philo(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (ft_error("Invalid arguments"));
	if (ft_init_data(ac, av, &data))
		return (1);
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
	free(data.philo);
	return (0);
}
