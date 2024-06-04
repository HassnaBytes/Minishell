/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:34:59 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stddef.h>

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	ft_insert_env(t_env **head, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

void	parse_env(char *env_var, char **key, char **value)
{
	char	*delimiter;
	int		key_length;

	delimiter = ft_strchr(env_var, '=');
	if (delimiter != NULL)
	{
		key_length = delimiter - env_var;
		*key = malloc((key_length + 1) * sizeof(char));
		ft_strncpy(*key, env_var, key_length);
		(*key)[key_length] = '\0';
		*value = ft_strdup(delimiter + 1);
	}
	else
	{
		*key = NULL;
		*value = NULL;
	}
}

void	copy_env(char **envp, t_env **head, int i)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	while (envp[i] != NULL)
	{
		parse_env(envp[i], &key, &value);
		if (key != NULL && value != NULL)
		{
			ft_insert_env(head, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

void	env_cmd(t_env *head, t_commands *cmd)
{
	t_env	*current;

	current = head;
	if (!cmd->arg[1])
	{
		while (current != NULL)
		{
			if (!check_is_path_exist(head))
			{
				ft_putstr_fd("bash: env: No such file or directory\n", 2);
				g_lb_data.exit_status = 127;
				return ;
			}
			if (current->value != NULL)
				printf("%s=%s\n", current->key, current->value);
			current = current->next;
			g_lb_data.exit_status = 0;
		}
	}
	else
	{
		ft_putstr_fd("bash: env: No such file or directoryn", 2);
		g_lb_data.exit_status = 127;
	}
}
