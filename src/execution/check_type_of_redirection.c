/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_of_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:53:43 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	dup_fd(t_commands *cmd, int i)
{
	dup2(cmd->redir[i].pipefd[0], STDIN_FILENO);
	close(cmd->redir[i].pipefd[0]);
}

void	call_handle_output_file(t_commands *cmd, int *fd, int i)
{
	if (handle_output_file(cmd, fd, i) != EXIT_SUCCESS)
	{
		g_lb_data.exit_status = 1;
		return ;
	}
}

void	check_type_of_redirection(t_commands *cmd, int *fd)
{
	int	i;

	i = 0;
	if (cmd->redir_count > 0)
	{
		while (i < cmd->redir_count)
		{
			if (cmd->redir[i].type == 'I')
			{
				if (handle_input_file(cmd, fd, i) != EXIT_SUCCESS)
					break ;
			}
			else if (cmd->redir[i].type == 'O' || cmd->redir[i].type == 'A')
				call_handle_output_file(cmd, fd, i);
			else
				dup_fd(cmd, i);
			i++;
		}
	}
}
