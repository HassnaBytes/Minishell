/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:32:12 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 06:32:00 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	execv_function(t_commands *cmd, char *path)
{
	signal(SIGQUIT, handle_child_signals);
	signal(SIGINT, handle_child_signals);
	execve(path, cmd[0].arg, cmd->environment);
	if (errno == 14)
		print_errors("bash", cmd->command, "command not found");
	else
		print_errors("bash", cmd->command, strerror(errno));
	g_lb_data.exit_status = 127;
	exit(g_lb_data.exit_status);
}

int	get_value_of_status(int status)
{
	if (((*(int *)&(status)) & 0177) != 0177
		&& ((*(int *)&(status)) & 0177) != 0)
		status = (128 + ((*(int *)&(status)) & 0177));
	if (((*(int *)&(status)) & 0177) == 0)
		status = (((*(int *)&(status)) >> 8) & 0x000000ff);
	return (status);
}

int	prepare_cmd(t_commands *cmd, char *path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("bash: Error in fork: ", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		signal(SIGQUIT, handle_child_signals);
		execv_function(cmd, path);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_lb_data.exit_status = get_value_of_status(status);
		if (g_lb_data.exit_status == 131)
			ft_putstr_fd("Quit: 3\n", 1);
		return (g_lb_data.exit_status);
	}
	return (g_lb_data.exit_status);
}

void	execute_bin_cmd(t_commands *cmd, t_env *env_list)
{
	char	*path;
	char	*get_path;

	path = NULL;
	get_path = NULL;
	if (cmd->command == NULL)
		return ;
	if (ft_strchr(cmd->command, '/'))
	{
		path = cmd->command;
	}
	else
	{
		get_path = find_path(env_list, "PATH");
		if (get_path == NULL)
		{
			path = my_strjoin("./", cmd->command);
			free(path);
		}
		else
			path = find_cmd_path(cmd, get_path);
	}
	g_lb_data.exit_status = prepare_cmd(cmd, path);
}
