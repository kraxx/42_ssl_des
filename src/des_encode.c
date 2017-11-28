/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:11:48 by jchow             #+#    #+#             */
/*   Updated: 2017/11/22 18:40:03 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

uint64_t	des_block_permutations(uint64_t k[16], uint64_t buf)
{
	t_64bits	ret;
	t_64bits	rl;
	t_64bits	right;
	uint32_t	left;
	int8_t		i;

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

void		des_de_base64(t_data *data)
{
	char	*ret;
	char	*buf;
	size_t	i;
	size_t	len;
	int8_t	remainder;

	len = data->len;
	ret = ft_strnew(((data->len / 4) * 3) + ((data->len % 4) ? 3 : 0));
	i = -1;
	while (++i < len / 65)
	{
		buf = de_base64(data->input + (i * 65), 65, data);
		ft_memcpy(ret + (i * 48), buf, 48);
		free(buf);
	}
	remainder = len % 65;
	if (remainder)
	{
		buf = de_base64(data->input + (i * 65), remainder, data);
		ft_memcpy(ret + (i * 48), buf, ((remainder / 4) * 3) +
				((remainder % 4) ? 3 : 0));
		free(buf);
	}
	free(data->input);
	data->input = ret;
}

static void	des_en_base64_remainder(char *input, char **ret,
									size_t len, t_data *data)
{
	char	*tmp;
	char	*buf;

	buf = en_base64(input, len, data);
	tmp = ft_strjoin(*ret, buf);
	free(*ret);
	free(buf);
	*ret = tmp;
}

char		*des_en_base64(char *input, t_data *data)
{
	char	*ret;
	char	*buf;
	char	*tmp;
	size_t	i;
	size_t	len;

	len = data->len;
	ret = ft_strnew(0);
	i = 0;
	while (i < len / 48)
	{
		buf = en_base64(input + (i * 48), 48, data);
		tmp = ft_strjoin(ret, buf);
		free(ret);
		free(buf);
		ret = tmp;
		++i;
	}
	if (len % 48)
		des_en_base64_remainder(input + (i * 48), &ret, len % 48, data);
	return (ret);
}
