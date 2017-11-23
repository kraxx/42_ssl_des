/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 15:44:30 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:26:04 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

/*
** This is my implementation of standard Base64 & OpenSSL's DES encryption/
** decryption algorithms.
**
** Commands currently handled are:
**
** base64
** des-ecb
** des-cbc
** triple des-cbc
*/

static int	parse_command(char *cmd)
{
	short	i;

	i = -1;
	while (++i < CMD_COUNT)
		if (!ft_strcmp(cmd, g_commands[i]))
			return (i);
	write_exit(1);
	return (-42);
}

int			main(int ac, char **av)
{
	t_data	data;
	short	cmd_index;

	if (ac < 2)
		write_exit(0);
	cmd_index = parse_command(av[1]);
	ft_bzero(&data, sizeof(t_data));
	data.output_fd = 1;
	g_cmd_fp[cmd_index](ac, av, &data);
	return (0);
}
