/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_com.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 15:19:16 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 01:02:14 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

void	trim_commands(char **commands)
{
	int		idx;
	char	*cpy;

	idx = 0;
	while (commands[idx])
	{
		cpy = malloc(ft_strlen(commands[idx]) + 1);
		ft_strlcpy(cpy, commands[idx], ft_strlen(commands[idx]) + 1);
		free(commands[idx]);
		commands[idx] = NULL;
		commands[idx] = ft_strtrim(cpy, " \n\t");
		free(cpy);
		cpy = NULL;
		idx++;
	}
}

char	*join_commands(char **str)
{
	char	*holder;

	holder = join_splite(str, 0);
	if (!holder)
		return (NULL);
	return (holder);
}

void	str_remove_pos(char *str, int pos)
{
	int		idx;

	if (!str)
		return ;
	idx = 0;
	while (idx != pos)
		idx++;
	while (str[idx])
	{
		str[idx] = str[idx + 1];
		idx++;
	}
}

char	*append_str(char *str, char c)
{
	char			*new_str;
	unsigned int	idx;

	if (!str)
	{
		new_str = ft_calloc(2, 1);
		new_str[0] = c;
		return (new_str);
	}
	idx = 0;
	new_str = ft_calloc(ft_strlen(str) + 2, 1);
	if (!new_str)
		return (NULL);
	while (str[idx])
	{
		new_str[idx] = str[idx];
		idx++;
	}
	new_str[idx] = c;
	free(str);
	str = NULL;
	return (new_str);
}

char	*append_str_begining(char *str, char c)
{
	int		idx;
	char	*new_str;

	idx = 0;
	if (!str)
	{
		new_str = ft_calloc(2, 1);
		new_str[0] = c;
		return (new_str);
	}
	new_str = ft_calloc(ft_strlen(str) + 2, 1);
	new_str[idx++] = c;
	while (str[idx - 1])
	{
		new_str[idx] = str[idx - 1];
		idx++;
	}
	free(str);
	str = NULL;
	return (new_str);
}
