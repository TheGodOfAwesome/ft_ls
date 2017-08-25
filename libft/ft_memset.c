/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 08:26:35 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/08/07 13:23:24 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *str, int c, int len)
{
	unsigned char	*strchange;

	strchange = (unsigned char *)str;
	while (len > 0)
	{
		*strchange = (unsigned char)c;
		strchange++;
		len--;
	}
	return (str);
}
