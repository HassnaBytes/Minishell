/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 23:49:33 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 01:01:15 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

unsigned int	count_appearance(const char *str, char c)
{
	unsigned int	counter;
	unsigned int	idx;

	counter = 0;
	idx = 0;
	while (str[idx])
	{
		if (str[idx] == c)
			counter++;
		idx++;
	}
	return (counter);
}

size_t	str2d_len(char **str)
{
	size_t	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

size_t	count_len_with_one_space(char *str)
{
	size_t			counter;
	unsigned int	idx;

	idx = 0;
	counter = 0;
	if (!str)
		return (0);
	while (str[idx])
	{
		if (str[idx] == ' ' || str[idx] == '\t')
		{
			counter++;
			while (str[idx] && (str[idx] == ' ' || str[idx] == '\t'))
				idx++;
			continue ;
		}
		counter++;
		idx++;
	}
	return (counter);
}

int	count_redir_for_alloc(char *str, bool double_quotes, bool single_quotes)
{
	int		count;
	int		idx;

	idx = 0;
	count = 0;
	while (str[idx])
	{
		quotes_switcher(&single_quotes, &double_quotes, str[idx] == '\'',
			str[idx] == '"');
		if (str[idx] == '>' && double_quotes && single_quotes)
			count_redir_for_alloc_comp(str, &idx, '>', &count);
		else if (str[idx] == '<' && single_quotes && double_quotes)
		{
			count_redir_for_alloc_comp(str, &idx, '<', &count);
		}
		else
			idx++;
	}
	return (count);
}

void	add_space_comp(char **new_str, int *idx,
	char *to_join, int to_increment)
{
	(*new_str) = ft_strjoin((*new_str), to_join);
	*idx += to_increment;
}
