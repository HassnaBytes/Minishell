/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:57:43 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/14 11:35:45 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

void	free_2d(char **str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		free(str[idx]);
		str[idx] = NULL;
		idx++;
	}
	free(str);
	str = NULL;
}

void	escape_chars(char *str, int *i, char c)
{
	while (str[(*i)] && str[(*i)] == c)
		(*i)++;
}

void	init_vars(size_t *counter, bool *double_quotes, bool *single_quotes,
		bool *trigger)
{
	if (counter != NULL)
		*counter = 0;
	if (double_quotes != NULL)
		*double_quotes = true;
	if (single_quotes != NULL)
		*single_quotes = true;
	if (trigger != NULL)
		*trigger = true;
}

char	**join_arr(char **arr, char *new)
{
	char	**new_arr;
	int		idx;

	idx = 0;
	if (!arr)
	{
		new_arr = ft_calloc(2, sizeof(char *));
		if (!new_arr)
			return (NULL);
		new_arr[0] = ft_strdup(new);
		return (new_arr);
	}
	else
	{
		new_arr = ft_calloc(str2d_len(arr) + 2, sizeof(char *));
		while (arr[idx])
		{
			new_arr[idx] = ft_strdup(arr[idx]);
			idx++;
		}
		new_arr[idx] = ft_strdup(new);
	}
	free_2d(arr);
	arr = NULL;
	return (new_arr);
}
