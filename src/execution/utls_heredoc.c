/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:00:49 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	childp(char **line, t_commands *cmd, char *del)
{
	while (1)
	{
		if (g_lb_data.signal == 1)
			break ;
		*line = readline("> ");
		if (*line == NULL)
		{
			break ;
			exit(0);
		}
		if (ft_strcmp(*line, del) == 0)
		{
			free(*line);
			return ;
			break ;
		}
		cmd->redir->centent = ft_strjoin(cmd->redir->centent, *line);
		cmd->redir->centent = ft_strjoin(cmd->redir->centent, "\n");
		free(*line);
	}
}

void	writepipe(t_commands *cmd, int *index, t_env *env)
{
	if (cmd->should_expand_heredoc)
	{
		cmd->redir->centent = expand(cmd->redir->centent, env, true, true);
	}
	write(cmd->redir[*index].pipefd[1], cmd->redir->centent, \
		ft_strlen(cmd->redir->centent));
	close(cmd->redir[*index].pipefd[1]);
}

void	handle_error_forking(t_commands *cmd)
{
	perror("Error forking process");
	free(cmd->redir->centent);
	exit(EXIT_FAILURE);
}

void	createpipes(t_commands *cmd, int *index)
{
	int	j;

	j = 0;
	if (pipe(cmd->redir[*index].pipefd) == -1)
	{
		perror("Error creating pipe");
		while (j < *index)
		{
			close(cmd->redir[j].pipefd[0]);
			close(cmd->redir[j].pipefd[1]);
			j++;
		}
		free(cmd->redir->centent);
		exit(EXIT_FAILURE);
	}
}
