/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:07:19 by sait-bah          #+#    #+#             */
/*   Updated: 2023/01/02 01:12:21 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordscounter(const char *str, char c)
{
	int		i;
	size_t	counter;
	int		countertrigger;

	i = 0;
	counter = 0;
	countertrigger = 1;
	while (str[i] != '\0')
	{
		if (str[i] != c && countertrigger == 1)
		{
			counter++;
			countertrigger = 0;
		}
		else if (str[i] == c)
		{
			countertrigger = 1;
		}
		i++;
	}
	return (counter);
}

static int	wordcount(char const *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] != c && s[i])
	{
		count++;
		i++;
	}
	return (count);
}

static void	insertvalues(char **str, const char *s, char c, int wordscount)
{
	int	sindex;
	int	str1dindex;
	int	str2dindex;

	sindex = 0;
	str1dindex = 0;
	while (str1dindex < wordscount)
	{
		str2dindex = 0;
		while (s[sindex] == c)
			sindex++;
		while (s[sindex] != c && s[sindex])
			str[str1dindex][str2dindex++] = s[sindex++];
		str[str1dindex][str2dindex] = 0;
		str1dindex++;
	}
	str[str1dindex] = 0;
}

char	**ft_split(char const *s, char c)
{
	int			sindex;
	char		**str;
	size_t		strindex;
	int			charcount;

	sindex = 0;
	strindex = 0;
	if (!s)
		return (0);
	str = ft_calloc(wordscounter(s, c) + 1, sizeof(char *));
	if (!str)
		return (0);
	while (strindex < wordscounter(s, c))
	{
		while (s[sindex] == c)
			sindex++;
		charcount = wordcount(s, c, sindex);
		str[strindex++] = ft_calloc(charcount + 1, 1);
		if (!str[strindex - 1])
			return (0);
		sindex += charcount;
	}
	insertvalues(str, s, c, wordscounter(s, c));
	return (str);
}
