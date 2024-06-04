/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_comp_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 04:57:02 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 01:03:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

void	expand_case(char *str, int *idx, char *var_name)
{
	(*idx)++;
	while (ft_isalnum(str[(*idx)]) || str[(*idx)] == '_')
		(*idx)++;
	free(var_name);
	var_name = NULL;
}

void	expand_init(t_expand_data *data, t_env *env)
{
	(*data).idx = 0;
	(*data).new_str = NULL;
	(*data).var_name = NULL;
	(*data).double_quotes = true;
	(*data).env = env;
}

void	expand_second(char **var_name, t_env *env, char **holder,
		char **new_str)
{
	*holder = ft_strdup(find_path(env, *var_name));
	*holder = trim_value(*holder);
	*new_str = ft_strjoin(*new_str, *holder);
	free(*holder);
	*holder = NULL;
	free(*var_name);
	*var_name = NULL;
}

void	expand_handle_dollar_dollar(t_expand_data *data)
{
	data->new_str = ft_strjoin(data->new_str, "$$");
	data->idx += 2;
}

void	expand_first_condition(t_expand_data *data, char **str, t_env *env)
{
	data->var_name = get_var_name(&(*str)[data->idx + 1]);
	if (!data->var_name)
		data->idx++;
	else if (find_path(env, data->var_name) == NULL)
		expand_case(*str, &data->idx, data->var_name);
	else
	{
		data->idx += ft_strlen(data->var_name) + 1;
		expand_second(&data->var_name, env, &data->holder, &data->new_str);
	}
}
