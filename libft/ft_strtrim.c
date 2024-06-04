/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 04:32:28 by sait-bah          #+#    #+#             */
/*   Updated: 2022/10/17 21:42:39 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*p;
	int		pindex;

	if (!s1)
		return (0);
	start = 0;
	end = ft_strlen(s1);
	pindex = 0;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	p = ft_calloc((end - start) + 1, 1);
	if (!p)
		return (0);
	while (start < end)
	{
		p[pindex] = s1[start];
		pindex++;
		start++;
	}
	p[pindex] = '\0';
	return (p);
}
