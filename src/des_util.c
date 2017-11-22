/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 03:25:26 by jchow             #+#    #+#             */
/*   Updated: 2017/11/22 03:25:28 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

uint64_t	des_string_to_buffer(size_t len, int i, t_data *data)
{
	t_64bits buf;

	if (len - i >= 8)
		ft_memcpy(&buf.ll, data->input + i, 8);
	else
	{
		if (data->flags.nopad)
			buf.ll = 0;
		else if (!data->flags.d)
		{
			ft_memset(&buf.c[len - i], 8 - (len - i), 8 - (len - i));
			data->len += (8 - (len - i));
		}
		ft_memcpy(&buf.ll, data->input + i, len - i);
	}
	return (buf.ll);
}

void		des_remove_padding(char *output, t_data *data)
{
	char	n;
	char	i;

	n = output[data->len - 1];
	i = -1;
	if (n < 9)
		while (++i < n)
		{
			if (output[data->len - 1 - i] != n)
				break ;
			else if (i == n - 1)
			{
				output[data->len - n] = 0;
				data->len -= n;
			}
		}
}
