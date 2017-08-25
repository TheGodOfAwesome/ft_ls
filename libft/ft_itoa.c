/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 10:40:31 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/07 12:54:02 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_itoa(int nbr)
{
	static char	rep[] = "0123456789ABCDEF";
	static char buff[65];
	char		*ptr;
	long long	num;
	int			base;

	ptr = &buff[64];
	base = 10;
	if (base < 2 || base > 16)
		return (0);
	*ptr = '\0';
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
