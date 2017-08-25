/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 16:29:23 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/14 15:07:02 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_base(int nbr, int base)
{
	static char	rep[] = "0123456789ABCDEF";
	static char	buff[65];
	char		*ptr;
	long long	num;

	ptr = &buff[64];
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
		*--ptr = rep[num % base];
		num /= base;
	}
	if (nbr < 0 && base == 10)
		*--ptr = '-';
	return (ptr);
}

void		ft_putnbr_fd(int n, int fd)
{
	char	*s;

	s = ft_itoa_base(n, 10);
	ft_putstr_fd(s, fd);
}
