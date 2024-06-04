/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:18:26 by houattou          #+#    #+#             */
/*   Updated: 2023/08/12 19:13:11 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

char	*my_strjoin(char *s1, char *s2)
{
	int		wordindex;
	char	*str;
	int		strindex;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
	}
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
	return (str);
}
