/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:50:36 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 06:36:46 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	edit_env(t_env *env, char *key, char *value)
{
	t_env	*holder;

	holder = env;
	while (holder)
	{
		if (ft_strcmp(key, holder->key) == 0)
		{
			free(holder->value);
			if (value)
				holder->value = ft_strdup(value);
		}
		holder = holder->next;
	}
}

bool	does_env_exits(t_env *env, char *key)
{
	t_env	*holder;

	holder = env;
	while (holder)
	{
		if (ft_strcmp(holder->key, key) == 0)
			return (true);
		holder = holder->next;
	}
	return (false);
}

static bool	check_if_path_request_exist(char *str)
{
	if (!access(str, R_OK))
	{
		return (true);
	}
	else
		return (false);
}

void	check_request_access(t_commands *command, t_env *env,
		char holder2[PATH_MAX])
{
	if (!check_if_path_request_exist(command->arg[1]))
	{
		g_lb_data.exit_status = 1;
		print_errors(command->arg[1], "cd", strerror(errno));
		return ;
	}
	if (!does_env_exits(env, "OLDPWD"))
		add_node(env, "OLDPWD", getcwd(holder2, PATH_MAX));
	else
		edit_env(env, "OLDPWD", getcwd(holder2, PATH_MAX));
	chdir(command->arg[1]);
	edit_env(env, "PWD", getcwd(holder2, PATH_MAX));
	g_lb_data.exit_status = 0;
}

void	cd_cmd(t_commands *command, t_env *env)
{
	char	*holder;
	char	holder2[PATH_MAX];

	holder = find_path(env, "HOME");
	if (!holder && str2d_len(command->arg) == 1)
	{
		g_lb_data.exit_status = 1;
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return ;
	}
	if (str2d_len(command->arg) == 1)
	{
		if (!does_env_exits(env, "OLDPWD"))
			add_node(env, "OLDPWD", getcwd(holder2, PATH_MAX));
		else
			edit_env(env, "OLDPWD", getcwd(holder2, PATH_MAX));
		chdir(holder);
		edit_env(env, "PWD", getcwd(holder2, PATH_MAX));
		g_lb_data.exit_status = 0;
		return ;
	}
	check_request_access(command, env, holder2);
}
