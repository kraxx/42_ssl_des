/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:14:42 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:26:10 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

uint64_t	permutate(uint64_t block, const t_uc tab[], int size, uint64_t mask)
{
	uint64_t	ret;
	int			i;

	ret = 0;
	i = 0;
	while (++i <= size)
	{
		if (tab[i - 1] > i)
			ret |= (block << (tab[i - 1] - i)) & mask;
		else
			ret |= (block >> (i - tab[i - 1])) & mask;
		mask >>= 1;
	}
	return (ret);
}

uint64_t	permutate_e(uint64_t r_block)
{
	uint64_t	ret;
	uint64_t	mask;
	int			i;
	int			j;

	mask = MASK_64;
	i = 0;
	j = 1;
	ret = (r_block << 31) & mask;
	while (++i < 48)
	{
		if (!(i % 6))
			j += 2;
		else if (i == 47)
			j = 47;
		ret |= r_block >> j & (mask >>= 1);
	}
	return (ret);
}

uint32_t	permutate_sbox(uint64_t e_block)
{
	uint32_t	row;
	uint32_t	col;
	uint32_t	ret;
	int			i;

	ret = 0;
	i = -1;
	while (++i < 8)
	{
		row = ((e_block >> 62) & 2) | ((e_block >> 58) & 1);
		col = (e_block >> 59) & 15;
		e_block <<= 6;
		ret |= g_des_sbox_arr[i][(row * 16) + col];
		if (i < 7)
			ret <<= 4;
	}
	return (ret);
}
