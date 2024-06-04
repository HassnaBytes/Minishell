/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:56:26 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

static bool	check_pipe_position(const char *input,
	bool single_quote, bool double_quote, int idx)
{
	char	*trim_str;

	trim_str = ft_strtrim(input, " \t");
	if (trim_str[0] == '|' || trim_str[ft_strlen(trim_str) - 1] == '|')
	{
		free(trim_str);
		return (false);
	}
	while (trim_str[idx])
	{
		if ((trim_str[idx] == '|' && trim_str[idx + 1] == '|') && (single_quote
				&& double_quote))
		{
			free(trim_str);
			return (false);
		}
		quotes_switcher(&single_quote, &double_quote,
			trim_str[idx] == '\'', trim_str[idx] == '"');
		idx++;
	}
	free(trim_str);
	trim_str = NULL;
	return (true);
}

static bool	check_pipe_position2(const char *input)
{
	int		idx;
	bool	single_quote;
	bool	double_quote;
	bool	should;

	single_quote = true;
	double_quote = true;
	should = true;
	idx = 0;
	while (input[idx])
	{
		quotes_switcher(&single_quote,
			&double_quote, input[idx] == '\'', input[idx] == '"');
		if (input[idx] == '|' && single_quote && double_quote)
		{
			idx++;
			while (input[idx] && (input[idx] == ' ' || input[idx] == '\t'))
				idx++;
			if (input[idx] == '|')
				return (false);
		}
		idx++;
	}
	return (true);
}

bool	check_user_input(const char *input)
{
	bool	res;

	res = true;
	if (!check_pipe_position(input, true, true, 0)
		|| !check_pipe_position2(input))
	{
		g_lb_data.exit_status = 258;
		return (print_err("bash: syntax error near unexpected token `|'\n"));
	}
	if (!check_1d_err(input))
		res = false;
	return (res);
}
