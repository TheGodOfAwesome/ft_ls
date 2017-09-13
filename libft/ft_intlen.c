/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 11:52:15 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/09/13 11:53:54 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_int_len(int num, int base)
{
	int		i;

	i = 0;
	if (num < 0 && base == 10)
	{
		num = num * -1;
		i++;
	}
	while (num != 0)
	{
		num = num / base;
		i++;
	}
	return (i);
}
