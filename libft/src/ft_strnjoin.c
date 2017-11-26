/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 21:30:20 by jchow             #+#    #+#             */
/*   Updated: 2017/11/20 21:30:21 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Technically used for non-strings. Allocates space for both char buffers and
** returns the two joined as a single array.
*/

#include "libft.h"

char	*ft_strnjoin(const char *s1, const char *s2, size_t l1, size_t l2)
{
	char	*mem;
	size_t	i;

	i = 0;
	mem = ft_strnew(l1 + l2);
	if (!mem)
		return (NULL);
	while (i < l1)
		mem[i++] = *s1++;
	while (i < l1 + l2)
		mem[i++] = *s2++;
	mem[i] = '\0';
	return (mem);
}
