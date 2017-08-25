/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 10:23:12 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/06/11 15:14:53 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int index;
	int len;

	i = 0;
	index = 0;
	len = ft_strlen((char *)needle);
	if (len == 0)
		return ((char *)haystack);
	while (haystack[i])
	{
		while (needle[index] == haystack[index + i])
		{
			if (index == len - 1)
				return ((char *)(haystack + i));
			index++;
		}
		index = 0;
		i++;
	}
	return (NULL);
}
