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

int		g_output_fd = 1;
char	*g_string = NULL;
char	*g_key_string = NULL;
char	*g_init_vector = NULL;
t_flags	g_flags;

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
		write_exit(10);
	while (len < 16)
	{
		tmp = ft_strdup(str);
		if (!(str = ft_strjoin(tmp, tmp)))
			write_exit(11);
		free(tmp);
		len *= 2;
	}
	if (len > 16)
	{
		if (!(tmp = ft_strsub(str, 0, 16)))
			write_exit(11);
		str = tmp;
		free(tmp);
	}
	return (str);
}

int		parse_command(char *cmd)
{
	int	i;

	i = -1;
	while (++i < CMD_COUNT)
		if (!ft_strcmp(cmd, g_commands[i]))
			return (i);
	write_exit(1);
	return (-42);
}

int		main(int ac, char **av)
{
	int	cmd_index;

	if (ac < 2)
		write_exit(0);
	cmd_index = parse_command(av[1]);
	ft_bzero(&g_flags, sizeof(t_flags));
	g_cmd_fp[cmd_index](ac, av);
	return (0);
}
