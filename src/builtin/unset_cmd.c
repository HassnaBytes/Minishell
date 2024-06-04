/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:36:18 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	delete_key(t_env **list, char *key)
{
	t_env	*current;
	t_env	*ptr;

	current = *list;
	ptr = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			if (ptr == NULL)
			{
				*list = current->next;
			}
			else
			{
				ptr->next = current->next;
			}
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		ptr = current;
		current = current->next;
	}
}

int	check_is_valid_arg(char *str)
{
	int	i;

	i = 1;
	if (!(is_alpha(str[0]) || str[0] == '_'))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (0);
	}
	i = 1;
	while (str[i] != '\0')
	{
		if (!(is_number(str[i]) || is_alpha(str[i]) || str[i] == '_'))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

void	unset_cmd(t_commands *cmd, t_env *env_list)
{
	int	i;

	i = 1;
	while (cmd->arg[i])
	{
		if (!check_is_valid_arg(cmd->arg[i]))
		{
			g_lb_data.exit_status = 1;
			i++;
			continue ;
		}
		delete_key(&env_list, cmd->arg[i++]);
	}
	return ;
}
