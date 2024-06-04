/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 03:10:40 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 06:36:26 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	free_str(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

char	*search_cmd_path(t_commands *cmd, char **token)
{
	char	cmd_path[PATH_MAX];
	int		i;
	char	*holder;

	i = 0;
	while (token[i] != NULL)
	{
		ft_strcpy(cmd_path, token[i]);
		ft_strcat(cmd_path, "/");
		ft_strcat(cmd_path, cmd->command);
		if (access(cmd_path, X_OK) == 0)
		{
			return (ft_strdup(cmd_path));
		}
		i++;
	}
	holder = NULL;
	holder = ft_strjoin(holder, cmd->command);
	if (access(holder, X_OK) == 0)
		return (holder);
	free(holder);
	return (NULL);
}

char	*find_cmd_path(t_commands *cmd, char *path_env)
{
	char	**token;

	token = ft_split(path_env, ':');
	if (token == NULL)
		return (NULL);
	cmd->path = search_cmd_path(cmd, token);
	free_2d(token);
	return (cmd->path);
}
