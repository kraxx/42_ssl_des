/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 21:26:44 by jchow             #+#    #+#             */
/*   Updated: 2017/11/22 18:39:01 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static uint32_t	fourbytes_to_three(uint32_t n)
{
	uint32_t ret[4];

	ret[0] = (n << 2) & (MASK_6BITS << 26);
	ret[1] = (n << 4) & (MASK_6BITS << 20);
	ret[2] = (n << 6) & (MASK_6BITS << 14);
	ret[3] = (n << 8) & (MASK_6BITS << 8);
	return (ret[0] | ret[1] | ret[2] | ret[3]);
}

static void		de_base64_decode(char *input, char *ret,
								size_t len, t_data *data)
{
	t_32bits	n;
	int8_t		i;

	while (len > 0)
	{
		i = -1;
		while (++i < 4)
		{
			if (*input++ == '=')
			{
				n.c[i] = 0;
				--data->len;
			}
			else
				n.c[i] = ft_indexof(g_base64, *(input - 1));
		}
		endian_switch32(&n.i);
		n.i = fourbytes_to_three(n.i);
		endian_switch32(&n.i);
		ft_memcpy(ret, &n.i, 3);
		len = len > 3 ? len - 4 : 0;
		ret += 3;
		--data->len;
	}
}

char			*de_base64(char *input, size_t len, t_data *data)
{
	char		*ret;

	if (input[len - 1] == '\n')
	{
		--len;
		--data->len;
	}
	ret = ft_strnew(len);
	de_base64_decode(input, ret, len, data);
	return (ret);
}

static void		en_base64_last_2bytes(char *input, char **ret,
										size_t len, t_data *data)
{
	uint32_t	n;
	char		*s;

	n = 0;
	s = *ret;
	if (len == 2)
	{
		ft_memcpy(&n, input, 3);
		endian_switch32(&n);
		*s++ = g_base64[(n >> 26) & MASK_6BITS];
		*s++ = g_base64[(n >> 20) & MASK_6BITS];
		*s++ = g_base64[(n >> 14) & MASK_6BITS];
		*s++ = '=';
	}
	else if (len == 1)
	{
		*s++ = g_base64[(*input >> 2) & MASK_6BITS];
		*s++ = g_base64[(*input << 4) & MASK_6BITS];
		*s++ = '=';
		*s++ = '=';
	}
	*ret += 4;
	data->len += 4 - len;
}

char			*en_base64(char *input, size_t len, t_data *data)
{
	uint32_t	n;
	char		*ret;
	char		*head;

	ret = ft_strnew(((len / 3) * 4) + ((len % 3) ? 4 : 0) + 1);
	head = ret;
	n = 0;
	while (len > 2)
	{
		ft_memcpy(&n, input, 3);
		endian_switch32(&n);
		*ret++ = g_base64[(n >> 26) & MASK_6BITS];
		*ret++ = g_base64[(n >> 20) & MASK_6BITS];
		*ret++ = g_base64[(n >> 14) & MASK_6BITS];
		*ret++ = g_base64[(n >> 8) & MASK_6BITS];
		input += 3;
		len -= 3;
		++data->len;
	}
	if (len > 0)
		en_base64_last_2bytes(input, &ret, len, data);
	++data->len;
	*ret = '\n';
	return (head);
}
