/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 04:12:47 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

#define MAX_LEN 19

static bool	compare(const char *str, const char *value)
{
	while (*str)
	{
		if (*str > *value)
			return (false);
		else if (*str < *value)
			return (true);
		str++;
		value++;
	}
	return (true);
}

bool	return_greater(char *str, char sign)
{
	char	*max;
	char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	if (sign == '+' || sign == 0)
		return (compare(str, max));
	return (compare(str, min));
}

bool	return_max(char *str)
{
	int		len;
	char	sign;

	sign = 0;
	if (*str == '-' || *str == '+')
	{
		sign = *str;
		str++;
	}
	len = ft_strlen(str);
	if (len < MAX_LEN)
		return (false);
	else if (len > MAX_LEN)
		return (true);
	else
		return (!return_greater(str, sign));
	return (false);
}

bool	is_digit(char *str)
{
	if (return_max(str))
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!(*str <= '9' && *str >= '0'))
			return (false);
		str++;
	}
	return (true);
}

void	exit_cmd(t_commands *cmd)
{
	if (!cmd->arg[1])
	{
		exit(g_lb_data.exit_status);
	}
	if (cmd->arg[1] && !is_digit(cmd->arg[1]))
	{
		print_errors("exit", cmd->arg[1], "numeric argument required");
		g_lb_data.exit_status = 255;
		exit(g_lb_data.exit_status);
	}
	if (cmd->arg[2])
	{
		g_lb_data.exit_status = 1;
		print_errors("exit", "too many arguments", NULL);
		return ;
	}
	if (cmd->arg[1] && is_digit(cmd->arg[1]))
	{
		g_lb_data.exit_status = ft_atoi(cmd->arg[1]);
		exit(g_lb_data.exit_status);
	}
}
