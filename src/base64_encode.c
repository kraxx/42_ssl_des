/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 21:26:44 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:23:06 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static uint32_t	four_to_three(uint32_t n)
{
	uint32_t ret[4];

	ret[0] = (n << 2) & (MASK_6BITS << 26);
	ret[1] = (n << 4) & (MASK_6BITS << 20);
	ret[2] = (n << 6) & (MASK_6BITS << 14);
	ret[3] = (n << 8) & (MASK_6BITS << 8);
	return (ret[0] | ret[1] | ret[2] | ret[3]);
}

static void		de_base64_pt2(char *input, char *ret, int len)
{
	t_32bits	n;

	while (len > 0)
	{
		n.c[0] = ft_indexof(g_base64, *input++);
		n.c[1] = ft_indexof(g_base64, *input++);
		if (*input++ == '=')
			n.c[2] = 0;
		else
			n.c[2] = ft_indexof(g_base64, *(input - 1));
		if (*input++ == '=')
			n.c[3] = 0;
		else
			n.c[3] = ft_indexof(g_base64, *(input - 1));
		endian_switch32(&n.i);
		n.i = four_to_three(n.i);
		endian_switch32(&n.i);
		ft_memcpy(ret, &n.i, 3);
		len -= 4;
		ret += 3;
	}
}

char			*de_base64(char *input)
{
	int			len;
	char		*ret;
	char		*head;

	len = ft_strlen(input);
	if (input[len - 1] == '\n')
		--len;
	ret = ft_strnew((len / 4) * 3);
	head = ret;
	de_base64_pt2(input, ret, len);
	return (head);
}

static void		en_base64_pt2(char *input, char **str, int len)
{
	uint32_t	n;
	char		*ret;

	ret = *str;
	if (len == 2)
	{
		memcpy(&n, input, 3);
		endian_switch32(&n);
		*ret++ = g_base64[(n >> 26) & MASK_6BITS];
		*ret++ = g_base64[(n >> 20) & MASK_6BITS];
		*ret++ = g_base64[(n >> 14) & MASK_6BITS];
		*ret++ = '=';
	}
	else if (len == 1)
	{
		*ret++ = g_base64[(*input >> 2) & MASK_6BITS];
		*ret++ = g_base64[(*input << 4) & MASK_6BITS];
		*ret++ = '=';
		*ret++ = '=';
	}
	*str += 4;
}

char			*en_base64(char *input, int len)
{
	uint32_t	n;
	char		*ret;
	char		*head;

	ret = ft_strnew(((len / 3) * 4) + ((len % 3) ? 4 : 0) + 1);
	head = ret;
	while (len > 2)
	{
		memcpy(&n, input, 3);
		endian_switch32(&n);
		*ret++ = g_base64[(n >> 26) & MASK_6BITS];
		*ret++ = g_base64[(n >> 20) & MASK_6BITS];
		*ret++ = g_base64[(n >> 14) & MASK_6BITS];
		*ret++ = g_base64[(n >> 8) & MASK_6BITS];
		input += 3;
		len -= 3;
	}
	if (len > 0)
		en_base64_pt2(input, &ret, len);
	*ret = '\n';
	return (head);
}
