/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revsortstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 15:30:44 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/09/19 18:07:13 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_revsortstr(char **str, int max)
{
	int     i;
	int     pairs_count;
	char    *temp;

	i = -1;
	pairs_count = 1;
	while (pairs_count)
	{
		pairs_count = 0;
		i = 0;
		while (i + 1 < max)
		{
			if (*(str + 1) != NULL)
			{
				if (ft_strcmp(str[i], str[i + 1]) < 0)
				{
					temp = str[i];
					str[i] = str[i + 1];
					str[i + 1] = temp;
					pairs_count++;
				}
			}
			i++;
		}
	}
}
