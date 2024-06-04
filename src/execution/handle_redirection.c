/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:15:03 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	open_output_file(t_commands *cmd, int pos)
{
	int	fd;

	if (cmd->redir[pos].type == 'A')
		fd = open(cmd->redir[pos].file_out, O_CREAT | O_WRONLY | O_APPEND,
				0644);
	else if (cmd->redir[pos].type == 'O')
		fd = open(cmd->redir[pos].file_out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = -1;
	return (fd);
}

int	handle_output_file(t_commands *cmd, int *fd, int pos)
{
	*fd = open_output_file(cmd, pos);
	if (*fd < 0)
	{
		print_errors(cmd->redir[pos].file_out, NULL, strerror(errno));
		g_lb_data.exit_status = 1;
		return (EXIT_FAILURE);
	}
	dup2(*fd, STDOUT_FILENO);
	if (pos != cmd->redir_count && (cmd->redir->type == 'A'
			|| cmd->redir->type == 'O'))
		close(*fd);
	return (EXIT_SUCCESS);
}

int	handle_input_file(t_commands *cmd, int *fd, int pos)
{
	*fd = open(cmd->redir[pos].file_out, O_RDONLY);
	if (*fd < 0)
	{
		print_errors(cmd->redir[pos].file_out, NULL, strerror(errno));
		g_lb_data.exit_status = 1;
		return (EXIT_FAILURE);
	}
	dup2(*fd, STDIN_FILENO);
	if (pos != cmd->redir_count && cmd->redir->type == 'I')
		close(*fd);
	return (EXIT_SUCCESS);
}
