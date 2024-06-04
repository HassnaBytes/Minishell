/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 01:34:05 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

t_env	*modify_value(t_env *env_list, char *key, char *value)
{
	t_env	*current;
	int		is_have_key;

	current = env_list;
	is_have_key = check_if_key_exist_and_update(env_list, key);
	if (is_have_key)
		current = update_existing_key(env_list, key, value);
	else
		current = add_new_key(env_list, key, value);
	return (current);
}

t_env	*add_node(t_env *env_list, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	if (value != NULL)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	if (env_list == NULL)
	{
		env_list = new_node;
	}
	else
	{
		current = env_list;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
	return (env_list);
}

void	add_declare_to_env(t_env *env_list)
{
	t_env	*current;

	current = env_list;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->key, 1);
			ft_putstr_fd("\n", 1);
		}
		current = current->next;
	}
	g_lb_data.exit_status = 0;
}

t_env	*add_new_key(t_env *env_list, char *key, char *value)
{
	if (value != NULL)
		return (add_node(env_list, key, value));
	else
		return (add_node(env_list, key, NULL));
}

int	check_if_key_exist_and_update(t_env *env_list, char *key)
{
	t_env	*current;

	current = env_list;
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, key))
			return (1);
		current = current->next;
	}
	return (0);
}
