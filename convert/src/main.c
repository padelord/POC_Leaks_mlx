/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: padelord <padelord@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 11:31:53 by padelord          #+#    #+#             */
/*   Updated: 2020/05/06 11:31:54 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "convert.h"

int		check_dest(const char *path)
{
	int		fd;
	char	c;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (open(path, O_WRONLY | O_CREAT , S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH));
	else
		printf("%s already exits, do you want to Replace? Append? or Cancel?\n", path);
	close(fd);
	read(0, &c, 2);
	if (c == 'C' || c == 'c')
		return (-2);
	else if (c == 'R' || c == 'r')
	{
		if (!(remove(path)))
		{
			printf("%s succesfully removed!\n", path);
			return (open(path, O_WRONLY | O_CREAT , S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH));
		}
		else
		{
			printf("Unable to delete %s\n", path);
			return (-2);
		}
	}
	else if (c == 'A' || c == 'a')
	{
		printf("getting %s in append mode\n", path);
		return (open(path, O_WRONLY | O_APPEND));
	}
	return (-1);
}

int		check_param(char *src, char *ext)
{
	unsigned int	s1;
	unsigned int	s2;

	return ((!(src) || !(ext) || (s1 = ft_strlen(src)) < (s2 = ft_strlen(ext))) ? 0 : !(ft_strcmp(src + s1 - s2, ext)));
}

int				copy_data(void *mlx, char *path, int fd)
{
	void				*img;
	unsigned int		*data;
	int					x = 0;
	int					y = 0;
	int					bpp;
	int					sln;
	int					end;
	unsigned int		size;
	unsigned long int	test;
	unsigned int		i;

	if ((img = mlx_xpm_file_to_image(mlx, path, &x, &y)))
	{
		data = (unsigned int*)mlx_get_data_addr(img, &bpp, &sln, &end);
		printf("data got:\nx :\t%d\ny :\t%d\nbpp :\t%d\nsl :\t%d\nend :\t%d\n", x, y, bpp, sln, end);
		if ((test = x * y) > UINT_MAX)
		{
			printf("Source too big\nUnable to load\n");
			return (0);
		}
		size = (unsigned int)test;
		write(fd, &size, 4);
		write(fd, &x, 4);
		write(fd, &y, 4);
		i = 0;
		while (i < size)
		{
			write(fd, data + i, 4);
			i++;
		}
		return (1);
	}
	else
		printf("Failed to get %s\n", path);
	return (0);
}

int   main(int ac, char **av)
{
	void				*mlx;
	int					fd;
	unsigned int		n;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		read(fd, &n, 4);
		close(fd);
		printf("value : %u\n", n);
	}
	if (ac == 3)
	{
		if (!(check_param(av[1], ".xpm")))
		{
			printf("%s is not a valid '.xpm' file\n", av[1]);
			return (0);
		}
		if (!(check_param(av[2], ".wtx")))
		{
			printf("%s is not a valid '.wtx' file\n", av[2]);
			return (0);
		}
		if ((fd = check_dest(av[2])) < 0)
			printf("%s\n", (fd == -1 ? "Error" : "Canceled"));
		else
		{
			printf("%s succesfully created, fd=%d\n", av[2], fd);
		}
		mlx = mlx_init();
		copy_data(mlx, av[1], fd);
		mlx_destroy(mlx);
		if (fd > 0)
			close(fd);
	}
	else
		printf("Usage : ./convert \"source.xpm\" \"dest\"\n");
    return 0;
}
