/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmp_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:57:05 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/14 11:24:51 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

void	handle_redirection_con(t_commands *commands, char **splited)
{
	int		idx;
	char	**holder;
	int		redir_idx;
	int		idx2;

	idx = 0;
	redir_idx = 0;
	while (splited[idx])
	{
		idx2 = 1;
		holder = split_pipe(splited[idx], ' ');
		if (check_if_redir(holder[0]))
		{
			commands->redir[redir_idx].type = get_redir_type(holder[0]);
			commands->redir[redir_idx].file_out = ft_strdup(holder[idx2++]);
			handle_redirection_con_tree(commands, holder, &idx2);
			while (holder[idx2])
				(commands)->arg = join_arr((commands)->arg, holder[idx2++]);
		}
		else
			handle_redirection_con_two(commands, holder, redir_idx);
		redir_idx++;
		free_2d(holder);
		idx++;
	}
}

char	*add_special_char(char *str)
{
	t_add_special	data;

	init_add_special_char(&data);
	while (str[data.idx])
	{
		add_special_char_comp_two(str, &data);
		data.idx++;
	}
	return (data.new_str);
}

char	*join_splite(char **splited_str, int idx)
{
	int		count;
	char	*str;
	int		str_idx;

	count = 0;
	str_idx = 0;
	while (splited_str[idx])
	{
		count += ft_strlen(splited_str[idx++]);
		str_idx++;
	}
	str = ft_calloc(count + str_idx + 1, 1);
	idx = 0;
	count = 0;
	str_idx = 0;
	while (splited_str[idx])
	{
		count = 0;
		while (splited_str[idx][count])
			str[str_idx++] = splited_str[idx][count++];
		str[str_idx++] = ' ';
		idx++;
	}
	return (str);
}
