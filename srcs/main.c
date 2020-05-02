#include "test.h"
#define WNAME "Test"

int		ft_key(int keycode, void *data)
{
	t_env	*env;

	env = (t_env *)data;
	if (keycode == K_ESC)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		mlx_destroy(env->mlx);
		exit(0);
	}
}

int		ft_loop(void *data)
{
	t_env	*env;

	env = (t_env *)data;
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (1);
}

void 	ft_color_img(void *img, int x, int y)
{
	unsigned int	*buffer = 0;
	int				bpp = 0;
	int				sl = 0;
	int				endian = 0;
	int				size;
	int				i;

	buffer = mlx_get_data_addr(img, &bpp, &sl, &endian);
	printf("bpp: %d\nsl: %d\nendian: %d\n", bpp, sl, endian);
	size = x * y;
	i = -1;
	while (++i < size)
	{
		buffer[i] = 0xFF0033;
	}
}

int   main()
{
	t_env	env;
	int		x;
	int		y;

	env.mlx = 0;
	env.img = 0;
	env.win = 0;
	env.mlx = mlx_init();
	if ((env.img = mlx_xpm_file_to_image(env.mlx, "open.xpm", &x, &y)))
	{
//		ft_color_img(env.img, SX, SY);
		if ((env.win = mlx_new_window(env.mlx, x, y, WNAME)))
		{
			mlx_key_hook(env.win, ft_key, &env);
			mlx_loop_hook(env.mlx, ft_loop, &env);
			mlx_loop(env.mlx);
		}
		mlx_destroy_image(env.mlx, env.img);
	}
	mlx_destroy(env.mlx);
    return 0;
}
/*
env.mlx = 0;
env.img = 0;
env.win = 0;
env.mlx = mlx_init();
if ((env.img = mlx_new_image(env.mlx, SX, SY)))
{
	ft_color_img(env.img, SX, SY);
	if ((env.win = mlx_new_window(env.mlx, SX, SY, WNAME)))
	{
		mlx_key_hook(env.win, ft_key, &env);
		mlx_loop_hook(env.mlx, ft_loop, &env);
		mlx_loop(env.mlx);
	}
	mlx_destroy_image(env.mlx, env.img);
}
mlx_destroy(env.mlx);
return 0;
*/
