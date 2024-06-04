/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 23:48:02 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 05:21:38 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

static void	get_commands_comp(t_commands *commands, char **splited_command,
		char **env, int *idx)
{
	size_t	str_2d_count;

	str_2d_count = str2d_len(splited_command);
	commands[(*idx)].redir = NULL;
	commands[(*idx)].redir_count = 0;
	commands[(*idx)].command = get_first_word(splited_command[(*idx)]);
	commands[(*idx)].environment = env;
	commands[(*idx)].arg = split_pipe(splited_command[(*idx)], ' ');
	commands[(*idx)].commands_count = (int)str_2d_count;
	(*idx)++;
}

static t_commands	*get_commands(const char *input, char **env)
{
	char		**splited_command;
	int			idx;
	size_t		str_2d_count;
	t_commands	*commands;

	splited_command = split_pipe((char *)input, '|');
	if (!splited_command)
		return (NULL);
	trim_commands(splited_command);
	str_2d_count = str2d_len(splited_command);
	commands = ft_calloc(str_2d_count + 1, sizeof(t_commands));
	idx = 0;
	init_commands(commands, str_2d_count);
	while (splited_command[idx])
	{
		if (redir_check(splited_command[idx]))
		{
			handle_redirection(&commands[idx], splited_command[idx], NULL);
			idx++;
			continue ;
		}
		get_commands_comp(commands, splited_command, env, &idx);
	}
	free_2d(splited_command);
	return (commands);
}

bool	check_after_expand(char *str, t_env *env)
{
	char	*holder;

	if (!str)
		return (false);
	holder = ft_strdup(str);
	holder = expand(holder, env, true, false);
	if (!holder)
	{
		free(holder);
		return (false);
	}
	else if (holder[0] == '\0')
	{
		free(holder);
		return (false);
	}
	free(holder);
	return (true);
}

void	parse_comp(t_commands *commands, t_env *env, char *holder)
{
	init_expand(commands, env);
	fixing_expand(commands);
	should_expand_her(commands);
	handle_quotes(commands);
	handling_empty_quotes(commands);
	free(holder);
}

t_commands	*parse(const char *input, t_env *env, char **env_arr)
{
	t_commands	*commands;
	char		*holder;

	if (input == NULL)
		exit(g_lb_data.exit_status);
	holder = ft_strtrim(input, " \t");
	if (ft_strlen(holder) == 0)
	{
		free(holder);
		holder = NULL;
		return (NULL);
	}
	add_history(input);
	if (!holder)
		return (NULL);
	if (!check_after_expand(holder, env) || !check_user_input(holder))
	{
		free(holder);
		return (NULL);
	}
	commands = get_commands(holder, env_arr);
	parse_comp(commands, env, holder);
	return (commands);
}
