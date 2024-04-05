/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:07:23 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/05 23:36:52 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				*forks;
	t_philo			*philo;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meals_mutex;
	struct timeval	start;
}					t_data;

int					ft_atoi(char *str);
void				ft_print_error(char *str);
int					ft_isdigit(int c);
int					ft_strlen(char *s);
void				ft_putstr_fd(char *s, int fd);
void				ft_usleep(int time);
void				ft_print(t_philo *philo, char *str);
void				ft_print_error(char *str);
void				ft_init_data(t_data *data, int ac, char **av);
void				*ft_philo(void *arg);

#endif