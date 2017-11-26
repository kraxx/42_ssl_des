/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchow <jchow@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 03:18:42 by jchow             #+#    #+#             */
/*   Updated: 2017/07/28 03:18:43 by jchow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Errors on number strings followed by non-numeric characters.
*/

#include "libft.h"

int	ft_atoi_strict(char *s)
{
	return (ft_numsize(ft_atoi(s), 10) == (int)ft_strlen(s));
}
