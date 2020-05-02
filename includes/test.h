/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padelord <padelord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 19:58:55 by padelord          #+#    #+#             */
/*   Updated: 2020/05/02 01:55:21 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# define SX 100
# define SY 100
# define WNAME "Test"
# include <stdio.h>
# include "mlx.h"
# include "ft_keymap.h"

typedef struct s_env t_env;

struct	s_env
{
	void	*mlx;
	void	*win;
	void	*img;
};

#endif
