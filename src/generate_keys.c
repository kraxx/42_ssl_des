/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:43:52 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:25:52 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static void	generate_subkeys_en(uint32_t c[], uint32_t d[])
{
	int	i;

	i = -1;
	while (++i < 16)
	{
		c[i + 1] = ((c[i] << g_subkey_shifts[i]) |
			(c[i] >> (28 - g_subkey_shifts[i]))) & 0xFFFFFFF0;
		d[i + 1] = ((d[i] << g_subkey_shifts[i]) |
			(d[i] >> (28 - g_subkey_shifts[i]))) & 0xFFFFFFF0;
	}
}

static void	generate_subkeys_de(uint32_t c[], uint32_t d[])
{
	int	i;

	c[1] = c[0];
	d[1] = d[0];
	i = 0;
	while (++i < 16)
	{
		c[i + 1] = ((c[i] >> g_subkey_shifts[i]) |
			(c[i] << (28 - g_subkey_shifts[i]))) & 0xFFFFFFF0;
		d[i + 1] = ((d[i] >> g_subkey_shifts[i]) |
			(d[i] << (28 - g_subkey_shifts[i]))) & 0xFFFFFFF0;
	}
}

static void	generate_16keys(uint32_t c[], uint32_t d[], uint64_t k[])
{
	uint64_t	cd;
	int			i;

	i = -1;
	while (++i < 16)
	{
		cd = ((uint64_t)c[i + 1] << 32) | ((uint64_t)d[i + 1] << 4);
		k[i] = permutate(cd, g_pc2, 48, MASK_64);
	}
}

void		generate_des3_keys(uint64_t k[3][16], t_data *data)
{
	uint32_t	c[17];
	uint32_t	d[17];
	uint64_t	key;
	int			i;

	i = -1;
	while (++i < 3)
	{
		key = ft_atoull_base(ft_strsub(data->key_string, i * 16, 16), 16);
		key = permutate(key, g_pc1, 56, MASK_64);
		c[0] = key >> 32 & 0xFFFFFFF0;
		d[0] = key >> 4 & 0xFFFFFFF0;
		if (data->flags.d)
			generate_subkeys_de(c, d);
		else
			generate_subkeys_en(c, d);
		generate_16keys(c, d, k[i]);
		data->flags.d = data->flags.d ? 0 : 1;
	}
	data->flags.d = data->flags.d ? 0 : 1;
}

void		generate_keys(uint64_t k[16], t_data *data)
{
	uint32_t	c[17];
	uint32_t	d[17];
	uint64_t	key;

	key = ft_atoull_base(data->key_string, 16);
	key = permutate(key, g_pc1, 56, MASK_64);
	c[0] = key >> 32 & 0xFFFFFFF0;
	d[0] = key >> 4 & 0xFFFFFFF0;
	if (data->flags.d)
		generate_subkeys_de(c, d);
	else
		generate_subkeys_en(c, d);
	generate_16keys(c, d, k);
}
