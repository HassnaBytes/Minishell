/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 15:09:04 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

static bool	check_new_line_flag(char *str)
{
	int	idx;

	idx = 1;
	if (str[0] == '-')
	{
		while (str[idx])
		{
			if (str[idx] != 'n')
				return (true);
			idx++;
		}
		return (false);
	}
	return (true);
}

void	skip_new_line_flag(t_commands *command, int *idx)
{
	while (command->arg[*idx] && command->arg[*idx][0] == '-'
		&& !check_new_line_flag(command->arg[*idx]))
		(*idx)++;
}

void	echo_whitout_redir(t_commands *command, int idx, bool new_line_state)
{
	int	idx2;

	g_lb_data.exit_status = 0;
	while (command->arg[idx])
	{
		idx2 = 0;
		while (command->arg[idx][idx2])
		{
			write(1, &command->arg[idx][idx2], 1);
			idx2++;
		}
		if (command->arg[idx + 1])
			write(1, " ", 1);
		idx++;
	}
	if (new_line_state)
		write(1, "\n", 1);
}

void	echo_cmd(t_commands *command)
{
	int		idx;
	bool	new_line_state;

	idx = 1;
	if (str2d_len(command->arg) == 1)
	{
		g_lb_data.exit_status = 0;
		printf("\n");
		return ;
	}
	new_line_state = check_new_line_flag(command->arg[idx]);
	skip_new_line_flag(command, &idx);
	echo_whitout_redir(command, idx, new_line_state);
}
