/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_cbc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 18:46:43 by jchow             #+#    #+#             */
/*   Updated: 2017/11/22 18:39:17 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static void	des3_cbc_encrypt_64bits(uint64_t k[3][16], char *new_string,
										size_t len, t_data *data)
{
	uint64_t	buf;
	uint64_t	buf_prev;
	uint64_t	vector;
	size_t		i;
	short		j;

	vector = ft_atoull_base(data->init_vector, 16);
	endian_switch64(&vector);
	i = 0;
	while (i <= len)
	{
		buf = des_string_to_buffer(len, i, data);
		des_cbc_xor_vector_en(&buf, &buf_prev, &vector, data);
		endian_switch64(&buf);
		j = -1;
		while (++j < 3)
			buf = des_block_permutations(k[j], buf);
		endian_switch64(&buf);
		des_cbc_xor_vector_de(&buf, &buf_prev, &vector, data);
		ft_memcpy(new_string + i, &buf, 8);
		i += 8;
	}
}

void		ft_des3_cbc(int ac, char **av, t_data *data)
{
	uint64_t	k[3][16];
	char		*output;

	parse_args_des_cbc(ac, av, data);
	data->key_string = string_truncate(data->key_string, 48);
	data->init_vector = string_truncate(data->init_vector, 16);
	generate_des3_keys(k, data);
	output = allocate_output_and_proc_de_base64(data);
	des3_cbc_encrypt_64bits(k, output, data->len, data);
	if (data->flags.d && !data->flags.nopad)
		des_remove_padding(output, data);
	write_output(output, data);
}
