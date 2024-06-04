/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:27:23 by sait-bah          #+#    #+#             */
/*   Updated: 2022/10/12 04:15:35 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int alnum)
{
	return ((ft_isalpha(alnum) == 1) || (ft_isdigit(alnum) == 1));
}
