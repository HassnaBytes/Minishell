/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_comp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:20:13 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/14 05:37:48 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	init_expand_comp(t_commands *commands, t_env *env, int idx)
{
	int	idx2;

	idx2 = 0;
	while (idx2 < commands[idx].redir_count)
	{
		if (commands[idx].redir[idx2].type != 'H')
			commands[idx].redir[idx2].file_out
				= expand(commands[idx].redir[idx2].file_out,
					env,
					true,
					false);
		idx2++;
	}
}

void	init_expand(t_commands *commands, t_env *env)
{
	int	idx;
	int	idx2;

	idx = 0;
	while (idx < commands[0].commands_count)
	{
		idx2 = 0;
		if (commands[idx].command)
			commands[idx].command = expand(commands[idx].command, env, true,
					false);
		if (commands[idx].arg)
		{
			while (commands[idx].arg[idx2])
			{
				commands[idx].arg[idx2] = expand(commands[idx].arg[idx2], env,
						true, false);
				idx2++;
			}
		}
		if (commands[idx].redir)
		{
			init_expand_comp(commands, env, idx);
		}
		idx++;
	}
}

void	should_expand_her(t_commands *commands)
{
	int	idx;
	int	idx2;

	idx = 0;
	while (idx < commands[0].commands_count)
	{
		idx2 = 0;
		if (commands[idx].redir)
		{
			while (idx2 < commands[idx].redir_count)
			{
				if (commands[idx].redir[idx2].type == 'H')
				{
					if (commands[idx].redir[idx2].file_out[0] == '\''
						|| commands[idx].redir[idx2].file_out[0] == '"')
						commands[idx].should_expand_heredoc = false;
					else
						commands[idx].should_expand_heredoc = true;
				}
				idx2++;
			}
		}
		idx++;
	}
}

void	handling_empty_quotes(t_commands *commands)
{
	int	idx;

	idx = 0;
	while (idx < commands[0].commands_count)
	{
		if (!commands[idx].command && !commands[idx].redir)
		{
			commands[idx].command = ft_strdup(" ");
		}
		idx++;
	}
}
