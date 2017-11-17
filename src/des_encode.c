/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:11:48 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:23:58 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static uint64_t	encode_des_block(uint64_t k[], uint64_t buf)
{
	t_64bits	ret;
	t_64bits	rl;
	t_64bits	right;
	uint32_t	left;
	int			i;

	ret.ll = permutate(buf, g_ip, 64, MASK_64);
	left = ret.i[1];
	right.i[0] = ret.i[0];
	i = -1;
	while (++i < 16)
	{
		rl.i[1] = right.i[0];
		ret.ll = permutate_e(right.ll << 32);
		ret.i[0] = permutate_sbox(ret.ll ^ k[i]);
		ret.i[0] = permutate(ret.i[0], g_p, 48, MASK_32);
		rl.i[0] = left ^ ret.i[0];
		left = rl.i[1];
		right.ll = rl.i[0];
	}
	rl.ll = (right.ll << 32) | left;
	ret.ll = permutate(rl.ll, g_final_ip, 64, MASK_64);
	return (ret.ll);
}

static void		string_to_buffer(uint64_t *buf, int len, int i)
{
	if (i + 8 < len)
		ft_memcpy(buf, g_string + i, 8);
	else
	{
		ft_bzero(buf + 8 - (len - i), 8 - (len - i));
		ft_memcpy(buf, g_string + i, len - i);
	}
}

void			des_cbc_encrypt_64bits(uint64_t k[], uint64_t vector,
										char *new_string, int len)
{
	uint64_t	buf_prev;
	uint64_t	buf;
	int			i;

	i = 0;
	while (i < len)
	{
		string_to_buffer(&buf, len, i);
		if (g_flags.d)
			buf_prev = buf;
		else
			buf ^= vector;
		endian_switch64(&buf);
		buf = encode_des_block(k, buf);
		endian_switch64(&buf);
		if (g_flags.d)
		{
			buf ^= vector;
			vector = buf_prev;
		}
		else
			vector = buf;
		ft_memcpy(new_string + i, &buf, 8);
		i += 8;
	}
}

void			des_ecb_encrypt_64bits(uint64_t k[], char *new_string, int len)
{
	uint64_t	buf;
	int			i;

	i = 0;
	while (i < len)
	{
		string_to_buffer(&buf, len, i);
		endian_switch64(&buf);
		buf = encode_des_block(k, buf);
		endian_switch64(&buf);
		ft_memcpy(new_string + i, &buf, 8);
		i += 8;
	}
}
