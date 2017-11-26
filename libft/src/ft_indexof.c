/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_indexof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 00:36:23 by jchow             #+#    #+#             */
/*   Updated: 2017/11/04 00:36:23 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Searches the given char array for 2nd argument "c" and returns the index
** of the the match. If no match is found, 0 is returned.
*/

#include "libft.h"

int	ft_indexof(const char *s, int c)
{
	return (strchr(s, c) - s);
}
