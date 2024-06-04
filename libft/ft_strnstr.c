/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:37:22 by sait-bah          #+#    #+#             */
/*   Updated: 2022/10/23 20:10:29 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needlelength;
	size_t	needleindex;

	i = 0;
	needleindex = 0;
	needlelength = ft_strlen(needle);
	if (needlelength == 0 || haystack == needle)
		return ((char *) haystack);
	while (haystack[i] && i < len)
	{
		needleindex = 0;
		while (haystack[i + needleindex] && needle[needleindex]
			&& haystack[i + needleindex] == needle[needleindex]
			&& i + needleindex < len)
			needleindex++;
		if (needleindex == needlelength)
			return ((char *) haystack + i);
		i++;
	}
	return (0);
}
