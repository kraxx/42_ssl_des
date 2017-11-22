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

static void	parse_opts_base64(char *str, t_data *data)
{
	if (data->flags.o)
	{
		if (data->output_fd != 1)
			close(data->output_fd);
		data->output_fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		data->flags.o = 0;
	}
	else if (data->flags.i || !data->input)
		read_input_from_file(str, data);
}

static void	parse_flags_base64(char *str, t_data *data)
{
	if (!(*(str + 1)))
		write_exit(2);
	while (*(++str))
	{
		if (*str == 'e')
			data->flags.e = 1;
		else if (*str == 'd' || *str == 'D')
			data->flags.d = 1;
		else if (*str == 'i')
		{
			data->flags.i = 1;
			data->flags.o = 0;
		}
		else if (*str == 'o' && !data->flags.i)
			data->flags.o = 1;
		else
			write_exit(2);
		if (data->flags.e && data->flags.d)
			write_exit(6);
	}
}

static void	parse_args_base64(int ac, char **av, t_data *data)
{
	int i;

	i = 1;
	while (++i < ac)
	{
		if (*av[i] == '-')
			parse_flags_base64(av[i], data);
		else
			parse_opts_base64(av[i], data);
	}
	if (data->flags.i || data->flags.o)
		write_exit(7);
	if (data->flags.badread && !ft_strlen(data->input))
		write_exit(9);
	if (!data->input)
		get_input_from_stdin(data);
}

void		ft_base64(int ac, char **av, t_data *data)
{
	char	*output;

	parse_args_base64(ac, av, data);
	if (data->flags.d)
		output = de_base64(data->input, data->len, data);
	else
		output = en_base64(data->input, data->len, data);
	write(data->output_fd, output, data->len);
	free(output);
	if (data->output_fd != 1)
		close(data->output_fd);
}
