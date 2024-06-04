/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:07:19 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 01:01:53 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

size_t	count_commands(char *str, char c)
{
	size_t	counter;
	bool	double_quotes;
	bool	single_quotes;
	bool	trigger;
	int		idx;

	init_vars(&counter, &double_quotes, &single_quotes, &trigger);
	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '\'' && double_quotes)
			single_quotes = !single_quotes;
		else if (str[idx] == '"' && single_quotes)
			double_quotes = !double_quotes;
		if (double_quotes && single_quotes && trigger && str[idx] != c)
		{
			counter++;
			trigger = false;
		}
		else if (double_quotes && single_quotes && str[idx] == c)
			trigger = true;
		idx++;
	}
	return (counter);
}

size_t	count_letters(char *str, int idx, char c)
{
	size_t	counter;
	bool	double_quotes;
	bool	single_qoutes;
	int		i;

	init_vars(&counter, &double_quotes, &single_qoutes, NULL);
	i = 0;
	while (i < idx)
	{
		quotes_switcher(&single_qoutes, &double_quotes, str[i] == '\'',
			str[i] == '"');
		i++;
	}
	while (str[i])
	{
		quotes_switcher(&single_qoutes, &double_quotes, str[i] == '\'',
			str[i] == '"');
		if (double_quotes && single_qoutes && str[i] == c)
			break ;
		else
			counter++;
		i++;
	}
	return (counter);
}

void	init_insert_values(int *i, int *split_idx1, bool *single_quotes,
		bool *double_quotes)
{
	*i = 0;
	*split_idx1 = 0;
	*single_quotes = true;
	*double_quotes = true;
}

static void	insert_values(char **split, char *str, char c)
{
	bool	double_quotes;
	bool	single_quotes;
	int		split_idx1;
	int		split_idx2;
	int		i;

	init_insert_values(&i, &split_idx1, &single_quotes, &double_quotes);
	while (split_idx1 < (int)count_commands(str, c))
	{
		split_idx2 = 0;
		escape_chars(str, &i, c);
		while (str[i])
		{
			quotes_switcher(&single_quotes, &double_quotes, str[i] == '\'',
				str[i] == '"');
			if (double_quotes && single_quotes && str[i] == c)
			{
				i++;
				break ;
			}
			else
				split[split_idx1][split_idx2++] = str[i++];
		}
		split_idx1++;
	}
}

char	**split_pipe(char *str, char c)
{
	char			**split;
	size_t			commands_count;
	int				splitidx1;
	size_t			letters_count;
	unsigned int	stridx;

	commands_count = count_commands(str, c);
	split = ft_calloc(commands_count + 1, sizeof(char *));
	splitidx1 = 0;
	stridx = 0;
	while (splitidx1 < (int)commands_count)
	{
		while (str[stridx] == c)
			stridx++;
		letters_count = count_letters(str, stridx, c);
		split[splitidx1] = ft_calloc(letters_count + 1, 1);
		stridx += letters_count + 1;
		splitidx1++;
	}
	insert_values(split, str, c);
	return (split);
}
