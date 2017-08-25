/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 11:05:45 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/13 14:30:13 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		num;

	i = 0;
	num = 0;
	sign = 1;
	if (ft_strlen((char *)str) == 0)
		return (0);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' ||
		str[i] == '\n' || str[i] == '\f' || str[i] == '\r')
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	(str[i] == '-' || str[i] == '+') ? i++ : 0;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (i >= 19 && sign == 1)
		return (-1);
	else if (i >= 19)
		return (0);
	return (num * sign);
}
