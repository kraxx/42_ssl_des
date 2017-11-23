/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:04:13 by jchow             #+#    #+#             */
/*   Updated: 2017/11/22 18:40:47 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

void	read_input_from_file(char *str, t_data *data)
{
	int		fd;
	int		ret;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	free(data->input);
	if (!(data->input = ft_strnew(0)))
		write_exit(5);
	fd = open(str, O_RDONLY);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		tmp = ft_strnjoin(data->input, buf, data->len, ret);
		free(data->input);
		data->input = tmp;
		data->len += ret;
	}
	if (ret < 0)
		data->flags.badread = 1;
	close(fd);
	data->flags.i = 0;
}

int		validate_hex(char *s, int len)
{
	while (len--)
		if (!ft_ishex(s[len]))
			return (0);
	return (1);
}

char	*string_truncate(char *str, int bytes)
{
	int		len;
	char	*ret;

	len = ft_strlen(str);
	if (!validate_hex(str, len))
		write_exit(4);
	if (!(ret = ft_strnew(bytes)))
		write_exit(5);
	if (len < bytes)
	{
		ft_strncpy(ret, str, len);
		ft_memset(ret + len, '0', bytes - len);
	}
	else
		ft_strncpy(ret, str, bytes);
	free(str);
	return (ret);
}

char	*allocate_output_and_proc_de_base64(t_data *data)
{
	char	*ret;

	if (data->flags.a && data->flags.d)
		des_de_base64(data);
	if (data->flags.nopad)
		ret = ft_strnew(data->len + (data->len % 8 ? 8 - (data->len % 8) : 0));
	else
		ret = ft_strnew(data->len + (data->len % 8 ? 8 - (data->len % 8) : 8));
	return (ret);
}
