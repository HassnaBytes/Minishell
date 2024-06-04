/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 23:54:34 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/14 10:10:58 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

bool	first_condition(char *str, int idx, bool single_quotes)
{
	return (str[idx] == '$' && str[idx + 1] != '$' && str[idx + 1] != '?'
		&& str[idx + 1] != '\0' && str[idx + 1] != ' '
		&& str[idx + 1] != '\t'
		&& (ft_isalpha(str[idx + 1]) || str[idx + 1] == '_') && single_quotes);
}

bool	second_condition(char *str, int idx)
{
	return ((str[idx] == '$' && ft_isdigit(str[idx + 1]))
		|| (str[idx] == '$'
			&& !ft_isalpha(str[idx + 1]) && str[idx + 1] != '?'));
}

bool	third_condition(char *str, int idx)
{
	return (str[idx] == '$' && (str[idx + 1] == ' '
			|| str[idx + 1] == '\t' || str[idx + 1] == '\0'));
}

void	add_special_char_comp(bool *trigger, char **new_str, char *to_join)
{
	if (*trigger)
		*new_str = append_str(*new_str, 11);
	else
		*trigger = true;
	*new_str = ft_strjoin(*new_str, to_join);
}

void	init_add_special_char(t_add_special *data)
{
	(*data).new_str = NULL;
	(*data).idx = 0;
	(*data).trigger = false;
	(*data).double_quotes = true;
	(*data).single_quotes = true;
}
