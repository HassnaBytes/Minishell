/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 10:59:41 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/14 08:37:57 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

bool	print_err(char *str)
{
	ft_putstr_fd(str, 2);
	return (false);
}

void	end_free(void *p1, void *p2, void *p3, void *p4)
{
	if (p1)
	{
		free(p1);
		p1 = NULL;
	}
	if (p2)
	{
		free(p2);
		p2 = NULL;
	}
	if (p3)
	{
		free(p3);
		p3 = NULL;
	}
	if (p4)
	{
		free(p4);
		p4 = NULL;
	}
}

void	init_commands(t_commands *commands, size_t count)
{
	int	idx;

	idx = 0;
	while (idx < (int)count)
	{
		commands[idx].command = NULL;
		commands[idx].arg = NULL;
		commands[idx].path = NULL;
		commands[idx].environment = NULL;
		commands[idx].commands_count = (unsigned int)count;
		idx++;
	}
}

void	free_commands(t_commands *commands)
{
	int	idx;
	int	idx2;

	idx = 0;
	while (idx < commands->commands_count)
	{
		idx2 = 0;
		if (commands[idx].command)
			free(commands[idx].command);
		if (commands[idx].arg)
			free_2d(commands[idx].arg);
		if (commands[idx].path)
			free(commands[idx].path);
		if (commands[idx].redir)
		{
			while (idx2 < commands[idx].redir_count)
			{
				free(commands[idx].redir[idx2].file_out);
				idx2++;
			}
			free(commands[idx].redir);
		}
		idx++;
	}
	free(commands);
}
