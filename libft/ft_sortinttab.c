/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sortinttab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/09 11:10:11 by exam              #+#    #+#             */
/*   Updated: 2017/08/26 15:55:18 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sortinttab(int *tab, int size)
{
	unsigned int		i;
	int					j;
	unsigned int		k;
	int					s;

	k = size - 1;
	s = 1;
	while (s > 0)
	{
		i = 0;
		j = 1;
		s = 0;
		while (i < k)
		{
			if (ft_intcmp(tab[i], tab[j]) == 1)
			{
				ft_intswap(&tab[i], &tab[j]);
				s++;
			}
			i++;
			j++;
		}
	}
}
