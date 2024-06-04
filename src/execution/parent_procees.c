/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_procees.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:51:16 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	wait_for_children(t_commands *cmd)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < cmd->commands_count)
	{
		waitpid(g_lb_data.g_pid[i], &status, 0);
		i++;
	}
	if (((*(int *)&(status)) & 0177) != 0177
		&& ((*(int *)&(status)) & 0177) != 0)
		status = (128 + ((*(int *)&(status)) & 0177));
	if (((*(int *)&(status)) & 0177) == 0)
		status = (((*(int *)&(status)) >> 8) & 0x000000ff);
	g_lb_data.exit_status = status;
}

void	close_child_pipe_fds(t_commands *cmd, int **fd, int num_commands)
{
	int	i;

	i = 0;
	(void)cmd;
	while (i < num_commands)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	parent_process(t_commands *cmd, int **fd, int num)
{
	close_child_pipe_fds(cmd, fd, num - 1);
	wait_for_children(cmd);
}
