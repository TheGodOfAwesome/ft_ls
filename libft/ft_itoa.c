/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:40:31 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/15 16:46:10 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	ft_count_int_len(int num, int base)
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

static char	*ft_itoa_base(int nbr, int base)
{
	static char	rep[] = "0123456789ABCDEF";
	char		*ptr;
	long long	num;

	ptr = (char *)malloc(sizeof(char) * ft_count_int_len(nbr, base) + 1);
	if (!ptr)
		return (NULL);
	ptr = &ptr[ft_count_int_len(nbr, base)];
	*ptr = '\0';
	if (base < 2 || base > 16)
		return (0);
	num = nbr;
	if (num < 0)
		num *= -1;
	if (num == 0)
		*(--ptr) = rep[num % base];
	while (num != 0)
	{
		*(--ptr) = rep[num % base];
		num /= base;
	}
	if (nbr < 0 && base == 10)
		*(--ptr) = '-';
	return (ptr);
}

char		*ft_itoa(int nbr)
{
	char	*str;

	if (nbr == -2147483648)
	{
		str = ft_strdup("-2147483648");
		return (str);
	}
	else if (nbr == 2147483647)
	{
		str = ft_strdup("2147483647");
		return (str);
	}
	else if (nbr == 0)
	{
		str = ft_strdup("0");
		return (str);
	}
	str = ft_itoa_base(nbr, 10);
	return (str);
}
