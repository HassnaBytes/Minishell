/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 04:42:56 by sait-bah          #+#    #+#             */
/*   Updated: 2022/10/17 21:41:34 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void	*src, size_t	len)
{
	size_t	i;
	char	*dest_char;
	char	*src_char;

	i = 0;
	dest_char = (char *) dest;
	src_char = (char *) src;
	if (dest_char > src_char)
	{
		while (len-- > 0)
			dest_char[len] = src_char[len];
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
