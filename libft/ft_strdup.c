/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmuvezwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 01:23:19 by kmuvezwa          #+#    #+#             */
/*   Updated: 2017/06/11 03:00:32 by kmuvezwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		count;
	char	*temp;

	i = 0;
	count = ft_strlen((char *)s1);
	temp = (char *)malloc(sizeof(char) * (count + 1));
	if (temp)
	{
		while (s1[i] != '\0')
		{
			temp[i] = s1[i];
			i++;
		}
		temp[i] = '\0';
		return ((char *)temp);
	}
	return (NULL);
}
