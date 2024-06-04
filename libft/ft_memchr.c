/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 04:20:07 by sait-bah          #+#    #+#             */
/*   Updated: 2022/10/23 20:00:47 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*sv2;

	i = 0;
	sv2 = (unsigned char *) s;
	while (i < n)
	{
		if (sv2[i] == (unsigned char) c)
		{
			return (&sv2[i]);
		}
		i++;
	}
	return (0);
}
