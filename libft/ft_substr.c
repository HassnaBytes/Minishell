/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 03:17:57 by sait-bah          #+#    #+#             */
/*   Updated: 2022/10/24 21:48:25 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	s_i;
	char			*p;
	size_t			p_i;

	s_i = 0;
	p_i = 0;
	if (len > ft_strlen (s))
		p = ft_calloc(ft_strlen (s) + 1, 1);
	else
		p = ft_calloc(len + 1, 1);
	if (!p || !s)
		return (0);
	while (s[s_i] != '\0')
	{
		if (s_i >= start && p_i < len)
		{
			p[p_i] = ((char *)s)[s_i];
			p_i++;
		}
		s_i++;
	}
	return (p);
}
