/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crenaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:15:09 by crenaudi          #+#    #+#             */
/*   Updated: 2019/01/16 21:58:49 by crenaudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_print_bits(t_u64 a, int bits, int nl)
{
	int		i;
	int		j;
	int		b;

	j = 0;
	j = bits - 8;
	i = bits / 8;
	while (i--)
	{
		b = 8;
		while (b--)
		{
			ft_putnbr((a & (1 << (b + j))) != 0);
			bits--;
			if (bits % nl == 0)
				ft_putchar('\n');
		}
		j = j - 8;
	}
}
