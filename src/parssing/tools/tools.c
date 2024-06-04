/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 08:46:07 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/14 11:25:20 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

static void	ft_str3join_comp(char *str, char *s, int strindex)
{
	int	idx;

	idx = 0;
	while (s[idx])
		str[strindex++] = s[idx++];
}

char	*ft_str3join(char *s1, char *s2, char *s3)
{
	int		wordindex;
	char	*str;
	int		strindex;

	if (!s1)
		return (s2);
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + ft_strlen(s3) + 1, 1);
	wordindex = 0;
	strindex = 0;
	if (!str)
		return (0);
	while (s1[wordindex] != '\0')
		str[strindex++] = s1[wordindex++];
	wordindex = 0;
	while (s2[wordindex] != '\0')
		str[strindex++] = s2[wordindex++];
	ft_str3join_comp(str, s3, strindex);
	return (str);
}

void	escape_string(const char *input, int *idx)
{
	if (input[*idx] == '"')
	{
		(*idx)++;
		while (input[*idx] != '"')
			(*idx)++;
	}
	else if (input[*idx] == '\'')
	{
		(*idx)++;
		while (input[*idx] != '\'')
			(*idx)++;
	}
}

char	*get_first_word_quote_case(char *str, char quote, int idx)
{
	size_t	counter;
	char	*first_word;

	counter = 0;
	idx++;
	while (str[idx + counter] && str[idx + counter] != quote)
		counter++;
	if (counter == 0)
		return (NULL);
	first_word = ft_calloc(counter + 1, 1);
	if (!first_word)
		return (NULL);
	counter = 0;
	while (str[idx] && str[idx] != quote)
		first_word[counter++] = str[idx++];
	return (first_word);
}

char	*get_first_word(char *str)
{
	int		idx;
	size_t	counter;
	char	*first_word;

	idx = 0;
	counter = 0;
	while (str[idx] && (str[idx] == ' ' || str[idx] == '\t'))
		idx++;
	if (str[idx] == '"' || str[idx] == '\'')
		return (get_first_word_quote_case(str, str[idx], idx));
	while (str[idx + counter] && str[idx + counter] != ' ' && str[idx
			+ counter] != '\t')
		counter++;
	if (counter == 0)
		return (NULL);
	first_word = ft_calloc(counter + 1, 1);
	counter = 0;
	if (!first_word)
		return (NULL);
	while (str[idx] && str[idx] != ' ' && str[idx] != '\t')
		first_word[counter++] = str[idx++];
	return (first_word);
}
