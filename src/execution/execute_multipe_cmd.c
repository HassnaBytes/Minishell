/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multipe_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 10:29:36 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 06:30:20 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	create_pipes(t_commands *cmd, int **fd)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmd->commands_count - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			exit(EXIT_FAILURE);
		if (pipe(fd[i]) == -1)
		{
			ft_putstr_fd(strerror(errno), 2);
			j = 0;
			while (j < i)
			{
				close(fd[j][0]);
				close(fd[j][1]);
				j++;
			}
			g_lb_data.exit_status = 1;
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	if_have_error_in_fork(t_commands *cmd, int **fd, int num_commands)
{
	ft_putstr_fd("minishell: error in fork\n", STDERR_FILENO);
	close_child_pipe_fds(cmd, fd, num_commands - 1);
	g_lb_data.exit_status = 1;
	return ;
}

void	child_process(t_commands *cmds, int **pipes, int num_commands,
		t_env *env)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < num_commands)
	{
		pid = fork();
		g_lb_data.g_pid[i] = pid;
		if (pid == -1)
			if_have_error_in_fork(cmds, pipes, num_commands);
		if (pid == 0)
		{
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < num_commands - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			close_child_pipe_fds(cmds, pipes, num_commands - 1);
			exit(execute_command(&cmds[i], env));
		}
		i++;
	}
}

void	free_pipes(int **pipes, int num)
{
	int	i;

	i = 0;
	while (i < num - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	handle_multipe_command(t_commands *cmds, t_env *env_list)
{
	int	**pipes;
	int	num_commands;

	num_commands = cmds->commands_count;
	if (num_commands - 1 > 10240)
	{
		print_errors("bash", NULL, strerror(errno));
		g_lb_data.exit_status = 128;
		return ;
	}
	pipes = (int **)malloc(sizeof(int *) * (num_commands - 1) * 2);
	if (!pipes)
		exit(EXIT_FAILURE);
	create_pipes(cmds, pipes);
	g_lb_data.g_pid = malloc(sizeof(pid_t) * num_commands);
	child_process(cmds, pipes, num_commands, env_list);
	parent_process(cmds, pipes, num_commands);
	free_pipes(pipes, num_commands);
	free(g_lb_data.g_pid);
}
