/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:12:39 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 01:03:57 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

void	expand_third_condition(t_expand_data *data)
{
	data->new_str = append_str(data->new_str, '$');
	data->idx++;
}

void	expand_second_condition(t_expand_data *data)
{
	data->idx += 2;
}

void	expand_exit_state(t_expand_data *data)
{
	exit_state(&data->new_str);
	data->idx += 2;
}

void	expand_default_case(t_expand_data *data, char *str)
{
	data->new_str = append_str(data->new_str, str[data->idx]);
	data->idx++;
}

char	*expand(char *str, t_env *env, bool single_quotes, bool heredoc)
{
	t_expand_data	data;

	expand_init(&data, env);
	while (str[data.idx])
	{
		if (!heredoc)
			quotes_switcher(&single_quotes, &data.double_quotes,
				str[data.idx] == '\'', str[data.idx] == '"');
		if (str[data.idx] == '$' && str[data.idx + 1] == '$')
			expand_handle_dollar_dollar(&data);
		else if (first_condition(str, data.idx, single_quotes))
			expand_first_condition(&data, &str, env);
		else if (third_condition(str, data.idx))
			expand_third_condition(&data);
		else if (second_condition(str, data.idx))
			expand_second_condition(&data);
		else if (str[data.idx] == '$' && str[data.idx + 1] == '?'
			&& single_quotes)
			expand_exit_state(&data);
		else
			expand_default_case(&data, str);
	}
	free(str);
	str = NULL;
	return (data.new_str);
}
