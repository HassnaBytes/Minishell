/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 23:25:14 by sait-bah          #+#    #+#             */
/*   Updated: 2022/10/21 20:05:30 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclegnth;
	size_t	dstlength;
	size_t	i;
	size_t	res;

	if (dstsize == 0)
		return (ft_strlen(src));
	srclegnth = ft_strlen(src);
	dstlength = ft_strlen(dst);
	i = 0;
	if (dstsize > dstlength)
	res = srclegnth + dstlength;
	else
	res = srclegnth + dstsize;
	while (src[i] && (dstlength + 1) < dstsize)
	{
		dst[dstlength] = src[i];
		dstlength++;
		i++;
	}
	dst[dstlength] = '\0';
	return (res);
}
