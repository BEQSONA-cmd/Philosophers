/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 21:07:23 by btvildia          #+#    #+#             */
/*   Updated: 2024/04/06 22:30:29 by btvildia         ###   ########.fr       */
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
	int				id_next;
	pthread_mutex_t	fork;
	int				food;
	struct s_data	*data;
	pthread_t		thread;
	int				last_meal;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_food;
	pthread_mutex_t	*forks;
	t_philo			*philo;
	pthread_mutex_t	print;
	struct timeval	time;
}					t_data;

void				*ft_philo(void *arg);
void				ft_usleep(int time);
long				get_time(struct timeval time);
void				ft_print(t_philo *philo, char *str);
void				*ft_malloc(size_t size);
int					ft_atoi(char *str);
void				ft_error(char *str);
int					ft_strlen(char *s);
void				ft_usleep(int time);
t_data				ft_init(int ac, char **av);

#endif
