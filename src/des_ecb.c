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

static void	encode_des_ecb(uint64_t k[])
{
	char	*new_string;
	int		len;

	if (g_flags.a && g_flags.d)
		g_string = de_base64(g_string);
	len = ft_strlen(g_string);
	new_string = NULL;
	if (g_flags.d && len % 8)
		write_exit(10);
	else
		new_string = ft_strnew((8 * len / 8) + (len % 8 ? 8 : 0) + 1);
	des_ecb_encrypt_64bits(k, new_string, len);
	if (g_flags.a && !g_flags.d)
	{
		new_string = en_base64(new_string, (8 * len / 8) + (len % 8 ? 8 : 0));
		write(g_output_fd, new_string, ft_strlen(new_string));
	}
	else
		write(g_output_fd, new_string, len);
}

static void	parse_opts_des_ecb(char *str)
{
	if (g_flags.k)
	{
		if (g_key_string)
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
	else if ((g_flags.i || !g_string) && !g_flags.k)
		set_g_string(str);
}

static void	parse_flags_des_ecb(char *str)
{
	if (!(*(str + 1)))
		write_exit(2);
	while (*(++str))
	{
		if (*str == 'e')
			g_flags.e = 1;
		else if (*str == 'd' || *str == 'D')
			g_flags.d = 1;
		else if (*str == 'i')
		{
			g_flags.i = 1;
			g_flags.o = 0;
		}
		else if (*str == 'o' && !g_flags.i)
			g_flags.o = 1;
		else if (*str == 'a')
			g_flags.a = 1;
		else if (*str == 'k' || *str == 'K')
			g_flags.k = 1;
		else
			write_exit(2);
		if (g_flags.e && g_flags.d)
			write_exit(6);
	}
}

static void	parse_args_des_ecb(int ac, char **av)
{
	int i;

	i = 1;
	while (++i < ac)
	{
		if (*av[i] == '-')
			parse_flags_des_ecb(av[i]);
		else
			parse_opts_des_ecb(av[i]);
	}
	if (g_flags.i || g_flags.o)
		write_exit(7);
	if (!g_key_string)
		get_key_from_stdin();
	g_key_string = string_64bits(g_key_string);
	if (!g_string)
		get_input_from_stdin();
	if (g_flags.badread)
		write_exit(9);
}

void		ft_des_ecb(int ac, char **av)
{
	uint64_t k[16];

	parse_args_des_ecb(ac, av);
	process_keys(k);
	encode_des_ecb(k);
}
