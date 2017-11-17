/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endians.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:17:58 by jchow             #+#    #+#             */
/*   Updated: 2017/11/17 00:24:12 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_des.h"

void	endian_switch64(uint64_t *n)
{
	uint64_t ret[8];
	uint64_t mask;

	mask = 255;
	ret[0] = *n >> 56;
	ret[1] = *n >> 40 & (mask << 8);
	ret[2] = *n >> 24 & (mask << 16);
	ret[3] = *n >> 8 & (mask << 24);
	ret[4] = *n << 8 & (mask << 32);
	ret[5] = *n << 24 & (mask << 40);
	ret[6] = *n << 40 & (mask << 48);
	ret[7] = *n << 56;
	*n = ret[0] | ret[1] | ret[2] | ret[3] | ret[4] | ret[5] | ret[6] | ret[7];
}

void	endian_switch32(uint32_t *n)
{
	uint32_t	ret[4];

	ret[0] = *n >> 24;
	ret[1] = (*n >> 8) & (255 << 8);
	ret[2] = (*n << 8) & (255 << 16);
	ret[3] = *n << 24;
	*n = ret[0] | ret[1] | ret[2] | ret[3];
}
