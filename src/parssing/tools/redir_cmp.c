/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 08:47:22 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/14 08:49:47 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

size_t	count_redirs(char **splited)
{
	size_t	counter;
	int		idx;

	idx = 0;
	counter = 0;
	while (splited[idx])
	{
		if (redir_check(splited[idx]))
			counter++;
		idx++;
	}
	return (counter);
}

void	init_redir(t_redir *redirs, int count)
{
	int	idx;

	idx = 0;
	while (idx < count)
	{
		redirs[idx].file_out = NULL;
		redirs[idx].type = 0;
		idx++;
	}
}

bool	check_if_redir(char *str)
{
	return (ft_strncmp(str, ">>", ft_strlen(str)) == 0 || ft_strncmp(str, "<<",
			ft_strlen(str)) == 0 || ft_strncmp(str, ">", ft_strlen(str)) == 0
		|| ft_strncmp(str, "<", ft_strlen(str)) == 0);
}

char	get_redir_type(char *str)
{
	if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
		return ('O');
	if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
		return ('I');
	if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
		return ('A');
	if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return ('H');
	return (0);
}

void	count_redir_for_alloc_comp(char *str, int *idx, char c, int *count)
{
	(*count)++;
	if (str[(*idx) + 1] == c)
		(*idx) += 2;
	else
		(*idx)++;
}
