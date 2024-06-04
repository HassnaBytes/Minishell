/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 22:19:34 by houattou          #+#    #+#             */
/*   Updated: 2023/08/13 22:27:49 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

char	*find_path(t_env *env_list, char *path_search)
{
	while (env_list != NULL)
	{
		if (!ft_strncmp(env_list->key, path_search, ft_strlen(env_list->key)
				+ 1))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
