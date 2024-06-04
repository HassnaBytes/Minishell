/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-bah <sait-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 01:59:47 by sait-bah          #+#    #+#             */
/*   Updated: 2023/02/01 06:35:16 by sait-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	numberscounter(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	numberconvert(char *p, long int numberlength, long int holder)
{
	while (holder != 0)
	{
		p[numberlength] = (holder % 10) + 48;
		numberlength--;
		holder /= 10;
	}
}

char	*ft_itoa(int n)
{
	long int	numberlength;
	char		*p;
	int			pindex;
	long int	holder;

	holder = (long int) n;
	numberlength = numberscounter(holder);
	pindex = 0;
	p = ft_calloc(numberlength + 1, sizeof(char));
	if (!p)
		return (0);
	p[numberlength] = '\0';
	numberlength--;
	if (holder == 0)
		p[0] = '0';
	else if (holder < 0)
	{
		holder *= -1;
		p[0] = '-';
	}
	numberconvert(p, numberlength, holder);
	return (p);
}
