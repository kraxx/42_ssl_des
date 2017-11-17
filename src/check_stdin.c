/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 18:29:05 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:23:14 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

void	get_input_from_stdin(void)
{
	int		ret;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	while ((ret = read(0, buf, BUFF_SIZE)) > 0)
	{
		if (!g_string)
			g_string = ft_strnew(0);
		buf[ret] = 0;
		tmp = g_string;
		g_string = ft_strjoin(tmp, buf);
		free(tmp);
	}
	if (!g_string)
		write_exit(3);
}

void	get_vector_from_stdin(void)
{
	int		ret;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	write(1, "Enter initial vector: ", 22);
	while ((ret = read(0, buf, BUFF_SIZE)) > 0)
	{
		if (!g_init_vector)
			g_init_vector = ft_strnew(0);
		buf[ret] = 0;
		tmp = g_init_vector;
		g_init_vector = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
		{
			*ft_strchr(g_init_vector, '\n') = 0;
			break ;
		}
	}
	if (!g_init_vector)
		write_exit(3);
}

void	get_key_from_stdin(void)
{
	g_key_string = ft_strdup(getpass("Enter des key in hex "));
	if (!ft_strcmp(g_key_string, ""))
		write_exit(4);
	if (ft_strcmp(g_key_string, getpass("Verifying - enter des key in hex: ")))
		write_exit(8);
}
