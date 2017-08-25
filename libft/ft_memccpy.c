/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 13:33:10 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/06/11 13:34:58 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*sdst;
	unsigned char	*ssrc;
	unsigned char	t;

	i = 0;
	sdst = (unsigned char *)dst;
	ssrc = (unsigned char *)src;
	t = (unsigned char)c;
	while (i < n)
	{
		sdst[i] = ssrc[i];
		if (ssrc[i] == t)
			return (sdst + i + 1);
		i++;
	}
	return (NULL);
}
