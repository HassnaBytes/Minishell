/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:32:49 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/14 11:05:48 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

char	*add_space(char *str, bool double_quotes, bool single_quotes)
{
	char	*new_str;
	int		idx;

	idx = 0;
	new_str = NULL;
	while (str[idx])
	{
		quotes_switcher(&single_quotes, &double_quotes, str[idx] == '\'',
			str[idx] == '"');
		if (str[idx] == '>' && str[idx + 1] == '>' && double_quotes
			&& single_quotes)
			add_space_comp(&new_str, &idx, " >> ", 1);
		else if (str[idx] == '<' && str[idx + 1] == '<' && double_quotes
			&& single_quotes)
			add_space_comp(&new_str, &idx, " << ", 1);
		else if (str[idx] == '>' && double_quotes && single_quotes)
			new_str = ft_strjoin(new_str, " > ");
		else if (str[idx] == '<' && double_quotes && single_quotes)
			new_str = ft_strjoin(new_str, " < ");
		else
			new_str = append_str(new_str, str[idx]);
		idx++;
	}
	return (new_str);
}

void	add_special_char_comp_two(char *str, t_add_special *data)
{
	quotes_switcher(&(*data).single_quotes, &(*data).double_quotes,
		str[(*data).idx] == '\'', str[(*data).idx] == '"');
	if (str[(*data).idx] == '>' && str[(*data).idx + 1] == '>'
		&& (*data).double_quotes && (*data).single_quotes)
	{
		add_special_char_comp(&(*data).trigger, &(*data).new_str, ">>");
		(*data).idx += 1;
	}
	else if (str[(*data).idx] == '<' && str[(*data).idx] == '<'
		&& str[(*data).idx + 1] == '<' && (*data).double_quotes
		&& (*data).single_quotes)
	{
		add_special_char_comp(&(*data).trigger, &(*data).new_str, "<<");
		(*data).idx += 1;
	}
	else if (str[(*data).idx] == '>' && (*data).double_quotes
		&& (*data).single_quotes)
		add_special_char_comp(&(*data).trigger, &(*data).new_str, ">");
	else if ((str[(*data).idx] == '<' && (*data).double_quotes
			&& (*data).single_quotes))
		add_special_char_comp(&(*data).trigger, &(*data).new_str, "<");
	else
		(*data).new_str = append_str((*data).new_str, str[(*data).idx]);
}

void	handle_redirection_con_two(t_commands *commands,
	char **holder, int redir_idx)
{
	int	idx2;

	idx2 = 0;
	commands->command = ft_strdup(holder[0]);
	while (!check_if_redir(holder[idx2]))
		commands->arg = join_arr(commands->arg, holder[idx2++]);
	commands->redir[redir_idx].type = get_redir_type(holder[idx2++]);
	commands->redir[redir_idx].file_out = ft_strdup(holder[idx2++]);
	while (holder[idx2])
		commands->arg = join_arr(commands->arg, holder[idx2++]);
}

void	handle_redirection_con_tree(t_commands *commands,
	char **holder, int *idx2)
{
	if (holder[(*idx2)])
	{
		if (commands->command == NULL)
			commands->command = ft_strdup(holder[(*idx2)]);
		commands->arg = join_arr(commands->arg, holder[(*idx2)++]);
	}
	while (holder[(*idx2)])
		commands->arg = join_arr(commands->arg, holder[(*idx2)++]);
}

void	handle_redirection(t_commands *commands, char *str, char *help)
{
	int		idx;
	char	*new_str;
	char	*holder;
	char	**splited;

	(void)help;
	idx = 0;
	init_redir(commands->redir, commands->redir_count);
	commands->redir = ft_calloc(count_redir_for_alloc(str, true, true),
			sizeof(t_redir));
	commands->redir_count = count_redir_for_alloc(str, true, true);
	new_str = NULL;
	new_str = add_space(str, true, true);
	holder = new_str;
	new_str = add_special_char(new_str);
	free(holder);
	splited = split_pipe(new_str, 11);
	handle_redirection_con(commands, splited);
	free(new_str);
	free_2d(splited);
}
