/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:44:30 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	execute_bin_and_builtin_cmd(t_commands *cmd, int fd, t_env *env_list)
{
	int	builtin;

	if (cmd->command != NULL && fd != -1)
	{
		builtin = check_is_builtin(cmd);
		if (builtin != NOT_BUILTIN)
			execute_builtin(cmd, env_list);
		else
			execute_bin_cmd(cmd, env_list);
	}
	if (fd != 0)
		close(fd);
}

int	execute_command(t_commands *cmd, t_env *env_list)
{
	int	fd;
	int	save_in;
	int	save_out;

	fd = 0;
	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (cmd->redir_count > 0)
		check_type_of_redirection(cmd, &fd);
	execute_bin_and_builtin_cmd(cmd, fd, env_list);
	dup2(save_out, STDOUT_FILENO);
	dup2(save_in, STDIN_FILENO);
	return (g_lb_data.exit_status);
}

void	execute(t_commands *cmd, t_env *data)
{
	herdoc(cmd, data);
	if (g_lb_data.signal == 1)
		g_lb_data.exit_status = 1;
	if (g_lb_data.signal == 0)
	{
		if (cmd->commands_count == 1)
			execute_command(cmd, data);
		else
			handle_multipe_command(cmd, data);
	}
	g_lb_data.signal = 0;
}
