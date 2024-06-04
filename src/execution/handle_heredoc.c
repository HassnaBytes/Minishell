/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:06:53 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	herdoc(t_commands *cmd, t_env *env)
{
	int	i;
	int	j;
	int	file;

	i = 0;
	file = -1;
	i = 0;
	while (i < cmd->commands_count)
	{
		j = 0;
		while (j < cmd[i].redir_count)
		{
			if (cmd[i].redir[j].type == 'H')
				file = handle_input_heredoc(&cmd[i], j,
						cmd[i].redir[j].file_out, env);
			j++;
		}
		i++;
	}
}

void	sigint_handler_child(int sig)
{
	(void)sig;
	g_lb_data.signal = 1;
	exit(99);
}

void	get_status_value(int *status, t_commands *cmd, int *index)
{
	if (((*(int *)&(*status)) & 0177) != 0177
		&& ((*(int *)&(*status)) & 0177) != 0)
		*status = (128 + ((*(int *)&(*status)) & 0177));
	if (((*(int *)&(*status)) & 0177) == 0)
		*status = ((*(int *)&(*status)) >> 8) & 0x000000ff;
	if (*status == 99)
	{
		g_lb_data.signal = 1;
		return ;
	}
	else
		g_lb_data.exit_status = 0;
	close(cmd->redir[*index].pipefd[1]);
}

int	handle_input_heredoc(t_commands *cmd, int index, char *del, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*line;

	line = NULL;
	cmd->redir->centent = NULL;
	createpipes(cmd, &index);
	pid = fork();
	if (pid == -1)
		handle_error_forking(cmd);
	else if (pid == 0)
	{
		signal(SIGINT, sigint_handler_child);
		close(cmd->redir[index].pipefd[0]);
		childp(&line, cmd, del);
		writepipe(cmd, &index, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(&status);
		get_status_value(&status, cmd, &index);
	}
	return ((cmd->redir[index].pipefd[0]));
}
