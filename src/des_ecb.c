/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 22:59:57 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:23:41 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static void	parse_opts_des_ecb(char *str, t_data *data)
{
	if (data->flags.k)
	{
		free(data->key_string);
		if (!(data->key_string = ft_strdup(str)))
			write_exit(5);
		data->flags.k = 0;
	}
	else if (data->flags.o)
	{
		if (data->output_fd != 1)
			close(data->output_fd);
		data->output_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		data->flags.o = 0;
	}
	else if ((data->flags.i || !data->input) && !data->flags.k)
		read_input_from_file(str, data);
}

static void	parse_flags_des_ecb(char *str, t_data *data)
{
	if (!(*(str + 1)))
		write_exit(2);
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
		else if (*str != 'i')
			write_exit(2);
		if (data->flags.e && data->flags.d)
			write_exit(6);
	}
}

static void	parse_args_des_ecb(int ac, char **av, t_data *data)
{
	int i;

	i = 1;
	while (++i < ac)
	{
		if (*av[i] == '-')
			parse_flags_des_ecb(av[i], data);
		else
			parse_opts_des_ecb(av[i], data);
	}
	if (data->flags.badread)
		write_exit(9);
	if (data->flags.i || data->flags.o)
		write_exit(7);
	if (!data->key_string)
		get_key_from_stdin(data);
	if (!data->input)
		get_input_from_stdin(data);
}

static void	des_ecb_encrypt_64bits(uint64_t k[16], char *new_string,
									int len, t_data *data)
{
	uint64_t	buf;
	int			i;

	i = 0;
	while (i <= len)
	{
		buf = des_string_to_buffer(len, i, data);
		endian_switch64(&buf);
		buf = des_block_permutations(k, buf);
		endian_switch64(&buf);
		ft_memcpy(new_string + i, &buf, 8);
		i += 8;
	}
}

void		ft_des_ecb(int ac, char **av, t_data *data)
{
	uint64_t	k[16];
	char		*output;

	parse_args_des_ecb(ac, av, data);
	data->key_string = string_truncate(data->key_string, 16);
	generate_keys(k, data);
	output = allocate_output_and_proc_de_base64(data);
	des_ecb_encrypt_64bits(k, output, data->len, data);
	if (data->flags.d && !data->flags.nopad)
		des_remove_padding(output, data);
	write_output(output, data);
}
