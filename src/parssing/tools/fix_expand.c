/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 05:41:02 by sait-bah          #+#    #+#             */
/*   Updated: 2023/08/15 01:03:15 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../libft/libft.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	counter;
	int	countertrigger;

	i = 0;
	counter = 0;
	countertrigger = 1;
	while (str[i] != '\0')
	{
		if (str[i] != c && countertrigger == 1)
		{
			counter++;
			countertrigger = 0;
		}
		else if (str[i] == c)
		{
			countertrigger = 1;
		}
		i++;
	}
	return (counter);
}

void	fixing_expand_comp(t_commands *commands, int idx, char **holder2)
{
	if (str2d_len(commands[idx].arg) == 1)
	{
		if (count_words(commands[idx].arg[0], ' ') > 1)
		{
			holder2 = ft_split(commands[idx].arg[0], ' ');
			free_2d(commands[idx].arg);
			commands[idx].arg = holder2;
		}
	}
}

void	fixing_expand(t_commands *commands)
{
	int		idx;
	char	*holder;
	char	**holder2;

	idx = 0;
	holder2 = NULL;
	while (idx < commands[idx].commands_count)
	{
		if (commands[idx].command)
		{
			if (count_words(commands[idx].command, ' ') > 1)
			{
				holder = get_first_word(commands[idx].command);
				free(commands[idx].command);
				commands[idx].command = holder;
			}
		}
		if (commands[idx].arg)
		{
			fixing_expand_comp(commands, idx, holder2);
		}
		idx++;
	}
}
