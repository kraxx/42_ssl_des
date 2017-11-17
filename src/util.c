/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 23:04:13 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:26:16 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

void	set_g_string(char *str)
{
	int		fd;
	int		ret;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	if (g_string)
		free(g_string);
	if (!(g_string = ft_strnew(0)))
		write_exit(5);
	fd = open(str, O_RDONLY);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = 0;
		tmp = g_string;
		g_string = ft_strjoin(tmp, buf);
		free(tmp);
	}
	if (ret < 0)
		g_flags.badread = 1;
	close(fd);
	g_flags.i = 0;
}

void	process_keys(uint64_t k[])
{
	uint32_t c[17];
	uint32_t d[17];
	uint64_t key;

	key = ft_atoull_base(g_key_string, 16);
	key = permutate(key, g_pc1, 56, MASK_64);
	c[0] = key >> 32 & 0xFFFFFFF0;
	d[0] = key >> 4 & 0xFFFFFFF0;
	if (g_flags.d)
		generate_subkeys_de(c, d);
	else
		generate_subkeys_en(c, d);
	generate_16keys(c, d, k);
}

int		validate_hex(char *s, int len)
{
	while (len--)
		if (!ft_ishex(s[len]))
			return (0);
	return (1);
}

char	*string_64bits(char *str)
{
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	if (!validate_hex(str, len))
		write_exit(4);
	while (len < 16)
	{
		tmp = ft_strdup(str);
		if (!(str = ft_strjoin(tmp, tmp)))
			write_exit(5);
		free(tmp);
		len *= 2;
	}
	if (len > 16)
	{
		if (!(tmp = ft_strsub(str, 0, 16)))
			write_exit(5);
		str = tmp;
		free(tmp);
	}
	return (str);
}
