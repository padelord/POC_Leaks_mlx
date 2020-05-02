/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padelord <padelord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 01:13:41 by padelord          #+#    #+#             */
/*   Updated: 2020/05/02 01:28:26 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int   main()
{
	t_env	env;

	env.mlx = 0;
	env.img = 0;
	env.win = 0;
	env.mlx = mlx_init();
	env.img = mlx_new_image(env.mlx, 50, 50);
	env.win = mlx_new_window(env.mlx, 50, 50, "test");
	mlx_destroy_image(env.mlx, env.img);
	mlx_destroy_window(env.mlx, env.win);
	mlx_destroy(env.mlx);
    return 0;
}
