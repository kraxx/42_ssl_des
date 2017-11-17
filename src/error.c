/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 23:16:16 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:25:41 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	write_exit(int n)
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
	exit(EXIT_FAILURE);
}
