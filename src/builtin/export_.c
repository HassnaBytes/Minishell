/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:37:15 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 01:43:16 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

bool	is_valid_key(const char *arg)
{
	int	i;

	if (!arg || (arg[0] != '_' && !is_alpha(arg[0])) || arg[0] == '='
		|| arg[0] == '$' || arg[0] == '>' || arg[0] == '<' || arg[0] == 32
		|| arg[0] == 9)
		return (0);
	i = 1;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (!(is_number(arg[i]) || is_alpha(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	handle_invalid_key(char *arg)
{
	print_errors("export", arg, "not a valid identifier");
	g_lb_data.exit_status = 1;
}

void	extract_key_value(char *arg, char **key, char **value)
{
	int	j;

	*key = NULL;
	*value = NULL;
	j = 0;
	while (arg[j] != '\0')
	{
		if (arg[j] == '=')
		{
			*key = ft_substr(arg, 0, j);
			*value = ft_strdup(arg + j + 1);
			break ;
		}
		j++;
	}
}

void	create_export_command(t_commands *cmd, t_env **env_list)
{
	int	i;

	i = 1;
	while (cmd->arg[i] != NULL)
	{
		export_argument(cmd->arg[i], env_list);
		i++;
	}
}

void	export_cmd(t_commands *cmd, t_env *env_list)
{
	if (!cmd->arg[1])
		add_declare_to_env(env_list);
	else
		create_export_command(cmd, &env_list);
}
