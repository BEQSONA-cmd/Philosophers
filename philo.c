/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:07:16 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/06 22:30:29 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_data_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo->fork = data->forks[i];
		data->philo[i].id = i;
		if (data->nb_philo == i + 1)
			data->philo[i].id_next = 0;
		else
			data->philo[i].id_next = i + 1;
		data->philo[i].food = 0;
		data->philo[i].data = data;
		i++;
	}
}

t_data	ft_init(int ac, char **av)
{
	t_data	data;

	data.nb_philo = ft_atoi(av[1]);
	data.time_die = ft_atoi(av[2]);
	data.time_eat = ft_atoi(av[3]);
	data.time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data.nb_food = ft_atoi(av[5]);
	if (data.nb_philo < 2 || data.nb_philo > 200 || (ac == 6
			&& data.nb_food < 1))
		ft_error("Invalid arguments");
	data.forks = ft_malloc(sizeof(int) * data.nb_philo);
	data.philo = ft_malloc(sizeof(t_philo) * data.nb_philo);
	pthread_mutex_init(&data.print, NULL);
	gettimeofday(&data.time, NULL);
	ft_init_data_philo(&data);
	return (data);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		ft_print(philo, "is thinking");
		pthread_mutex_lock(&philo->data->forks[(philo->id)]);
		pthread_mutex_lock(&philo->data->forks[(philo->id_next)]);
		ft_print(philo, "has taken a fork");
		ft_usleep(philo->data->time_eat);
		ft_print(philo, "is eating");
		philo->last_meal = get_time(philo->data->time);
		pthread_mutex_unlock(&philo->data->forks[(philo->id)]);
		pthread_mutex_unlock(&philo->data->forks[(philo->id_next)]);
		ft_usleep(philo->data->time_eat);
		ft_print(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep);
		if (philo->data->nb_food && ++philo->food == philo->data->nb_food)
			break ;
		if (philo->data->time_die < get_time(philo->data->time)
			- philo->last_meal)
		{
			ft_print(philo, "died");
			break ;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		ft_error("Invalid arguments");
	data = ft_init(ac, av);
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
	while (i < data.nb_philo)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	return (0);
}
