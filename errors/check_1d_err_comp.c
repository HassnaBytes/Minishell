/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_1d_err_comp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:57:18 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/libft.h"

bool	check_quotes(const char *input)
{
	int		idx;
	bool	double_state;
	bool	single_state;

	idx = 0;
	double_state = true;
	single_state = true;
	while (input[idx])
	{
		if (input[idx] == '"' && single_state == true)
			double_state = !double_state;
		else if (input[idx] == '\'' && double_state == true)
			single_state = !single_state;
		idx++;
	}
	return (single_state && double_state);
}

bool	check_redirection_position(const char *input)
{
	int		len;
	char	*trimed_str;
	bool	res;

	res = true;
	trimed_str = ft_strtrim(input, " \t");
	len = ft_strlen(trimed_str);
	if (trimed_str[len - 1] == '>' || trimed_str[len - 1] == '<')
		res = false;
	free(trimed_str);
	return (res);
}

bool	check_1d_err_comp(const char *input)
{
	if (!check_quotes(input))
	{
		g_lb_data.exit_status = 258;
		return (
			print_err("minishell: unexpected EOF while looking for matching\n"));
	}
	if (!check_sequensial_redirs(input, '>', true, true))
		return (
			print_err("minishell: syntax error near unexpected token `>'\n"));
	if (!check_sequensial_redirs(input, '<', true, true))
	{
		g_lb_data.exit_status = 258;
		return (
			print_err("minishell: syntax error near unexpected token `<'\n"));
	}
	if (!last_redir_check(input, true, true, 0))
	{
		g_lb_data.exit_status = 258;
		return (
			print_err("minishell: syntax error near unexpected token `|'\n"));
	}
	return (true);
}
