/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 02:45:25 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 01:02:33 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

static char	*remove_pos(char *str, int pos)
{
	char	*new_str;
	int		new_str_idx;
	int		idx;

	new_str = calloc(strlen(str), 1);
	idx = 0;
	new_str_idx = 0;
	while (str[idx])
	{
		if (idx == pos)
		{
			idx++;
			continue ;
		}
		new_str[new_str_idx++] = str[idx++];
	}
	free(str);
	return (new_str);
}

void	remove_quote_from_str_comp(char **str, bool single_quotes,
		bool double_quotes, int *idx)
{
	if ((*str)[(*idx)] == '"' && single_quotes)
	{
		(*str) = remove_pos((*str), (*idx));
		while ((*str)[(*idx)] && (*str)[(*idx)] != '"')
			(*idx)++;
		if ((*str)[(*idx)] == '"')
			(*str) = remove_pos((*str), (*idx));
	}
	else if ((*str)[(*idx)] == '\'' && double_quotes)
	{
		(*str) = remove_pos((*str), (*idx));
		while ((*str)[(*idx)] && (*str)[(*idx)] != '\'')
			(*idx)++;
		if ((*str)[(*idx)] == '\'')
			(*str) = remove_pos((*str), (*idx));
	}
	else
		(*idx)++;
}

void	remove_quote_from_str(char **str, bool single_quotes,
		bool double_quotes)
{
	int		idx;

	idx = 0;
	while ((*str)[idx])
	{
		quotes_switcher(&single_quotes, &double_quotes, (*str)[idx] == '\''
			&& double_quotes, (*str)[idx] == '"' && single_quotes);
		remove_quote_from_str_comp(str, single_quotes, double_quotes, &idx);
	}
}

void	handle_quotes_comp(t_commands *commands, int idx)
{
	int	idx2;

	idx2 = 0;
	while (commands[idx].arg[idx2])
	{
		remove_quote_from_str(&commands[idx].arg[idx2], true, true);
		idx2++;
	}
}

void	handle_quotes(t_commands *commands)
{
	int	idx;
	int	idx2;

	idx = 0;
	while (idx < commands[0].commands_count)
	{
		if (commands[idx].command)
			remove_quote_from_str(&commands[idx].command, true, true);
		if (commands[idx].arg)
			handle_quotes_comp(commands, idx);
		if (commands[idx].redir)
		{
			idx2 = 0;
			while (idx2 < commands[idx].redir_count)
			{
				if (commands[idx].redir[idx2].file_out)
					remove_quote_from_str(&commands[idx].redir[idx2].file_out,
						true,
						true);
				idx2++;
			}
		}
		idx++;
	}
}
