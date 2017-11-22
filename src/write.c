/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 23:16:16 by jchow             #+#    #+#             */
/*   Updated: 2017/11/18 22:00:28 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static void	write_usage(void)
{
	int	i;

	i = 0;
	write(1, "\nStandard commands:\n", 20);
	write(1, "\nMessage Digest commands:\n", 26);
	write(1, "\nCipher commands:\n", 18);
	while (i < CMD_COUNT)
		ft_putendl(g_commands[i++]);
}

void		write_exit(int n)
{
	char *msg[12];

	msg[0] = "usage: ft_ssl command [command opts] [command args]";
	msg[1] = "error: invalid command";
	msg[2] = "error: invalid flag(s)";
	msg[3] = "error: no input";
	msg[4] = "error: key is not in proper hex";
	msg[5] = "error: memory allocation failure";
	msg[6] = "error: can't encrypt [-e] (default) AND decrypt [-d]";
	msg[7] = "error: -i/-o require arguments";
	msg[8] = "error: key verification error - bad password read";
	msg[9] = "error: unable to open file; No such file/directory";
	msg[10] = "error: data not multiple of block length (8)";
	msg[11] = "error: missing input for key or initial vector";
	ft_putendl(msg[n]);
	write_usage();
	exit(EXIT_FAILURE);
}

void		write_output(char *output, t_data *data)
{
	char		*tmp;

	if (data->flags.a && !data->flags.d)
	{
		tmp = output;
		output = des_en_base64(tmp, data);
		free(tmp);
	}
	if (data->flags.p)
	{
		write(1, "key=", 4);
		ft_putendl(data->key_string);
	}
	write(data->output_fd, output, data->len);
	if (data->output_fd != 1)
		close(data->output_fd);
}
