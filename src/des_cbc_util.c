/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 02:48:18 by jchow             #+#    #+#             */
/*   Updated: 2017/11/22 02:48:19 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

static void	parse_opts_des_cbc_2(char *str, t_data *data)
{
	if (data->flags.v)
	{
		free(data->init_vector);
		if (!(data->init_vector = ft_strdup(str)))
			write_exit(5);
		data->flags.v = 0;
	}
	else if (data->flags.k)
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
	else if ((data->flags.i || !data->input) &&
			!data->flags.k && !data->flags.v)
		read_input_from_file(str, data);
}

void		parse_opts_des_cbc(char *str, t_data *data)
{
	if (data->flags.v && data->flags.k)
		write_exit(11);
	parse_opts_des_cbc_2(str, data);
}

void		des_cbc_xor_vector_en(uint64_t *buf, uint64_t *buf_prev,
								uint64_t *vector, t_data *data)
{
	if (data->flags.d)
		*buf_prev = *buf;
	else
		*buf ^= *vector;
}

void		des_cbc_xor_vector_de(uint64_t *buf, uint64_t *buf_prev,
								uint64_t *vector, t_data *data)
{
	if (data->flags.d)
	{
		*buf ^= *vector;
		*vector = *buf_prev;
	}
	else
		*vector = *buf;
}
