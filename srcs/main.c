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
	return (0);
}

int		ft_loop(void *data)
{
	t_env	*env;

	env = (t_env *)data;
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (++env->frame >= 20000)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		mlx_destroy(env->mlx);
		exit(0);
	}
	return (0);
}

void	*get_img_from_wtx(void *mlx, char *path, int *x, int *y)
{
	int				fd;
	unsigned int	*tab;
	unsigned int 	size;
	int				bpp;
	int				sl;
	int 			endian;
	void			*img;
	int				t;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	if ((read(fd, &size, 4)) < 4 || (read(fd, x, 4)) < 4 || (read(fd, y, 4)) < 4)
		return (0);
	if (!(img = mlx_new_image(mlx, *x, *y)))
		return (0);
	tab = (unsigned int *)mlx_get_data_addr(img, &bpp, &sl, &endian);
	if ((read(fd, tab, size * 4)) < (int)size * 4 || (read(fd, &t, 4)))
	{
		close(fd);
		mlx_destroy_image(mlx, img);
		return (0);
	}
	close(fd);
	return (img);
}

int   main(int ac, char **av)
{
	t_env	env;
	int		x;
	int		y;

	env.mlx = 0;
	env.img = 0;
	env.win = 0;
	env.frame = 0;
	env.mlx = mlx_init();
	if ((env.img = get_img_from_wtx(env.mlx, (ac > 1) ? av[1] : "open.wtx", &x, &y)))
	{
		if ((env.win = mlx_new_window(env.mlx, x, y, (ac > 1) ? av[1] : "open.wtx")))
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
