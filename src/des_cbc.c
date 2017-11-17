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

static void	encode_des_cbc(uint64_t k[])
{
	uint64_t	vector;
	char		*new_string;
	int			len;

	if (g_flags.a && g_flags.d)
		g_string = de_base64(g_string);
	len = ft_strlen(g_string);
	new_string = NULL;
	if (g_flags.d && len % 8)
		write_exit(10);
	else
		new_string = ft_strnew((8 * len / 8) + (len % 8 ? 8 : 0) + 1);
	vector = ft_atoull_base(g_init_vector, 16);
	endian_switch64(&vector);
	des_cbc_encrypt_64bits(k, vector, new_string, len);
	if (g_flags.a && !g_flags.d)
	{
		new_string = en_base64(new_string, (8 * len / 8) + (len % 8 ? 8 : 0));
		write(g_output_fd, new_string, ft_strlen(new_string));
	}
	else
		write(g_output_fd, new_string, len);
}

static void	parse_opts_des_cbc(char *str)
{
	if (g_flags.v && g_flags.k)
		write_exit(11);
	if (g_flags.v)
	{
		free(g_init_vector);
		if (!(g_init_vector = ft_strdup(str)))
			write_exit(5);
		g_flags.v = 0;
	}
	else if (g_flags.k)
	{
		free(g_key_string);
		if (!(g_key_string = ft_strdup(str)))
			write_exit(5);
		g_flags.k = 0;
	}
	else if (g_flags.o)
	{
		if (g_output_fd != 1)
			close(g_output_fd);
		g_output_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		g_flags.o = 0;
	}
	else if ((g_flags.i || !g_string) && !g_flags.k && !g_flags.v)
		set_g_string(str);
}

static void	parse_flags_des_cbc(char *str)
{
	if (!(*(str + 1)))
		write_exit(2);
	while (*(++str))
	{
		if (*str == 'i')
			if ((g_flags.i = 1))
				g_flags.o = 0;
		if (*str == 'e')
			g_flags.e = 1;
		else if (*str == 'd' || *str == 'D')
			g_flags.d = 1;
		else if (*str == 'o' && !g_flags.i)
			g_flags.o = 1;
		else if (*str == 'a')
			g_flags.a = 1;
		else if (*str == 'k' || *str == 'K')
			g_flags.k = 1;
		else if (*str == 'v')
			g_flags.v = 1;
		else if (*str != 'i')
			write_exit(2);
		if (g_flags.e && g_flags.d)
			write_exit(6);
	}
}

static void	parse_args_des_cbc(int ac, char **av)
{
	int i;

	i = 1;
	while (++i < ac)
	{
		if (*av[i] == '-')
			parse_flags_des_cbc(av[i]);
		else
			parse_opts_des_cbc(av[i]);
	}
	if (g_flags.i || g_flags.o)
		write_exit(7);
	if (!g_key_string)
		get_key_from_stdin();
	g_key_string = string_64bits(g_key_string);
	if (!g_init_vector)
		get_vector_from_stdin();
	g_init_vector = string_64bits(g_init_vector);
	if (!g_string)
		get_input_from_stdin();
	if (g_flags.badread)
		write_exit(9);
}

void		ft_des_cbc(int ac, char **av)
{
	uint64_t k[16];

	parse_args_des_cbc(ac, av);
	process_keys(k);
	encode_des_cbc(k);
}
