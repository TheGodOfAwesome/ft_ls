/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:51:19 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/06/10 20:27:23 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	t;
	unsigned char	*src;
	size_t			i;

	i = 0;
	t = (unsigned char)c;
	src = (unsigned char *)s;
	while (i < n)
	{
		if (*src == t)
		{
			return ((void *)src);
		}
		src++;
		i++;
	}
	return (NULL);
}
