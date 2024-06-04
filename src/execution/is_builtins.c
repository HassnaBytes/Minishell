/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 10:05:57 by houattou          #+#    #+#             */
/*   Updated: 2023/08/13 23:40:33 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	check_is_builtin(t_commands *cmd)
{
	int	len;

	if (cmd->command == NULL)
		return (-1);
	len = ft_strlen(cmd->command);
	if (!ft_strncmp(cmd->command, "echo", ft_max(len, 4)))
		return (ECHO);
	else if (!ft_strncmp(cmd->command, "env", ft_max(len, 3)))
		return (ENV);
	else if (!ft_strncmp(cmd->command, "pwd", ft_max(len, 3)))
		return (PWD);
	else if (!ft_strncmp(cmd->command, "unset", ft_max(len, 5)))
		return (UNSET);
	else if (!ft_strncmp(cmd->command, "exit", ft_max(len, 4)))
		return (EXIT);
	else if (!ft_strncmp(cmd->command, "cd", ft_max(len, 2)))
		return (CD);
	else if (!ft_strncmp(cmd->command, "export", ft_max(len, 6)))
		return (EXPORT);
	else
		return (NOT_BUILTIN);
}

void	execute_builtin(t_commands *cmd, t_env *env_list)
{
	int	builtin;

	if (cmd->command == NULL)
		return ;
	builtin = check_is_builtin(cmd);
	if (builtin == ECHO)
		echo_cmd(cmd);
	else if (builtin == CD)
		cd_cmd(cmd, env_list);
	else if (builtin == EXPORT)
		export_cmd(cmd, env_list);
	else if (builtin == UNSET)
		unset_cmd(cmd, env_list);
	else if (builtin == PWD)
		pwd_cmd();
	else if (builtin == ENV)
		env_cmd(env_list, cmd);
	else if (builtin == EXIT)
		exit_cmd(cmd);
}
