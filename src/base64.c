/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:57:29 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:22:53 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static void	parse_opts_base64(char *str)
{
	if (g_flags.o)
	{
		close(g_output_fd);
		g_output_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		g_flags.o = 0;
	}
	else if (g_flags.i || !g_string)
		set_g_string(str);
}

static void	parse_flags_base64(char *str)
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
		else if (*str == 'o')
		{
			if (!g_flags.i)
				g_flags.o = 1;
		}
		else
			write_exit(2);
		if (g_flags.e && g_flags.d)
			write_exit(6);
	}
}

static void	parse_args_base64(int ac, char **av)
{
	int i;

	i = 1;
	while (++i < ac)
	{
		if (*av[i] == '-')
			parse_flags_base64(av[i]);
		else
			parse_opts_base64(av[i]);
	}
	if (g_flags.i || g_flags.o)
		write_exit(7);
	if (g_flags.badread && !ft_strlen(g_string))
		write_exit(9);
	if (!g_string)
		get_input_from_stdin();
}

void		ft_base64(int ac, char **av)
{
	char	*output;

	parse_args_base64(ac, av);
	if (g_flags.d)
		output = de_base64(g_string);
	else
		output = en_base64(g_string, ft_strlen(g_string));
	ft_putstr_fd(output, g_output_fd);
	free(output);
	if (g_output_fd != 1)
		close(g_output_fd);
}
