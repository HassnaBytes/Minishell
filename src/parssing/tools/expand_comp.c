/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_comp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 04:41:00 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

char	*get_var_name(char *str)
{
	int		idx;
	char	*var_name;

	idx = 0;
	var_name = NULL;
	while (str[idx] && str[idx] != ' ' && str[idx] != '\t' && str[idx] != '\''
		&& str[idx] != '"' && str[idx] != '$' && (ft_isalnum(str[idx])
			|| str[idx] == '_'))
		var_name = append_str(var_name, str[idx++]);
	return (var_name);
}

int	get_char_pos(char *str, char c)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == c)
			return (idx);
		idx++;
	}
	return (-1);
}

char	*get_var(char *str, char **env)
{
	int		idx;
	char	*holder;
	int		idx2;

	idx = 0;
	while (env[idx])
	{
		idx2 = get_char_pos(env[idx], '=');
		holder = get_substr(env[idx], 0, idx2 - 1);
		if (ft_strncmp(str, holder, ft_strlen(holder)) == 0)
		{
			free(holder);
			return (env[idx]);
		}
		free(holder);
		idx++;
	}
	return (NULL);
}

void	exit_state(char **new_str)
{
	char	*holder;

	holder = ft_itoa(g_lb_data.exit_status);
	*new_str = ft_strjoin(*new_str, holder);
	free(holder);
}

char	*trim_value(char *str)
{
	char	*holder;

	holder = ft_strtrim(str, " \t");
	free(str);
	return (holder);
}
