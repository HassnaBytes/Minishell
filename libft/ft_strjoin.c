/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 03:26:57 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/11 20:24:41 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		wordindex;
	char	*str;
	int		strindex;

	if (!s1)
		s1 = ft_calloc(1, 1);
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, 1);
	wordindex = 0;
	strindex = 0;
	if (!str)
		return (0);
	while (s1[wordindex] != '\0')
	{
		str[strindex] = s1[wordindex++];
		strindex++;
	}
	wordindex = 0;
	while (s2[wordindex] != '\0')
	{
		str[strindex] = s2[wordindex++];
		strindex++;
	}
	free(s1);
	return (str);
}
