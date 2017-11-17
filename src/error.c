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
	char *msg[15];

	msg[0] = "usage: ft_ssl command [command opts] [command args]";
	msg[1] = "ft_ssl: Error: WHATEVER is an invalid command";
	msg[2] = "Invalid flag(s)";
	msg[3] = "LOL FILL IT L8r";
	msg[4] = "Too many arguments";
	msg[5] = "No input";
	msg[6] = "Can't encrypt [-e] (default) AND decrypt [-d]";
	msg[7] = "-i/-o require arguments";
	msg[8] = "Key verification error - bad password read";
	msg[9] = "Only enter one key";
	msg[10] = "Key is not in proper hex";
	msg[11] = "Memory allocation failure";
	msg[12] = "Unable to open file; No such file/directory";
	msg[13] = "Data not multiple of block length (8)";
	msg[14] = "Missing input for key or initial vector";
	ft_putendl(msg[n]);
	exit(EXIT_FAILURE);
}
