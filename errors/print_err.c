/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 09:03:17 by sait-bah          #+#    #+#             */
/*   Updated: 2023/06/18 11:00:57 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/minishell.h"

void	release_mem(void *para1, void *para2, void *para3, void *para4)
{
	if (para1)
		free(para1);
	if (para2)
		free(para2);
	if (para3)
		free(para3);
	if (para4)
		free(para4);
}
