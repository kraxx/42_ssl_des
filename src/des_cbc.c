/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 23:52:02 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:23:26 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static void	parse_flags_des_cbc_2(char *str, t_data *data)
{
	while (*(++str))
	{
		if (*str == 'i')
			if ((data->flags.i = 1))
				data->flags.o = 0;
		if (*str == 'e')
			data->flags.e = 1;
		else if (*str == 'd' || *str == 'D')
			data->flags.d = 1;
		else if (*str == 'o' && !data->flags.i)
			data->flags.o = 1;
		else if (*str == 'a')
			data->flags.a = 1;
		else if (*str == 'k' || *str == 'K')
			data->flags.k = 1;
		else if (*str == 'p')
			data->flags.p = 1;
		else if (*str == 'v')
			data->flags.v = 1;
		else if (*str != 'i')
			write_exit(2);
		if (data->flags.e && data->flags.d)
			write_exit(6);
	}
}

static void	parse_flags_des_cbc(char *str, t_data *data)
{
	if (!(*(str + 1)))
		write_exit(2);
	parse_flags_des_cbc_2(str, data);
}

void		parse_args_des_cbc(int ac, char **av, t_data *data)
{
	int i;

	i = 1;
	while (++i < ac)
	{
		if (*av[i] == '-')
			parse_flags_des_cbc(av[i], data);
		else
			parse_opts_des_cbc(av[i], data);
	}
	if (data->flags.badread)
		write_exit(9);
	if (data->flags.i || data->flags.o)
		write_exit(7);
	if (!data->key_string)
		get_key_from_stdin(data);
	if (!data->init_vector)
		get_vector_from_stdin(data);
	if (!data->input)
		get_input_from_stdin(data);
}

static void	des_cbc_encrypt_64bits(uint64_t k[16], char *new_string,
									int len, t_data *data)
{
	uint64_t	buf;
	uint64_t	buf_prev;
	uint64_t	vector;
	int			i;

	vector = ft_atoull_base(data->init_vector, 16);
	endian_switch64(&vector);
	i = 0;
	while (i <= len)
	{
		buf = des_string_to_buffer(len, i, data);
		des_cbc_xor_vector_en(&buf, &buf_prev, &vector, data);
		endian_switch64(&buf);
		buf = des_block_permutations(k, buf);
		endian_switch64(&buf);
		des_cbc_xor_vector_de(&buf, &buf_prev, &vector, data);
		ft_memcpy(new_string + i, &buf, 8);
		i += 8;
	}
}

void		ft_des_cbc(int ac, char **av, t_data *data)
{
	uint64_t	k[16];
	char		*output;

	parse_args_des_cbc(ac, av, data);
	data->key_string = string_truncate(data->key_string, 16);
	data->init_vector = string_truncate(data->init_vector, 16);
	generate_keys(k, data);
	output = allocate_output_and_proc_de_base64(data);
	des_cbc_encrypt_64bits(k, output, data->len, data);
	if (data->flags.d && !data->flags.nopad)
		des_remove_padding(output, data);
	write_output(output, data);
}
