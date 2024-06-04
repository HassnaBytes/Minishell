/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houattou <houattou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:51:39 by houattou          #+#    #+#             */
/*   Updated: 2023/08/15 06:40:48 by houattou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "./libft/libft.h"

t_g_lb_data	g_lb_data;

void	replace_tabs(char *str)
{
	int	idx;

	if (!str)
		return ;
	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '\t')
			str[idx] = ' ';
		idx++;
	}
}

void	init_g_lb_data(void)
{
	g_lb_data.exit_status = 0;
	g_lb_data.g_pid = 0;
	g_lb_data.signal = 0;
}

void	free_env(t_env *env)
{
	t_env	*holder;
	t_env	*to_free;

	holder = env;
	while (holder)
	{
		to_free = holder;
		free(to_free->key);
		free(to_free->value);
		holder = holder->next;
	}
}

void	init(char **env, t_env **env_list, int ac, char **av)
{
	(void)av,
		(void)ac;
	copy_env(env, env_list, 0);
}

int	main(int ac, char **av, char **env)
{
	char		*user_input;
	t_commands	*cmd;
	t_env		*env_list;

	env_list = NULL;
	init(env, &env_list, ac, av);
	handle_parent_signals();
	init_g_lb_data();
	while (true)
	{
		g_lb_data.signal = 0;
		user_input = readline("minishell: ");
		replace_tabs(user_input);
		cmd = parse(user_input, env_list, env);
		if (!cmd)
		{
			free(user_input);
			continue ;
		}
		execute(cmd, env_list);
		free_commands(cmd);
		cmd = NULL;
		free(user_input);
	}
	return (g_lb_data.exit_status);
}
