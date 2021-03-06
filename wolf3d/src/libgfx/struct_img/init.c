/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <crenaudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 18:31:08 by crenaudi          #+#    #+#             */
/*   Updated: 2020/05/02 04:38:15 by padelord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"

static t_texture	*txt_malloc(t_vec2 size, int nframes)
{
	t_texture	*txt;

	if (!(txt = malloc(sizeof(*txt))))
		return (0);
	ft_bzero(txt, sizeof(*txt));
	if ((txt->src = malloc(sizeof(int) * size.x * size.y * nframes)))
		ft_bzero(txt->src, sizeof(int) * size.x * size.y * nframes);
	if ((txt->frames = malloc(sizeof(int*) * nframes)))
		ft_bzero(txt->src, sizeof(int*) * nframes);
	if (!txt->src || !txt->frames)
	{
		if (txt->src)
			free(txt->frames);
		if (txt->frames)
			free(txt->src);
		ft_bzero(txt, sizeof(*txt));
		free(txt);
		txt = 0;
	}
	return (txt);
}

static int			getsrc(char *path, t_texture *tx)
{
	int		fd;
	t_u32	s;
	int		x;
	int		y;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	read(fd, &s, 4);
	if (s == (t_u32)tx->size.x * (t_u32)tx->size.y * (t_u32)tx->nframes)
	{
		read(fd, &x, 4);
		read(fd, &y, 4);
		if (x == tx->size.x && y / tx->nframes == tx->size.y)
			if ((read(fd, tx->src, s * 4)) == s * 4)
			{
				close(fd);
				return (1);
			}
	}
	close(fd);
	return (0);
}
/*
static int			getsrc(void *mlx, char *path, t_texture *tx)
{
	t_img	img;
	int		x;
	int		y;
	int		done;
	t_u32	*t;

	t = NULL;
	ft_bzero(&img, sizeof(img));
	done = 0;
	if ((img.ptr = mlx_xpm_file_to_image(mlx, path, &x, &y)))
	{
		if ((t = (t_u32*)mlx_get_data_addr(img.ptr, &img.bpp, &img.sl,
			&img.endian)))
		{
			if (x == tx->size.x && y == tx->nframes * tx->size.y && (done = 1))
				tx->src = ft_memcpy(tx->src, t, sizeof(t_u32) * x * y);
			else
				ft_error(1, R_TX_SIZE);
		}
		mlx_destroy_image(mlx, img.ptr);
	}
	else
		ft_error(1, R_TX_FILE);
	ft_bzero(&img, sizeof(img));
	return (done);
}
*/
t_texture			*init_tx(char *path, t_vec2 size, int nframes)
{
	t_texture	*txt;

	if (size.x <= 0 || size.y <= 0 || nframes <= 0)
		return (0);
	if (!(txt = txt_malloc(size, nframes)))
	{
		ft_error(1, R_TX_MALC);
		return (0);
	}
	txt->size = size;
	txt->nframes = nframes;
	if (path)
	{
		if (!(getsrc(path, txt)))
		{
			free(txt->src);
			free(txt->frames);
			bzero(txt, sizeof(*txt));
			free(txt);
			return (0);
		}
	}
	while (nframes--)
		txt->frames[nframes] = txt->src + nframes * size.x * size.y;
	return (txt);
}

t_sprite			*init_sprite(t_texture *tx, t_u32 mod, int cd, t_vec2 pos)
{
	t_sprite	*dest;

	if (!tx)
		return (0);
	else if (!(dest = malloc(sizeof(*dest))))
	{
		close_tx(&tx);
		return (0);
	}
	ft_bzero(dest, sizeof(*dest));
	dest->tx = tx;
	dest->mod = mod;
	dest->cd = cd;
	dest->pos = pos;
	dest->tof = 0;
	dest->cframe = 0;
	return (dest);
}
