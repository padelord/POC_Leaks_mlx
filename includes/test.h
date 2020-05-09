/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padelord <padelord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 19:58:55 by padelord          #+#    #+#             */
/*   Updated: 2020/05/06 12:03:06 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# define SX 100
# define SY 100
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "ft_keymap.h"

typedef struct s_env t_env;

struct	s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	int		frame;
};

#endif
