/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 04:18:49 by sait-bah          #+#    #+#             */
/*   Updated: 2022/10/23 19:54:28 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (((char *)str)[i] == (char)c)
			return (&((char *) str)[i]);
		i++;
	}
	if ((char )c == '\0')
		return (&((char *) str)[i]);
	return (0);
}
