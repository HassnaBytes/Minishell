/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1d_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 01:48:32 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static bool	check_redir_herdo_count(const char *input, char c, char c_rev)
{
	int	idx;
	int	count;
	int	idx2;

	idx = 0;
	count = 0;
	while (input[idx])
	{
		idx2 = 0;
		escape_string(input, &idx);
		while (input[idx + idx2] && input[idx + idx2] == c)
		{
			idx2++;
			count++;
		}
		if (input[idx] == c && input[idx + 1] == c_rev)
			return (false);
		if (count > 2)
			return (false);
		count = 0;
		idx++;
	}
	return (true);
}

bool	check_sequensial_redirs(const char *input, char c,
		bool single_quote, bool double_quote)
{
	int	idx;
	int	idx2;

	idx = 0;
	while (input[idx])
	{
		idx2 = 1;
		quotes_switcher(&single_quote, &double_quote, input[idx] == '\'',
			input[idx] == '"');
		if (input[idx] == c && single_quote && double_quote)
		{
			if (input[idx + 1] == c)
				idx++;
			while (input[idx + idx2] && input[idx + idx2] == ' ')
				idx2++;
			if (input[idx + idx2] == '>' || input[idx + idx2] == '<')
				return (false);
			idx += idx2;
		}
		idx++;
	}
	return (true);
}

bool	last_redir_check(const char *str, bool single_quotes,
		bool double_quotes, int idx)
{
	int	idx2;

	while (str[idx])
	{
		idx2 = 1;
		quotes_switcher(&single_quotes, &double_quotes, str[idx] == '\'',
			str[idx] == '"');
		if ((str[idx] == '>' || str[idx] == '<') && (single_quotes
				&& double_quotes))
		{
			if ((str[idx + 1] == '>' || str[idx + 1] == '<') && (single_quotes
					&& double_quotes))
				idx++;
			while (str[idx + idx2] && (str[idx + idx2] == ' ' || str[idx
						+ idx2] == '\t'))
				idx2++;
			if (str[idx + idx2] == '|')
				return (false);
			idx += idx2;
			continue ;
		}
		idx++;
	}
	return (true);
}

bool	check_1d_err(const char *input)
{
	if (!check_redirection_position(input))
	{
		g_lb_data.exit_status = 258;
		return (
			print_err("minishell: syntax error near unexpected token `>'\n"));
	}
	if (!check_redir_herdo_count(input, '>', '<'))
	{
		g_lb_data.exit_status = 258;
		return (
			print_err("minishell: syntax error near unexpected token `>'\n"));
	}
	if (!check_redir_herdo_count(input, '<', '>'))
	{
		g_lb_data.exit_status = 127;
		return (
			print_err("minishell: syntax error near unexpected token `<'\n"));
	}
	if (!check_1d_err_comp(input))
		return (false);
	return (true);
}
