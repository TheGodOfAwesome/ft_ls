/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/28 12:31:41 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/05/29 16:36:03 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*sdst;
	char	*ssrc;
	size_t	i;

	i = 0;
	sdst = (char *)dst;
	ssrc = (char *)src;
	while (i < n)
	{
		sdst[i] = ssrc[i];
		i++;
	}
	return ((void *)sdst);
}
