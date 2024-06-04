/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 00:42:58 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 01:48:08 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	idx;

	idx = 0;
	while (s1[idx])
	{
		if (s1[idx] != s2[idx])
			return (s1[idx] - s2[idx]);
		idx++;
	}
	if (s1[idx] != s2[idx])
		return (s1[idx] - s2[idx]);
	return (0);
}

int	check_is_path_exist(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, "PATH"))
			return (1);
		current = current->next;
	}
	return (0);
}

void	print_errors(char *cmd, char *arg, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	is_number(char str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

int	is_alpha(char str)
{
	int	i;

	i = 0;
	if ((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z'))
		return (1);
	return (0);
}
