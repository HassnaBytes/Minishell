/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 01:39:00 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 01:48:58 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

t_env	*update_existing_key(t_env *env_list, char *key, char *value)
{
	t_env	*current;

	current = env_list;
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, key))
		{
			if (value != NULL)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			break ;
		}
		current = current->next;
	}
	return (current);
}

void	export_argument(char *arg, t_env **env_list)
{
	char	*key;
	char	*value;

	if (!is_valid_key(arg))
	{
		handle_invalid_key(arg);
		return ;
	}
	extract_key_value(arg, &key, &value);
	if (key == NULL)
	{
		key = ft_strdup(arg);
	}
	modify_value(*env_list, key, value);
	free(key);
	free(value);
}
