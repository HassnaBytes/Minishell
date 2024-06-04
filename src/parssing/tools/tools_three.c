/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:30:07 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/14 11:34:52 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

bool	redir_check(char *str)
{
	int		idx;
	bool	single_quote;
	bool	double_quote;

	idx = 0;
	single_quote = true;
	double_quote = true;
	while (str[idx])
	{
		if (str[idx] == '\'')
			single_quote = !single_quote;
		if (str[idx] == '"')
			double_quote = !double_quote;
		if ((str[idx] == '>' || str[idx] == '<') && (double_quote
				&& single_quote))
			return (true);
		idx++;
	}
	return (false);
}

char	*put_char_in_pos(char *str, int c, int pos)
{
	int		idx;
	char	*new_str;
	int		new_str_idx;

	new_str = ft_calloc(ft_strlen(str) + 2, 1);
	if (!new_str)
		return (NULL);
	new_str_idx = 0;
	idx = 0;
	while (str[idx])
	{
		if (idx == pos)
		{
			new_str[new_str_idx++] = c;
			pos = -1;
		}
		else
			new_str[new_str_idx++] = str[idx++];
	}
	if (idx == pos)
		new_str[idx] = c;
	return (new_str);
}

char	**remove_first_pos_2d_arr(char **str)
{
	char	**arr;
	int		idx;
	int		arr_idx;

	arr = ft_calloc(str2d_len(str), sizeof(char *));
	if (!arr)
		return (NULL);
	idx = 1;
	arr_idx = 0;
	while (str[idx])
		arr[arr_idx++] = ft_strdup(str[idx++]);
	free_2d(str);
	return (arr);
}

void	quotes_switcher(bool *single_quotes, bool *double_quotes,
		bool single_case, bool double_case)
{
	if (single_case)
		*single_quotes = !*single_quotes;
	if (double_case)
		*double_quotes = !*double_quotes;
}

char	*get_substr(char *str, int start, int end)
{
	size_t	len;
	int		idx;
	int		idx2;
	char	*res;

	len = (size_t)(end - start);
	idx = 0;
	idx2 = 0;
	res = ft_calloc(len + 2, 1);
	if (!res)
		return (NULL);
	while (str[start] && str[start] && start <= end)
		res[idx2++] = str[start++];
	return (res);
}
